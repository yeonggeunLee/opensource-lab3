#include <stdio.h>
#include <stdlib.h>

void exitfunc1(void);
void exitfunc2(void);

int main() {
    atexit(exitfunc1);
    atexit(exitfunc2);
    printf("메인 함수.\n");
}

void exitfunc1(void) {
    printf("종료 함수 1.\n");
}

void exitfunc2(void) {
    printf("종료 함수 2.\n");
}
