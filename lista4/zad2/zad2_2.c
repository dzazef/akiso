#include <stdio.h>
#include <signal.h>

int main() {
    for (int i=0; i<65; i++) {
        kill(1, i);
    }
}
