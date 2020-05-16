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

#define DEGUG_CHW 1
void PrintArray(int *nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 1; i <= numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

#define MAX_N 51
#define MAX_TIME 0x5a5a5a5aU
int g_memo[MAX_N][MAX_N][MAX_N * MAX_N];
int g_ret;
int g_n;
int g_dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

// opt
#define OPT_LEN
int g_memolen[MAX_N][MAX_N];

void InitV(int gridSize)
{
    g_ret = MAX_TIME;
    g_n = gridSize;
    memset(g_memo, MAX_TIME, sizeof(g_memo));
#ifdef OPT_LEN
    memset(g_memolen, 0x0, sizeof(g_memolen));
#endif
}

bool CheckLessTime(int r, int c, int t)
{
    for (int i = 0; i < g_memolen[r][c]; i++) {
        if (g_memo[r][c][i] <= t) {
            return true;
        }
    }
    return false;
}

bool IsExitMatrix(int m, int n, int i, int j)
{
    bool ans = false;
    if (i < 0 || i == m || j < 0 || j == n) {
        ans = true;
    }
    return ans;
}

void Step(int r, int c, int t, int **grid)
{
    if (t > g_ret) {
        return;
    }
    if (r == g_n - 1 && c == g_n - 1) {
        printf("finish value, t=%d\n", t);
        if (g_ret > t)
            g_ret = t;
        return;
    }
#ifdef OPT_LEN
    if (CheckLessTime(r, c, t)) {
        return;
    }
#else
    if (g_memo[r][c][t] != MAX_TIME) {
        return;
    }
    // 如果只是按每步都去检查2500个，则还不如不检查，反而超时。因此考虑优化时，就不能使用固定长度的数组，要用实际存的个数
    // if (CheckLessTime(r, c, t)) return;
#endif

    int ans = MAX_TIME;
    for (int k = 0; k < 4; k++) {
        int newr = r + g_dirs[k][0];
        int newc = c + g_dirs[k][1];
        if (IsExitMatrix(g_n, g_n, newr, newc))
            continue;
        int newt = grid[newr][newc];
        if (newt < t)
            newt = t;
#ifdef OPT_LEN
        g_memo[r][c][g_memolen[r][c]] = newt;
        g_memolen[r][c]++;
#else
        g_memo[r][c][newt] = 1;
#endif
        Step(newr, newc, newt, grid);
        // ans = MIN(ans, curTime);
    }
    return;
}

int Dfs(int **grid, int gridSize, int *gridColSize)
{
    InitV(gridSize);
    Step(0, 0, grid[0][0], grid);
    return g_ret;
}

int g_visit2[MAX_N][MAX_N];
int g_find;
void BiDfs(int r, int c, int t, int **grid)
{
    if (g_find || grid[r][c] > t) return;
    if (r == g_n - 1 && c == g_n - 1) {
        g_find = true;
        return;
    }

    for (int k = 0; k < 4; k++) {
        int newr = r + g_dirs[k][0];
        int newc = c + g_dirs[k][1];
        if (IsExitMatrix(g_n, g_n, newr, newc))
            continue;
        int newt = grid[newr][newc];
        if (newt > t) continue;
        if (g_visit2[newr][newc] == 1) continue;
        g_visit2[newr][newc] = 1;
        BiDfs(newr, newc, t, grid);
    }
    return;
}

int BinaryDfs(int **grid, int gridSize, int *gridColSize)
{
    int maxStep = 0;
    g_n = gridSize;
    for (int i = 0; i < g_n; i++) {
        for (int j = 0; j < g_n; j++) {
            maxStep = MAX(maxStep, grid[i][j]);
        }
    }
    int left = 0;
    int right = maxStep;
    while (left < right) {
        int mid = left + (right - left) / 2;
        memset(g_visit2, 0x0, sizeof(g_visit2));
        g_find = false;
        g_visit2[0][0] = true;
        BiDfs(0, 0, mid, grid);
        if (g_find) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int swimInWater(int **grid, int gridSize, int *gridColSize)
{
    int ans;
    // work
    // ans = Dfs(grid, gridSize, gridColSize);

    // 使用二分查找，可以根据值来做二分
    ans = BinaryDfs(grid, gridSize, gridColSize);
    return ans;
}

// #define MAP_ROW 5
// #define MAP_COL 5
// int g_map[MAP_ROW][MAP_COL] = {{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}};
// int g_col[MAP_ROW] = {5,5,5,5,5};

// int main()
// {
//     int gridSize = MAP_ROW;
//     int **grid = NULL;
//     int *gridColSize = NULL;

//     /* 申请测试用例输入参数中需要的内存并根据用例输入初始化 */
//     grid = malloc(gridSize * sizeof(int *));
//     if (grid == NULL) {
//         return -1;
//     }
//     gridColSize = malloc(gridSize * sizeof(int));
//     if (gridColSize == NULL) {
//         return -1;
//     }
//     for (int i = 0; i < gridSize; i++) {
//         gridColSize[i] = g_col[i];
//         grid[i] = malloc(gridColSize[i] * sizeof(int));
//         if (grid[i] == NULL) {
//             return -1;
//         }
//     }
//     for (int i = 0; i < gridSize; i++) {
//         for (int j = 0; j < gridColSize[i]; j++) {
//             grid[i][j] = g_map[i][j];
//         }
//     }
//     int result = swimInWater(grid, gridSize, gridColSize);

//     /* 释放测试用例输入参数中申请的内存 */
//     for (int i = 0; i < gridSize; i++) {
//         free(grid[i]);
//     }
//     free(gridColSize);
//     free(grid);
// }