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
	
	else
	{
		printf("복사 대상 파일 : '%s'\n ",argv[1]); 
		Original = argv[1];
	}

	if(argc <= 2 || argv[2] == NULL)
	{
		printf("복사된 파일 이름이 입력되지 않았습니다. \n");
		printf("'Duplication' 이름을 사용합니다.");
		Duplication = "Duplication";
	}
	
	else
	{
		printf("복사된 파일 이름을 입력받았습니다. \n");
		printf("'%s'이름을 사용합니다\n" , argv[2]);
		Duplication = argv[2];
	}

	in = open(Original , O_RDONLY);/* 복사 대상 파일을 읽기 전용으로 읽어들임 */
	out = open(Duplication , O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	if(in == -1 || out == -1)//in 과 out 중 하나라도 -1(파일이 존재하지 않는다면) 지시문 출력 후 프로그램 종료
	{
		printf("File open error\n");
		exit(1);
	}
  	
	printf("복사를 시작합니다.\n");
	
	start = clock();
	buffer = clock();
	while((nread = read(in , block , sizeof(block))) > 0)
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
     
	printf("\n");

	return(0);
}
