#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle(int signal) {
    printf("Catched signal no. %d\n", signal);
}

int main() {
    printf("My PID: %d\n", getpid());
    printf("Creating handlers for all signals...\n");
	for (int i=1; i<65; i++) {
        signal(i, handle);
    }
    printf("Test: Sending SIGINT(2) to %d\n", getpid());
    kill(getpid(), 2);
    
    printf("Test: Sending SIGKILL(9) to %d\n", getpid());
    kill(getpid(), 9);
    return 0;    
}
