#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <netdb.h>
#include <unistd.h>

int client_count = 0;
typedef struct {
    int fd;
    char* id;
    int id_is_set;
} client;
client* client_list;

int find_descriptor_by_username(const char* user) ;

int get_client_number_by_descriptor(int fd1) ;

int main(int argc, char** argv) {
    //checking parameters
    if (argc!=3) {
        perror("Użycie: telnet_server hostname port [number_of_clients]");
        exit(1);
    }
    //creating socket
    struct sockaddr_in sn;
    bzero((char*)&sn, sizeof(sn));
    struct hostent* he;
    if (!(he = gethostbyname(argv[1]))) {
        fprintf(stderr, "gethostbyname()");
        exit(1);
    }
    sn.sin_family = AF_INET;
    sn.sin_port = htons((unsigned short)atoi(argv[2]));
    sn.sin_addr = *(struct in_addr *)(he->h_addr_list[0]);
    int s; if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) exit(2);
    if (bind(s, (struct sockaddr *)&sn, sizeof(sn)) == -1) {
        perror("bind error");
        exit(3);
    }
    listen(s, SOMAXCONN);

    client_list = malloc(SOMAXCONN * sizeof(client));

    fd_set copy_fd_set, master_fd_set;
    FD_ZERO(&master_fd_set);
    FD_SET(s, &master_fd_set);
    int server_running = 1;
    while(server_running) {
        memcpy(&copy_fd_set, &master_fd_set, sizeof(fd_set));
        select(FD_SETSIZE, &copy_fd_set, NULL, NULL, NULL);
        for (int fd=0; fd<FD_SETSIZE; fd++) {
            if (FD_ISSET(fd, &copy_fd_set)) {
                if (fd == s) {
                    socklen_t l;
                    listen(s, 1);
                    int new_conn = accept(s, (struct sockaddr *) &sn, &l);
                    char* hello = "Hello! Here are all users connected: \n";
                    send(new_conn, hello, strlen(hello), 0);
                    for (int i = 0; i < client_count; i++) {
                        send(new_conn, client_list[i].id, sizeof(client_list[i].id), 0);
                        send(new_conn, "\n", sizeof(char), 0);
                    }
                    char* login = "Set up your login now: ";
                    send(new_conn, login, strlen(login), 0);
                    FD_SET(new_conn, &master_fd_set);
                    client_list[client_count].fd = new_conn;
                    client_list[client_count].id_is_set = 0;
                    client_count++;
                } else {
                    int user_count = get_client_number_by_descriptor(fd);
                    if(client_list[user_count].id_is_set) {
                        char *buff = malloc(4096 * sizeof(char));
                        ssize_t mess_length = recv(fd, buff, 4096, 0);
                        if (mess_length < 0) {
                            close(fd);
                            FD_CLR(fd, &master_fd_set);
                        } else {
                            char *user = malloc(4096 * sizeof(char));
                            char *message = malloc(4096 * sizeof(char));
                            int was_space_found = 0;
                            int t1 = 0;
                            int t2 = 0;
                            for (int i = 0; i < strlen(buff); i++) {
                                if (buff[i] == ' ' && was_space_found == 0) {
                                    was_space_found = 1;
                                    continue;
                                }
                                if (was_space_found) message[t1++] = buff[i];
                                else if (buff[i]!='\0' && buff[i]!='\n') user[t2++] = buff[i];
                            }
                            int user_fd = find_descriptor_by_username(user);
                            if (user_fd < 1)
                                fprintf(stderr, "wrong username: %s-%d\n", user, user_fd);
                            else
                                send(find_descriptor_by_username(user), message, 4096, 0);
                        }
                    } else {
                        char *buff = malloc(4096 * sizeof(char));
                        ssize_t mess_length = recv(fd, buff, 4096, 0);
                        if (mess_length < 0) {
                            close(fd);
                            FD_CLR(fd, &master_fd_set);
                        } else {
                            char* id_temp = malloc(4096* sizeof(char));
                            for (int i=0; i<strlen(buff); i++) {
                                if (buff[i]!='\n' && buff[i]!='\0')
                                    id_temp[i] = buff[i];
                            }
                            client_list[user_count].id = id_temp;
                            client_list[user_count].id_is_set = 1;
                        }
                    }
                }
            }
        }
    }
}

int mystrcmp(const char* s1, const char* s2) {
    int result = 1;
    for (int i=0; i<strlen(s2); i++) {
        if (s1[i]!=s2[i] && s1[i]!='\n' && s2[i]!='\n' && s1[i]!='\0' && s2[i]!='\0') result=0;
    }
    return result;
}

int get_client_number_by_descriptor(int fd1) {
    for (int i=0; i<client_count; i++) {
        if (client_list[i].fd == fd1)
            return i;
    }
    return -1;
}

int find_descriptor_by_username(const char* user) {
    for (int i=0; i<client_count; i++) {
        if (mystrcmp(client_list[i].id, user)==1)
            return client_list[i].fd;
    }
    return -1;
}