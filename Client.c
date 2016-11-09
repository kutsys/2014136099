#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <string.h>

#define    MAXLINE        512
#define    MAX_SOCK    128

char *escapechar = "exit";
char name[10];                //채팅에서 사용할 이름

int main(int argc, char *argv[])
{
	char line[MAXLINE], msg[MAXLINE + 1];
	int n, pid;
	int maxfd1;
	int s;
	fd_set read_fds;
/*
	fd_set : 관리하는 파일의 지정번호가 등록되어 있는 비트 배열 구조체
	readfds : 읽을 데이터가 있는지 검사하기 위한 파일 목록
*/
	struct sockaddr_in server_addr;
/* struct sockaddr_in {
	sin_family_t	 sin_family;		 : IPv4 주소체계 
	unist16_t	 sin_port; 	 	 : port 번호
	struct		 in_addr sin_addr;       : IP주소를 나타내는 32 비트 정수 타입 구조체 
	char		 sin_zero[8]; 		 : sockaddr과 같은 크기를 유지하기 위한 잉여공간. 사용하지 않음
}
*/

	//argv[0] = 프로그램 이름
	//argv[1] = serverIP
	//argv[2] = serverPort
	//argv[3] = username 
 	//위 4가지 입력이 이뤄지지 않으면 프로그램 실행X
	if (argc != 4)
	{
		fprintf(stderr, "사용법: %s serverIP serverPort UserName \n", argv[0]);
		exit(0);
	}

	//채팅 참가자 이름 저장
	sprintf(name, "[%s]", argv[3]);
	//name 변수에 argv[3]에 저장된 문자열을 [%s]형식으로 저장 

	//소켓생성
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
/*
int socket(int domain , int type , int protocol)
domain : PF_INET : IPv4 인터넷 프로토콜을 사용
type   : SOCK_STREAM : TCP/IP 프로토콜을 이용.
protocol : 통신에 있어 특정 프로토콜을 사용을 지정하기 위한 변수이며, 보통 0값을 사용
반환값 : -1 -> 실패
 	그 이외 -> 소켓 식별자
*/	
	{
		fprintf(stderr, "Client: Can't open stream socket.\n");
		//socket생성 실패
		exit(0);	
		//program 종료
	}

	//채팅 서버의 소켓주소 저장
	bzero((char *)&server_addr, sizeof(server_addr));
/*void bzero(void *s, size_t n)
작동 : s의 처음 n 바이트를 0으로 채운다.
반환값 없음.
---------------------------------------------
server_addr전체를 0으로 초기화
*/
	server_addr.sin_family = AF_INET;
	//sin_family : 	IPv4 주소체계
	//AF_INET    :  IPv4 인터넷 프로토콜
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	//sin_addr : IP주소를 나타내는 32비트 정수 타입 구조체
	//sin_addr.s_addr : IP주소 저장(확인 필요**********************************)
	//inet_addr()함수는 숫자와 점으로 이루어진 IP문자열을 long형의 숫자 IP로 바꾼다.
	//unsigned long int inet_addr(const char *cp)
	//			      const char *cp : 숫자와 점으로 이루어진 ip 문자열
	//				반환 : -1 - 실패, -1 이외의 수 : 실패
	server_addr.sin_port = htons(atoi(argv[2]));
	//sin_port : port 번호 할당
	//int atoi(const char *str)
	//char *str : 정수로 변환할 10진수 정수 문자열

	//htons() : short int(일반적으로 2byte) 데이터를 network byte order(big-endian) 로 변경한다.
	//unsigned short int htons(unsigned short int hostshort)	
	
	//cpu마다 데이터 저장 박식이 다르다(Little Endian, Big Endian 2 방식)
	//서로 다른 데이터 저장 방식을 사용하는 시스템끼리 통신을 하게 되는 경우 전혀 원하지 않는 값들을 	       //서로 주고받는 경우가 발생할 수 있다. 이런 문제를 해결하기 위해 데이터 통신에서는 network byte 
	//order(Big-endian 방식)을 설정해 놓았다.

	//연결 요청
	if (connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		fprintf(stderr, "Server: Can't bind local address.\n");
		exit(0);
	}
	else
	{
		printf("서버에 접속되었습니다. \n");
	}


	maxfd1 = s + 1;            //최대 소켓번호 + 1
	FD_ZERO(&read_fds);

	while (1)
	{
		FD_SET(s, &read_fds);

		FD_SET(0, &read_fds);
		if (select(maxfd1, &read_fds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) < 0)
		{
			fprintf(stderr, "select error <= 0\n");
			exit(0);
		}

		if (FD_ISSET(s, &read_fds))
		{
			int size;
			if ((size = recv(s, msg, MAXLINE, 0)) > 0)
			{
				msg[size] = '\0';
				printf("%s \n", msg);
			}
		}

		if (FD_ISSET(0, &read_fds))
		{
			if (fgets(msg, MAXLINE, stdin))
			{
				sprintf(line, "%s %s", name, msg);
				if (send(s, line, strlen(line), 0) < 0)
					printf("send() error \n");

				if (strstr(msg, escapechar) != NULL)    //종료문자 처리
				{
					printf("Good bye. \n");
					close(s);
					exit(0);
				}
			}
		}

	}
	return 0;
}
