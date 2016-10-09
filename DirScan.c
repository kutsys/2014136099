#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir , int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL)
	//opendir(열기 대상 디렉토리):
	//열기 성공 -> 디렉토리 정보 구조체(DIR)반환
	//열기 실패 -> NULL 반환	
	{
		fprintf(stderr , " cannot open directory: %s\n", dir);
		return;
		//NULL 반환 받은 경우 에러 메세지 출력 후 프로그램 종료
	}
	
	chdir(dir);//dir변수에 저장된 디렉토리로 현재 디렉토리를 변경
	//현재 디렉토리를 path가 지정한 곳으로 바꾼다
 
	while((entry = readdir(dp)) != NULL)
	//readdir : 디렉토리 항목을 읽음. 항목을 다 읽거나 에러인 경우 NULL을 반환
	//dir가 가리키는 디렉토리 내 파일 목록의 주소를 반환 후 다음 파일 목록을 가리킴.
	//while()문을 이용해 readdir()함수를 NULL을 반환 받을 때 까지 반복 구동한다.  
	{
		lstat(entry->d_name , &statbuf);
		//entry에 저장된 디렉토리 이름을 statbuf에 저장 <-- 1
		if(S_ISDIR(statbuf.st_mode))
		//statbuf의 모드 값 검사 -> 디렉토리일 경우 
		{
			if(strcmp("." , entry->d_name) == 0 || strcmp(".." , entry->d_name) == 0) 
			//문자열이 "." 혹은 ".." 여부 검사
				continue;
				if(entry->d_name[0] == '.') 
				//.으로 시작하는  Hidden 파일인 경우				
				{
					continue;
				//다음 반복문 구동
				}				
				//조건 충족 시 다음 entry에 저장된 디렉토리 등록( <-- 1 다시 실행)
			printf("%*s%s/n" , depth, "" ,entry->d_name);
			//출력 : depth , 디렉토리 이름		
		}			
		else
		{ 
			if(entry->d_name[0] == '.') 
			//.으로 시작하는  Hidden 파일인 경우
			{
				continue;
			//다음 반복문 구동
			}
			printf("%*s%s\n", depth, "", entry->d_name);
			//출력 : depth , 디렉토리 이
		}		
		//일반 파일인 경우 depth와 파일 이름 출력
	}
	chdir("..");//이전 디렉토리로 이동 
	closedir(dp);
	//closedir() : opendir()으로 열린 디렉토리를 닫아주는 역할
}			
	

int main()
{
	printf("Directory scan : present directory :\n");
	printdir("." , 0); //현재 디렉토리를 대상으로 printdir 함수 호출
	printf("done.\n");
	exit(0);//종료
}
