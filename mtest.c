//InBoo, InFoo, InBar 함수를 호출합니다.

#include <stdio.h>

int InFoo();
int InBoo();
int InBar();

void main()
{
	printf("mtest 함수입니다.\n");
	printf("함수를 호출합니다.\n");
	
	InBoo();
	InFoo();
	InBar();
}
