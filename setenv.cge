//setenv()함수를 사용하여 $TEST_ENV라는 환경변수를 정의하고 그 값을 1234로 설정하고, 설정된 값을 bash에서 확인한다.

#include <stdio.h>
#include <stdlib.h>

/*
int setenv(const char *envname , const char *envval, int overwrite)
char *envname : 환경변수 이름
char *envval : 변수 값
char *overwrite : 이미 같은 이름의 변수가 있다면 값을 변경할지의 여부

반환 : int : 성공하면 0 , 실패하면 -1

*/

void main()
{
	printf("setenv 실행파일 입니다.\n");
	setenv("TEST_ENV", "1234" , 0);
	printf("$TEST_ENV : %s\n" , getenv("TEST_ENV"));
}
