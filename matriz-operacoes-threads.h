#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include "matriz.h"

typedef struct{
	int tid, threads, N;
}param_t;

int **mat_a;
int **mat_b;
int **mat_cThread;
int **mat_cThreadBlock;

void *multiply(void *arg);
void *multiplyBlock(void *arg);
