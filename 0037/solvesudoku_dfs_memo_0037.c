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
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 1; i <= numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

#define MAX_N 10
int g_v[MAX_N][MAX_N];
bool g_row[MAX_N][MAX_N];
bool g_col[MAX_N][MAX_N];
bool g_sb[MAX_N][MAX_N];
bool bFinish;

void PrintMatrix()
{
#ifdef DEGUG_CHW
    printf("value: \n");
    for (int i = 1; i <= 9; i++) {
        PrintArray(g_v[i], 9);
    }
#endif
    printf("g_row: \n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (g_row[i][j]) printf("1 ");
            else (g_row[i][j]) printf("0 ");
        }
        printf("\n");
    }
    printf("g_col: \n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (g_col[i][j]) printf("1 ");
            else (g_col[i][j]) printf("0 ");
        }
        printf("\n");
    }
    printf("g_sb: \n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (g_sb[i][j]) printf("1 ");
            else (g_sb[i][j]) printf("0 ");
        }
        printf("\n");
    }
}


void InitV(char** board)
{
    bFinish = false;
    memset(g_row, 0x0, sizeof(g_row));
    memset(g_col, 0x0, sizeof(g_col));
    memset(g_sb, 0x0, sizeof(g_sb));
    memset(g_v, 0x0, sizeof(g_v));
    for (int i = 1; i < MAX_N; i++) {
        for (int j = 1; j < MAX_N; j++) {
            if (board[i - 1][j - 1] != '.') {
                int t = board[i - 1][j - 1] - '0';
                g_row[i][t] = true;
                g_col[j][t] = true;
                int si = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
                g_sb[si][t] = true;
                g_v[i][j] = t;
            }
        }
    }
    printf("inti value\n");
    PrintMatrix();
}

void Finish(char** board)
{
    for (int i = 1; i < MAX_N; i++) {
        for (int j = 1; j < MAX_N; j++) {
            board[i - 1][j - 1] = g_v[i][j] + '0';
        }
    }
}

void Step(int r, int c)
{
    // 如果行已经是跑到第10行，则表示找到，完成
    if (r == MAX_N) {
        bFinish = true;
    printf("finish value\n");
    PrintMatrix();
        return;
    }
    // 如果当前值不为0，已经有值了，则直接进入下一步
    if (g_v[r][c] != 0) {
        if (c == MAX_N - 1) {
            Step(r + 1, 0);
        } else {
            Step(r, c + 1);
        }
    } else {
        // 如果当前为0，则需要从1-9中找到一个数字
        int si = (r - 1) / 3 * 3 + (c - 1) / 3 + 1;
        for (int v = 1; v < MAX_N; v++) {
            if (g_row[r][v] || g_col[c][v] || g_sb[si][v]) continue;
            g_row[r][v] = true;
            g_col[c][v] = true;
            g_sb[si][v] = true;
            g_v[r][c] = v;

            if (c == MAX_N - 1) {
                Step(r + 1, 0);
            } else {
                Step(r, c + 1);
            }
            if (!bFinish) {
                g_row[r][v] = false;
                g_col[c][v] = false;
                g_sb[si][v] = false;
                g_v[r][c] = 0;
            }
        }
    }
}

void Dfs(char** board, int boardSize, int* boardColSize)
{
    InitV(board);
    Step(1, 1);
    printf("copy before value\n");
    PrintMatrix();
    Finish(board);
    printf("copy after value\n");
    PrintMatrix();

}

void solveSudoku(char** board, int boardSize, int* boardColSize)
{
    Dfs(board, boardSize, boardColSize);
}


#define MAP_ROW 9
#define MAP_COL 9
char g_map[MAP_ROW][MAP_COL] = {"53..7....", "6"};
int g_col[MAP_ROW] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

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