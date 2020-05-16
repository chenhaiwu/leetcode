#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>


#define MAXNUM 101

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize)
{
    int ret = 0;
    int m = obstacleGridSize;
    if (m == 0) {
        return ret;
    }
    int n = obstacleGridColSize[0];
    if (obstacleGrid[0][0] == 1) {
        return ret;
    }
    long long dp[MAXNUM][MAXNUM] = {0};
    dp[0][0] = 1;
    // printf("m=%d, n=%d\n", m, n);
    for (int i = 1; i < m; i++) {
        if (obstacleGrid[i][0] == 0 && dp[i - 1][0] == 1) {
            dp[i][0] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        if (obstacleGrid[0][i] == 0 && dp[0][i - 1] == 1) {
            dp[0][i] = 1;
        }
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[i][j] == 1) {
                continue;
            }
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    /*
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
    */
    
    return (int)dp[m - 1][n - 1];
}

int main()
{

}