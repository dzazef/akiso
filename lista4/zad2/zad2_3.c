#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int count;

void handle(int signal) {
    //printf("Catched signal no. %d\n", signal);
    count++;
}

int main() {
    printf("My PID: %d\n", getpid());
    printf("Creating handlers for all signals...\n");
    for (int i=1; i<65; i++) {
        signal(i, handle);
    }
    printf("Sending signal SIGUSR(10) 100000 times to %d\n", getpid());
    for (int i=0; i<100000; i++) {
        kill(getpid(), SIGUSR1);
    }
    printf("Numbers of signal received: %d\n", count);
    return 0;
}
