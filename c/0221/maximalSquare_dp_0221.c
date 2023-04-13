#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

int FuncMin(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

#define MAX_LEN 5001

int g_dp1[MAX_LEN][MAX_LEN];

// #define DEGUG_CHW
void PrintMatrix(int dp, int gridSize, int colSize)
{
#ifdef DEGUG_CHW
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < colSize; col++) {
            if (dp == 1) printf("%d ", g_dp1[row][col]);
        }
        printf("\n");
    }
    printf("ddd\n");
#endif
}

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize)
{
    if (matrixSize == 0) return 0;
    for (int i = 0; i <= matrixSize; i++) {
        for (int j = 0; j <= matrixColSize[0]; j++) {
            if (i == 0 || j == 0) {
                g_dp1[i][j] = 0;
                continue;
            }
            if (matrix[i - 1][j - 1] == '1') {
                g_dp1[i][j] = 1;
            } else {
                g_dp1[i][j] = 0;
            }
        }
    }
    PrintMatrix(1, matrixSize, matrixColSize[0]);
    int ans = 0;
    for (int i = 1; i <= matrixSize; i++) {
        for (int j = 1; j <= matrixColSize[0]; j++) {
            if (g_dp1[i][j] == 0) continue;
            g_dp1[i][j] = FuncMin(g_dp1[i - 1][j - 1], FuncMin(g_dp1[i - 1][j], g_dp1[i][j - 1])) +1;
            if (g_dp1[i][j] > ans) {
                ans = g_dp1[i][j];
            }
        }
    }
    PrintMatrix(1, matrixSize, matrixColSize[0]);
    return ans * ans;
}
