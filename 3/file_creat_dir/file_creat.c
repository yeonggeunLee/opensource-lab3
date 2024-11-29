#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    char *buf = "파일 생성 테스트.";
    ssize_t cnt;
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    
    if(argc < 2) {
        fprintf(stderr, "사용법 : file_creat filename\n");
        exit(1);
    }
    
    if( (fd = open(argv[1], flags, mode)) == -1) {
        perror("open");
        exit(1);
    }
    
    cnt = write(fd, buf, strlen(buf));
    printf("write count = %ld\n", cnt);
    close(fd);
}
