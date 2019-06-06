#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int multiplicarOmp (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M);
void multiplicaBlocoOMP(int size, int n, int **A, int **B, int **C, int TILE);
