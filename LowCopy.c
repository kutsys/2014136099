#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
        FILE * src; 
        FILE * dst;
        int buff_size = 0; 
        int read_value = 0;
        char * buff; 
        if (argc < 3) {
                fprintf(stderr,"argument is wrong, check your command\n");
                exit(1);
        }
        else if (argc == 3)
                buff_size = 64;
        else if (argc == 4)
                buff_size = atoi(argv[3]); 
        else {
                fprintf(stderr,"argument is wrong, check you cmmand.\n");
                exit(1);
        }
        buff = (char*)calloc(buff_size, sizeof(char)); 

        src = fopen(argv[1],"r");//피복사 파일, 새파일의 FILE open
        dst = fopen(argv[2],"w");

        if(src == NULL || dst == NULL) {
                fprintf(stderr, "file open failed\n");
                exit(1);
        }

        while((read_value = fread(buff,1,buff_size, src)) > 0 ) 
                fwrite(buff,1,read_value,dst);

        free(buff); 
        fclose(dst);
        fclose(src);
        exit(0);
}
