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

#define MAX_N 201
#define MAX_STEPS (2 * 201)

// 表示g_memo[i][j][steps] mouse在i位置，cat在j位置，此时走了第i步时的状态值
int g_memo[MAX_N][MAX_N][MAX_N * 2 + 1];
int g_n;

// g_memo[i][j][steps] = 0 : 初始值， 1：平局 2：mouse胜，3：表示cat胜，则好和结果差1
// step参数m ,c 表示动物的位置，走了多少步
int Step(int** g, int* gc, int m, int c, int cursteps)
{
    if (cursteps >= 2 * g_n) {
        g_memo[m][c][cursteps] = 1;
        return 1;
    }
    if (m == 0) {
        g_memo[m][c][cursteps] = 2;
        return g_memo[m][c][cursteps];
    } else if (m == c) {
        g_memo[m][c][cursteps] = 3;
        return g_memo[m][c][cursteps];
    }
    // memo
    if (g_memo[m][c][cursteps] != 0) {
        return g_memo[m][c][cursteps];
    }
    if (cursteps % 2 == 0) {
        // mouse go
        bool bCat = true;
        for (int i = 0; i < gc[m]; i++) {
            int nn = g[m][i];
            int nv = Step(g, gc, nn, c, cursteps + 1);
            if (nv == 2) {
                // m win, just return
                g_memo[m][c][cursteps] = 2;
                return 2;
            } else if (nv != 3) {
                // 还有路可走，其实就是平局
                bCat = false;
            }
        }
        if (bCat) {
            g_memo[m][c][cursteps] = 3;
        } else {
            g_memo[m][c][cursteps] = 1;
        }
        return g_memo[m][c][cursteps];
    } else {
        // cat go
        bool bMouse = true;
        for (int i = 0; i < gc[c]; i++) {
            int nn = g[c][i];
            if (nn == 0) continue;
            int nv = Step(g, gc, m, nn, cursteps + 1);
            if (nv == 3) {
                g_memo[m][c][cursteps] = 3;
                return 3;
            } else if (nv != 2) {
                bMouse = false;
            }
        }
        if (bMouse) {
            g_memo[m][c][cursteps] = 2;
        } else {
            g_memo[m][c][cursteps] = 1;
        }
        return g_memo[m][c][cursteps];
    }
}

int Dfs(int** graph, int graphSize, int* graphColSize)
{
    g_n = graphSize;
    int ans;
    memset(g_memo, 0x0, sizeof(g_memo));

    ans = Step(graph, graphColSize, 1, 2, 0) - 1;
    return ans;
}

int catMouseGame(int** graph, int graphSize, int* graphColSize)
{
    int ans;
    ans = Dfs(graph, graphSize, graphColSize);
    return ans;
}

#define MAP_ROW 6
#define MAP_COL 6
int g_map[MAP_ROW][MAP_COL] = {{2, 5}, {3}, {0, 4, 5}, {1, 4, 5}, {2, 3}, {0, 2, 3}};
int g_col[MAP_ROW] = {2, 1, 3, 3, 2, 3};

int main()
{
    int gridSize = MAP_ROW;
    int **grid = NULL;
    int *gridColSize = NULL;

    /* 申请测试用例输入参数中需要的内存并根据用例输入初始化 */
    grid = malloc(gridSize * sizeof(int *));
    if (grid == NULL) {
        return -1;
    }
    gridColSize = malloc(gridSize * sizeof(int));
    if (gridColSize == NULL) {
        return -1;
    }
    for (int i = 0; i < gridSize; i++) {
        gridColSize[i] = g_col[i];
        grid[i] = malloc(gridColSize[i] * sizeof(int));
        if (grid[i] == NULL) {
            return -1;
        }
    }
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            grid[i][j] = g_map[i][j];
        }
    }

    int result = catMouseGame(grid, gridSize, gridColSize);

    /* 释放测试用例输入参数中申请的内存 */
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(gridColSize);
    free(grid);
}