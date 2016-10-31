//lect3.c(low level copy)
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv) {
        int src_fd = -1, dst_fd = -1; //복사될 파일과 생성될 파일의 File descriptor
        int read_value = 0;
        char* buff; //임시 버퍼
        int buf_size = 0; //버퍼사이즈를 저장하는 변수
        if (argc < 3 || argc > 4) {
                fprintf(stderr,"argument is wrong, check your command\n");
                exit(1);
        }
        else if(argc == 4) {
                buf_size = atoi(argv[3]);
        }//arg로 복사될 파일, 새 파일명 버퍼 사이즈를 지정
        buff = (char*)calloc(buf_size,sizeof(char)); //버퍼 메모리 동적할당
        src_fd = open(argv[1], O_RDONLY); //복사할 파일 오픈
        dst_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);//새 파일 오픈

        if(src_fd == -1 || dst_fd == -1) { //오픈 실패시 에러 처리
                fprintf(stderr, "file open failed\n");
                exit(1);
        }

        while((read_value = read(src_fd,buff,buf_size)) > 0 ) //버퍼 사이즈 만큼 읽고 새 파일에 씀
                write(dst_fd,buff,read_value);

        close(src_fd);
        close(dst_fd);
        free(buff);
        exit(0);
