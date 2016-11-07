//Low-Level 파일 함수를 사용하여 파일복사 프로그램을 작성한다.
//복사할 파일명은 프로그램 파라미터로 지정할 수도 있고, 프로그램 내부에 고정할 수도 있다.

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

int main(int argc , char *argv[])
{
	char block[1024];
	char *Original;// 원본 파일명 저장
	char *Duplication;// 복사 파일명 저장
	int in , out;//open 함수로 읽어들인 File Descriptor 값 저장
	int nread;
	clock_t start, end, buffer;
	//argc == 1 -> '실행 파일명'만 입력받음
 	//argv[1] == NULL -> 복사 대상 파일 이름 입력 없음

	if(argc > 3)
	{
		printf("입력 초과.\n");
		printf("프로그램 종료.\n");
		return;
	}
	
	if(argc <= 1 || argv[1] == NULL)
	{
		printf("복사 대상 파일 이름이 입력되지 않았습니다.\n");
		printf("프로그램 종료.\n");
		exit(1);
	}
	
	//'실행 파일명' 이외의 입력이 존재
	else
	{
		printf("복사 대상 파일 : '%s'\n ",argv[1]); 
		Original = argv[1];
	}

	//argc == 2 -> '실행 파일명', '복사 대상 파일' 이외의 입력이 존재하지 않음
	//argv[2] == NULL -> 복사된 파일 이름 입력 X 
	if(argc <= 2 || argv[2] == NULL)
	{
		printf("복사된 파일 이름이 입력되지 않았습니다. \n");
		printf("'Duplication' 이름을 사용합니다.");
		Duplication = "Duplication";
	}
	
	//'실행 파일명', '복사 대상 파일', '복사된 파일 이름' 입력이 완료. 
	//그 이상의 입력에 대해서는 프로그램 내에서는 어떠한 상호작용도 없음. 
	else
	{
		printf("복사된 파일 이름을 입력받았습니다. \n");
		printf("'%s'이름을 사용합니다\n" , argv[2]);
		Duplication = argv[2];
	}

	//open(const char *path , int flags , mode_t mode);
	//path : 파일 경로를 포함한 이름을 나타내는 문자열 포인터
	//flags : 파일 오픈 모드
	//mode : 생성 파일의 권한 설정
	//성공 시 : File Descriptor 반환 ('0' : 표준 입력장치 , '1' : 표준 출력장치 . '2' : 표준 에러출력장치)
	//실패 시 : -1 반환	

	in = open(Original , O_RDONLY);/* 복사 대상 파일을 읽기 전용으로 읽어들임 */
	//O_RDONLY : 읽기 전용으로 열기
	out = open(Duplication , O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	/*복사된 파일 쓰기 전용으로 만든다*/
	/*O_WRONLY : 쓰기 전용으로 열기*/
	/*O_CREAT : 해당 파일이 없으면 생성한다. 파일의 접근권한을 지정하기 위해 접근권한 값을 추가해야 한다.*/
	//S_IRUSR과 S_IWUSR은 File Access Permission Bit 
	/*S_IRUSR : 사용자가 파일을 읽을 수 있음 , S_IWUSR : 사용자가 파일을 기록할 수 있음.*/

	// open함수 return 값 확인
	if(in == -1 || out == -1)//in 과 out 중 하나라도 -1(파일이 존재하지 않는다면) 지시문 출력 후 프로그램 종료
	{
		printf("File open error\n");
		exit(1);
	}
  	
	printf("복사를 시작합니다.\n");
	
	start = clock();
	buffer = clock();
	while((nread = read(in , block , sizeof(block))) > 0)
	//read(int fd , void *buf , size_t nbytes)
	//int fd : File Descriptor
	//void *buf : 파일을 읽어 들일 버퍼
	//size_t nbytes 버퍼의 크기
	//반환 값 : 정상적으로 읽어들인 경우 -> byte크기 ||  실패한 경우 -> -1
	{
		
          	write(out , block , nread);
		printf("*");

		end = clock();

		if(end - start - buffer >= 1)
		{
			printf("*");
		}
		
		buffer = end;
	}

	close(in);	
	close(out);	
        //open으로 열린 파일 닫기
	
	printf("\n");

	return(0);
}

//1. write/read 함수 이해
//write( 
//2. open 함수 이해
