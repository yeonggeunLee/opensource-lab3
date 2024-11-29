#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void execute_command(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
        printf("%s completed\n", argv[1]);
        exit(EXIT_SUCCESS);
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    execute_command(argc, argv);
    return 0;
}
