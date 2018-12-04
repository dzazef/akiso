#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int pid;
    printf("Waiting for PID: ");
    scanf("%d", &pid);
    printf("\nSending signal SIGUSR(10) 100000 times to %d", pid);
    for (int i=0; i<1000; i++) {
        kill(pid, SIGUSR1);
    }
    return 0;
}
