#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
    pid_t pid;
    
    printf("fork 호출\n");
    pid = fork();
    if (pid == 0)
        printf("자식 프로세스\n");
    else if (pid > 0)
        printf("부모 프로세스\n");
    else
        printf("fork 실패\n");
}
