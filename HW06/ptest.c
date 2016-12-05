#include <stdio.h>
#include <time.h>

int main (void) 
{
    char buff[100];
    time_t now = time (0);
	
    	while(1)
	{
    		now = time(0);
		strftime (buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime (&now));	
  		printf ("%s\n", buff);
		sleep(2);
		fflush(stdout);
	}

    return 0;
}

  //size_t strftime(char *restrict s , size_t maxsize , const char *restrict format, const struct tm *restrict timeptr);
    //char *restrict s : 문자열을 받을 버퍼 포인터
    //size_t maxsize : 버퍼의 크기
    //const char *restrict format : 날자와 시간 정보를 나열하기 위한 문자열 포맷
    //const struct tm *restrict timeptr : 날짜와 시간 정보
    //반환 : size_t : 문자열 길이
