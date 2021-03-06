#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) 
{
  FILE * src; 
  FILE * dst;
        
  int count = 0;
  int buff_size = 0; 
  int read_value = 0;
  char * buff; 
  clock_t program_start , iteration_end , program_end;	

  if (argc < 3)
  {
  	fprintf(stderr,"입력 오류.\n");
 	 return;
  }

  else if (argc == 3)
  {
 	 buff_size = 1024;
  }	
        
  else 
  {
 	 fprintf(stderr,"입력 오류.\n");
 	 return;
  }
       
  buff = (char*)calloc(buff_size, sizeof(char)); 
	
  src = fopen(argv[1],"r");
  dst = fopen(argv[2],"w");

  if(src == NULL || dst == NULL) 
  {
    fprintf(stderr, "파일 open 실패.\n");
    return;
  }

  program_start = clock();
	
  while((read_value = fread(buff,1,buff_size, src)) > 0 ) 
  {	
       		 fwrite(buff,1,read_value,dst);
		iteration_end = clock();
		
		if((iteration_end - program_start - count) > 0) 
		{
			printf("*");
		}
		count = iteration_end;
  }
	
  program_end = clock();	

  printf("\n수행 시간 : %d\n" , program_end -program_start);

  free(buff); 
  
  fclose(dst);
  fclose(src);
  exit(0);
}
