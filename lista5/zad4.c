#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LIMIT 5

int **ma, **mb, **mc, **temp;
int size;
clock_t begin, end;

void createMatrixes() {
    time_t t;
    ma = malloc(size * sizeof(int*));
    mb = malloc(size * sizeof(int*));
    mc = malloc(size * sizeof(int*));
    temp = malloc(size * sizeof(int*));
    for (int i=0; i<size; i++) {
        ma[i] = malloc(size * sizeof(int));
        mb[i] = malloc(size * sizeof(int));
        mc[i] = malloc(size * sizeof(int));
        temp[i] = malloc(size * sizeof(int));
    }
    srand((unsigned) time(&t));
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            ma[i][j] = rand()%LIMIT;
            mb[i][j] = rand()%LIMIT;
        }
    }
}

double multiply() {
    begin = clock();
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++) {
                mc[i][j] += ma[i][k] * mb[k][j];
            }

    end = clock();
    return (double)(end - begin)/CLOCKS_PER_SEC;
}

double multiply_with_transponse() {
    begin = clock();
    //transponse
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp[j][i] = mb[i][j];
        }
    }
    //multiply
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                mc[i][j] += ma[i][k] * temp[j][k];
            }
        }
    }
    end = clock();
    return (double) (end - begin) / CLOCKS_PER_SEC;
}

void print() {
    for (int i=0; i<size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %d ", mc[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void reset_result_matrix() {
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++) {
            mc[i][j] = 0;
            temp[i][j] = 0;
        }
}

int main(int argc, char** argv)
{
    if (argc<1) {
    	fprintf(stderr, "Uncorrect parameters\n");
    	exit(1);
    }
    size = atoi(argv[1]);

    createMatrixes();
    reset_result_matrix();
    printf("normal multiply: %fs\n", multiply());
    reset_result_matrix();
    printf("multiply with transponse: %fs\n", multiply_with_transponse());

    return 0;
}

