#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

int strtohexdec(char* str) {
    int value = (int)strtol(str, NULL, 0);
    if (value>4095) return -1;
    return value;
}

int main(int argc, char** argv) {
    if (argc!=2) {
        fprintf(stderr, "Usage ./sasm <file>");
        return 1;
    }
    FILE* fp;

    fp = fopen(argv[1], "r");
    if (fp==NULL) {
        fprintf(stderr, "Error while trying to read from file");
        return 1;
    }

    int counter = 0;
    char* line = NULL;
    size_t len = 0;
    char* delim = " \n";
    char* opcode;
    while ((getline(&line, &len, fp))!=-1) {
        opcode = strtok(line, delim);
        if (strcmp(opcode, "Load")==0) {
            printf("1");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "Store")==0) {
            printf("2");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "Add")==0) {
            printf("3");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "Subt")==0) {
            printf("4");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "Input")==0) {
            printf("5000");
        } else if (strcmp(opcode, "Output")==0) {
            printf("6000");
        } else if (strcmp(opcode, "Halt")==0) {
            printf("7000");
        } else if (strcmp(opcode, "Skipcond")==0) {
            printf("8");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "Jump")==0) {
            printf("9");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "Clear")==0) {
            printf("A000");
        } else if (strcmp(opcode, "AddI")==0) {
            printf("B");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "JumpI")==0) {
            printf("C");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "LoadI")==0) {
            printf("D");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else if (strcmp(opcode, "StoreI")==0) {
            printf("E");
            opcode = strtok(NULL, line);
            strtok(opcode, delim);
            printf("%03x", strtohexdec(opcode));
        } else {
            fprintf(stderr, "Error ar line %d: unexpected token \'%s\'\n", counter, opcode);
            return 1;
        }
        counter++;
    }
    fclose(fp);
    printf("\n");
    return 0;
}