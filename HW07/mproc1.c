#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>

#define PROCESS_COUNT 10

char *PATH = {"/home/heongyu/SysPro/HW07/subproc"};

void main()
{	
	int i;
	pid_t pid[PROCESS_COUNT];
	
	printf("2014136099 이헌규\n");
	
	printf("자식 프로세스를 생성합니다.");
	
	for(i = 0; i < PROCESS_COUNT; i++)
	{
		pid[i] = fork();
		
		if(pid[i] == -1)	
		{
			perror("fork error - program exit");
			exit(0);
		}	
			
		else if(pid[i] == 0)
		{
			printf("자식 프로세스 생성 : %d\n" , getpid());
			execl(PATH , "SUBPROC" , NULL);	
		}
		else
		{
		}	
		
	}
	
	for(i = 0 ; i < PROCESS_COUNT; i++ ) 
	{
		wait(&pid[i]);
	}
}
