#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>



char* timeToString(struct tm *t);

void test_funct();

void main()
{	
	int count;
	int i;
	int r;
	
	srand(time(NULL));
	
	printf("현재 PID 출력 프로그램. 호출 횟수 입력 : \n");
	scanf("%d", &count);	


	for( i = 0; i < count; i++)
	{
		r = rand()%10;		
		sleep(r);	
		test_funct();
	}
}


char* timeToString(struct tm *t)
{
	static char s[20];
	
	sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
	    t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);

	return s;
}

void test_funct()
{
	static int count;

	struct tm *t;
	time_t timer;
	
	count++;	

	timer = time(NULL);
	t = localtime(&timer);
	
	printf("PID : [%d] Current Time : [%s] Funct count : [%d]\n", getpid(),timeToString(t),count);
}
