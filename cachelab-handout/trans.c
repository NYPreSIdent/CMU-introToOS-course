/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    int blockRow, blockColumn, iterateNum;
    int temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;

    // We divide it into 8x8 blocks, so all the block rows or columns can be fit into the cache cause we
    // have 32 sets.
    if (N == 32 && M == 32) {
        for (blockRow = 0; blockRow < 4; blockRow++) {
            for (blockColumn = 0; blockColumn < 4; blockColumn++) {
                for (iterateNum = 0; iterateNum < 8; iterateNum++) {
                    temp1 = A[blockRow * 8][blockColumn * 8 + iterateNum];
                    temp2 = A[blockRow * 8 + 1][blockColumn * 8 + iterateNum];
                    temp3 = A[blockRow * 8 + 2][blockColumn * 8 + iterateNum];
                    temp4 = A[blockRow * 8 + 3][blockColumn * 8 + iterateNum];
                    temp5 = A[blockRow * 8 + 4][blockColumn * 8 + iterateNum];
                    temp6 = A[blockRow * 8 + 5][blockColumn * 8 + iterateNum];
                    temp7 = A[blockRow * 8 + 6][blockColumn * 8 + iterateNum];
                    temp8 = A[blockRow * 8 + 7][blockColumn * 8 + iterateNum];

                    B[blockColumn * 8 + iterateNum][blockRow * 8] = temp1;
                    B[blockColumn * 8 + iterateNum][blockRow * 8 + 1] = temp2;
                    B[blockColumn * 8 + iterateNum][blockRow * 8 + 2] = temp3;
                    B[blockColumn * 8 + iterateNum][blockRow * 8 + 3] = temp4;
                    B[blockColumn * 8 + iterateNum][blockRow * 8 + 4] = temp5;
                    B[blockColumn * 8 + iterateNum][blockRow * 8 + 5] = temp6;
                    B[blockColumn * 8 + iterateNum][blockRow * 8 + 6] = temp7;
                    B[blockColumn * 8 + iterateNum][blockRow * 8 + 7] = temp8;
                }
            }
        }
    }

}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

