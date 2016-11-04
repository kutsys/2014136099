//High-level 파일함수를 사용하여 파일복사 프로그램을 작성한다
//파일을 복사하는 동안 low-level과 같은 방식으로 *을 출력한다.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) 
{
        //파일 포인터 선언
	FILE * src; 
        FILE * dst;
        
	int count = 0;
	int buff_size = 0; 
        int read_value = 0;
        char * buff; 

	clock_t program_start , iteration_end , program_end;	

        if (argc < 3)//입력이 3개 미만 -> 실행 파일, 피복사 파일만 입력
	{
    		fprintf(stderr,"입력 오류.\n");
		//fprintf(FILE *fp , const char *format , ...)
		// 	 (입출력에 이용될 파일 ,입출력 될 문자열 , 입출력될 변수 목록)
    		//stderr :  표준 오류 - 오류 메세지나 진단을 출력하기 위한 출력 스트림	 
	      	return;
		//프로그램 종료
	}

        else if (argc == 3)//입력이 3개 -> 실행 파일, 피복사 파일 , 복사 파일(write 대상 파일) 입력
	{
                buff_size = 64;
	}	
       
	else if (argc == 4)
	{
                buff_size = atoi(argv[3]);
	} 
       
	else//4개 이상의 입력에 대해서는 프로그램 종료로 예외처리 
	{
                fprintf(stderr,"입력 오류.\n");
                return;
        }
       
	buff = (char*)calloc(buff_size, sizeof(char)); 
	//buff 변수 0으로 동적 메모리 할당
	//calloc(size_t n , size_t size)
	//size_t n : 항목의 개수 
	//size_t size : 항목의 크기

        src = fopen(argv[1],"r");//argv[1]으로 받은 file이름과 동일한 파일을 '읽기 모드'로 연다.
        dst = fopen(argv[2],"w");//argv[2]으로 받은 file이름과 동일한 파일을 '쓰기 모드'로 연다.


	//만약 src 혹은 dst 가 NULL 이면 프로그램 종료
        if(src == NULL || dst == NULL) 
	{
                fprintf(stderr, "파일 open 실패.\n");
                return;
        }

 	program_start = clock();
	
        while((read_value = fread(buff,1,buff_size, src)) > 0 ) 
        //fread(void *ptr , size_t size , size_t nitems , FILE *stream)
	//void *ptr : 파일 내용을 읽어들일 메모리 포인터 
	//size_t size : 데이터 하나의 크기
	//size_t nitems : 읽어 들일 데이터의 크기
	//FILE *stream : 대상 파일 스트림)
	//반환 : size_t : 읽어 들인 데이터 개수를 반환하며, 오류가 발생하면 -1을 반환	
	{	
       		 fwrite(buff,1,read_value,dst);
		//fwrite(void *ptr , size_t size , size_t nitems, FILE *stream);
		//void *ptr : 파일에 출력할 내용을 갖고있는 메모리 포인터
		//size_t size : 데이터 하나의 크기
		//size_t nitems : 파일에 출력할 데이터의 개수
		//FILE *stream : 대상 파일 스트림
		//반환 : int : 출력한 데이터의 개수를 반환하며, 오류가 발생하면 -1을 반환 
		
		iteration_end = clock();
		
		if((iteration_end - program_start - count) > 1)
		{
			printf("%d" , iteration_end - program_start - count);
			printf("*");
		}
		count = iteration_end;
	}
	
	printf("\n수행 시간 : %d\n" , program_end -program_start);

 	free(buff); //buff 변수의 메모리 할당 해제
       
	//fopen으로 열었던 파일들 닫아준다.
	fclose(dst);
        fclose(src);
        exit(0);
}

