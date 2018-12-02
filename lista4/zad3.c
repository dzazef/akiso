#include <memory.h>
#include <stdio.h>
#include <values.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>

#define MAX 512
char* argv[MAX];
char line[MAX];

void clearLine(char** ptr) {
    memset(ptr, 0, MAX * (sizeof ptr[0]));
}

int divideByChar(char* ptrline, char** ptrargv, char* separator) {
    char* token;
    int i=0;
    for (token = strtok(ptrline, separator); token; token = strtok(NULL, separator)) {
        ptrargv[i++]=token;
    }
    return i;
}

void readLine (char** ptrargv, char* ptrline) {
    clearLine(ptrargv);
    char dir[MAX];
    char host[MAX];
    gethostname(host, sizeof(host));
    getcwd(dir, sizeof(dir));
    printf("\033[36;1m%s:\033[34;1m%s\033[0m$ ", host, dir);
    if (fgets(ptrline, MAX, stdin)==NULL) printf("EOF\n");
    strncpy(strstr(ptrline, "\n"), "\0", 2);
}

void execute(char** ptr, int ampersand) {
    int i;
    i = fork();
    if (i==0) {
        if (ampersand) printf("Process created with PID: %d", getpid());
        execvp(ptr[0], ptr);
        kill(getpid(), 9);
    }
    else {
        if (!ampersand) wait(&i);
    }
}

int checkCharReplace(char *ptr, char *ch) {
    if (strstr(ptr, ch)) {
        strncpy(strstr(ptr, ch), " ", 1);
        return 1;
    }
    return 0;
}

int checkChar(char *ptr, char ch) {
    int count = 0;
    int length = (int) strlen(ptr);
    for (int i = 0; i < length; i++) {
        if (ptr[i]==ch) {
            count++;
        }
    }
    return count;
}

int checkValues(int* ptr, int limit) {
    int result = 1;
    for (int i=0; i<limit; i++) {
        if (ptr[i]!=0) result=0;
    }
    return result;
}

void Piping(char* ptrline, int cmdcount, int ampersandFound) {
    int outfound = checkChar(line, '>');
    int infound = checkChar(line, '<');
    char* divideBySpace[MAX];
    int j = divideByChar(ptrline, divideBySpace, " ");
    char* cmd[MAX][MAX]; int k=0; int p=0;
    for (int i=0; i<j; i++) {
        if (strcmp(divideBySpace[i], "|")==0 || strcmp(divideBySpace[i], ">")==0 || strcmp(divideBySpace[i], "<")==0) {
            p=0;
            k++;
            continue;
        }
        cmd[k][p++] = divideBySpace[i];
    }
    int fd[2];
    pipe(fd);
    int pid2;
    int pid = fork();
    if (pid==0) pid2=fork();

    if(pid==0 && pid2==0) {
        if (dup2(fd[1], 1)<0) {
            perror("fd error");
            exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        execvp(cmd[0][0], cmd[0]);
        perror("blad");
        exit(1);
    } else if (pid==0) {
        if (dup2(fd[0], 0)<0) {
            perror("fd error");
            exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        execvp(cmd[1][0], cmd[1]);
        perror("blad");
        exit(1);
    } else {
        close(fd[0]);
        close(fd[1]);
        wait(&pid);
        wait(&pid2);
    }
}

int main() {
    signal(SIGCHLD, SIG_IGN);
    int ampersandFound;
    int countPipes;
    char linetemp[1024];
    while(1) {
        readLine(argv, line);
        strcpy(linetemp, line);
        if (strlen(line)==0) continue;
        countPipes=checkChar(line, '|');
        ampersandFound= checkCharReplace(line, "&");
        divideByChar(line, argv, " ");
        if (strcmp("cd", argv[0])==0) {if (chdir(argv[1]) != 0) printf("Nieznaleziono ścieżki\n");}
        else if (strcmp("exit", argv[0])==0)  exit(0);
        else {
            if (countPipes==0) execute(argv, ampersandFound);
            else {
                Piping(linetemp, countPipes+1, ampersandFound);
            }
        }
    }
}
