#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


int **ma, **mb, **mc;
int *idx;
int size;
int thread_count;
clock_t begin, end;
double s;

void create_alloc_fill_matrixes() {
    time_t t;
    ma = malloc(size * sizeof(int*));
    mb = malloc(size * sizeof(int*));
    mc = malloc(size * sizeof(int*));
    for (int i=0; i<size; i++) {
        ma[i] = malloc(size * sizeof(int));
        mb[i] = malloc(size * sizeof(int));
        mc[i] = malloc(size * sizeof(int));
    }
    srand((unsigned) time(&t));
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            ma[i][j] = rand()%2;
            mb[i][j] = rand()%2;
        }
    }
}

void create_alloc_reset_index() {
    idx = malloc(size * sizeof(int));
    for (int i=0; i<size; i++) {
        idx[i] = 0;
    }
}

void reset_result_matrix() {
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++) {
            mc[i][j] = 0;
        }
}

void* multithread_multiply() {
	begin = clock();
    for (int i=0; i<size; i++) {
        if (idx[i]==0) {
            idx[i]=1;
            for (int j = 0; j < size; j++)
                for (int k = 0; k < size; k++) {
                    mc[i][j] = mc[i][j] || (ma[i][k] && mb[k][j]);
                    if (mc[i][j]) break;
                }
        }
    }
    end=clock();
    s= (double) (end - begin) / CLOCKS_PER_SEC;
    return NULL;
}

void print_matrixes() {
    int s = (size>5 ? 5 : size);
    printf("Matrix A: \n");
    for(int i=0; i<s; i++) {
        for(int j=0; j<s; j++) {
            printf("%d ", ma[i][j]);
        }
        printf("\n");
    }
    printf("Matrix B: \n");
    for(int i=0; i<s; i++) {
        for(int j=0; j<s; j++) {
            printf("%d ", mb[i][j]);
        }
        printf("\n");
    }
    for(int i=0; i<s; i++) {
        for(int j=0; j<s; j++) {
            printf("%d ", mc[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    if (argc!=3) {
        fprintf(stderr, "Wrong parameters. Try again.");
    }
    size = atoi(argv[1]);
    thread_count = atoi(argv[2]);
    create_alloc_fill_matrixes();
    create_alloc_reset_index();
    reset_result_matrix();

    pthread_t thread_index_arr[thread_count];
    for (int i=0; i<thread_count; i++)
        pthread_create(&thread_index_arr[i], NULL, multithread_multiply, NULL);

    int done = 0;
    while (done==0) {
        done = 1;
        for (int i=0; i<size; i++) {
            if(idx[i]==0) done = 0;
        }
    }

	printf("timer: %fs\n", s);
    //print_matrixes();
}

