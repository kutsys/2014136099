#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

int main(int argc , char *argv[])
{
	char block[1024];
	char *Original;
	char *Duplication;
	int in , out;
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

	in = open(Original , O_RDONLY);
	out = open(Duplication , O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	if(in == -1 || out == -1)
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
