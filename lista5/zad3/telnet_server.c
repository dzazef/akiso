#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "socketlib.h"

ssize_t n;
char *buf[1024];

int main(int argc, char** argv) {
    fd_set fdset, masterfdset;
    char* hostname;
    int port, sock;
    int clientcount;

    if (argc!=4) {
        fprintf(stderr, "Użycie: telnet_server hostname port number_of_clients");
        exit(1);
    }
    hostname = argv[1];
    port = atoi(argv[2]);
    clientcount = atoi(argv[3]);
    sock = server_tcp_socket(hostname, port);
    int fdtab[clientcount];
    FD_ZERO(&masterfdset);
    FD_SET(1, &masterfdset);
    fdtab[0]=1;
    clientcount++;
    for (int i=1; i<clientcount; i++) {
        fdtab[i] = accept_tcp_connection(sock);
        fprintf(stderr, "Client %d connected, sending \"Choose id\" prompt\n", i);
        FD_SET(fdtab[i], &masterfdset);
        write(fdtab[i], "Choose your id: ", 100);
    }
    fprintf(stderr, "going to loop\n");
    while(1) {
        memcpy(&fdset, &masterfdset, sizeof(fd_set));
        if (select(fdtab[clientcount-1]+1, &fdset, NULL, NULL, NULL) < 0) {
            perror("on select");
            exit(1);
        }
        for (int i=0; i<clientcount; i++) {
            if(FD_ISSET(fdtab[i], &fdset)) {
                if (fdtab[i]==1) n = read(0, buf, 100);
                else n = read(fdtab[i], buf, 100);
                if (n==0) {
                    for (int j = 0; j < clientcount; j++) {
                        close(fdtab[j]);
                    }
                    exit(1);
                } else {
                    for (int k=0; k<clientcount; k++) {
                        if (fdtab[i]!=fdtab[k]) write(fdtab[k], buf, n);
                    }
                }
            }
        }
    }
}
