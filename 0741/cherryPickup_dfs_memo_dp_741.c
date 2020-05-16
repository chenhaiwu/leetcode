/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

// #include "securec.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX_N 51
#define MIN_VAL (-5000)
int g_memo[MAX_N][MAX_N][MAX_N];
int g_n;

int Step(int** grid, int i1, int j1, int i2)
{
    int j2 = i1 + j1 - i2;
    if (i1 < 0 || j1 < 0 || i2 < 0 || j2 < 0) return -1;
    if (grid[i1][j1] < 0 || grid[i2][j2] < 0) return -1;
    if (i1 == 0 && j1 == 0) return grid[i1][j1];
    if (g_memo[i1][j1][i2] != MIN_VAL) return g_memo[i1][j1][i2];

    int ans1 = Step(grid, i1 - 1, j1, i2 - 1);
    int ans2 = Step(grid, i1 - 1, j1, i2);
    int ans3 = Step(grid, i1, j1 - 1, i2 - 1);
    int ans4 = Step(grid, i1, j1 - 1, i2);
    ans1 = MAX(ans1, ans2);
    ans3 = MAX(ans3, ans4);
    ans1 = MAX(ans1, ans3);
    if (ans1 < 0) {
        g_memo[i1][j1][i2] = -1;
        return -1;
    }
    ans1 += grid[i1][j1];
    if (i1 != i2) {
        ans1 += grid[i2][j2];
    }
    g_memo[i1][j1][i2] = ans1;
    return g_memo[i1][j1][i2];
}

int Dfs(int** grid, int gridSize, int* gridColSize)
{
    g_n = gridSize;
    for (int i = 0; i < g_n; i++) {
        for (int j = 0; j < g_n; j++) {
            for (int k = 0; k < g_n; k++) {
                g_memo[i][j][k] = MIN_VAL;
            }
        }
    }
    int ans;
    ans = Step(grid, g_n - 1, g_n - 1, g_n - 1);
    return MAX(0, ans);
}

/* dfs超时，选择dp [i][j] : 表示s的i字符到p的j字符的匹配情况 */

int cherryPickup(int** grid, int gridSize, int* gridColSize)
{
    int ans = -1;
    if (grid == NULL || gridSize == 0) return 0;
    ans = Dfs(grid, gridSize, gridColSize);
    // ans = Dp(s, p);
    return ans;
}

int main()
{
    int ans = 0;
    return ans;
}