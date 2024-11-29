#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 1024
#define SEM_KEY 1234
#define SHM_KEY 5678

void sem_op(int semid, int semnum, int op) {
    struct sembuf sb;
    sb.sem_num = semnum;
    sb.sem_op = op;
    sb.sem_flg = 0;
    if (semop(semid, &sb, 1) == -1) {
        perror("semop");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(1);
    }

    const char *source_file = argv[1];
    const char *destination_file = argv[2];

    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shm_addr = (char *)shmat(shmid, NULL, 0);
    if (shm_addr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    int semid = semget(SEM_KEY, 2, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // 세마포어 초기화
    semctl(semid, 0, SETVAL, 1);
    semctl(semid, 1, SETVAL, 0);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        FILE *dest = fopen(destination_file, "w");
        if (!dest) {
            perror("fopen");
            exit(1);
        }

        while (1) {
            sem_op(semid, 1, -1);

            if (strcmp(shm_addr, "EOF") == 0) {
                break;
            }

            fprintf(dest, "%s", shm_addr);
            sem_op(semid, 0, 1);
        }

        fclose(dest);
        printf("Child: File copy completed.\n");
        exit(0);
    } else {
        FILE *src = fopen(source_file, "r");
        if (!src) {
            perror("fopen");
            exit(1);
        }

        while (fgets(shm_addr, SHM_SIZE, src)) {
            sem_op(semid, 0, -1);
            sem_op(semid, 1, 1);
        }

        sem_op(semid, 0, -1);
        strcpy(shm_addr, "EOF");
        sem_op(semid, 1, 1);

        fclose(src);
        wait(NULL);
    }

    shmdt(shm_addr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    printf("Parent: File copy completed.\n");
    return 0;
}

