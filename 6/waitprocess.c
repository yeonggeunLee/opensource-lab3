#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status, exit_status;
    
    if ((pid = fork()) < 0)
        perror ("fork 실패");
    if (pid == 0) {
        sleep(4);
        exit(5);
    }

    if ((pid = wait(&status)) == -1) {
        perror("wait 실패");
        exit(2);
    }
    if (WIFEXITED(status)) {
        exit_status = WEXITSTATUS(status);
        printf("Exit status from %d was %d\n", pid, exit_status);
    }
    exit(0);    
}
