#include <stdio.h>
#include <malloc.h>
#include <memory.h>

int main(int argc, char** argv) {
    if (argc!=2) {
        fprintf(stderr, "Użycie ./marie <plik>");
        return 1;
    }
    FILE* fp;

    fp = fopen(argv[1], "r");
    if (fp==NULL) {
        fprintf(stderr, "Błąd czytania pliku");
        return 1;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char* delim = " ";
    char* opcode;
    while ((read = getline(&line, &len, fp))!=-1) {
        opcode = strtok(line, delim);
        printf("%s\n", opcode);
        //switch case
    }
    fclose(fp);
    return 0;
}