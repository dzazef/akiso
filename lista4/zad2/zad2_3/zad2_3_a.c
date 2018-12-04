#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int count = 0;

void handle() {
    count++;
}

int main() {
    printf("My PID: %d\n", getpid());
    printf("Creating handlers for all signals...\n");
    signal(SIGUSR1, handle);
    getchar();
    printf("Numbers of signal received: %d\n", count);
    return 0;
}
