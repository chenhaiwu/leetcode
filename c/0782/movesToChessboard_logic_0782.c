/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
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

#define MAX_N 31
// ¥Î¤_??¨C¤@¦æÉO²Ä¤@¦æ¬O¬Û¤Ï?¬O¬Û¦P¡A‰z²Ä1¦æ?1¡A¬Û¤Ï?0¡Aªì©l¤Æ?0
int g_rows[MAX_N];
int g_n;

bool IsSameRow(int** board, int i, int j, int* boardColSize)
{
    for (int k = 0; k < boardColSize[i]; k++) {
        if (board[i][k] != board[j][k]) {
            return false;
        }
    }
    return true;
}

bool IsReverseRow(int** board, int i, int j, int* boardColSize)
{
    for (int k = 0; k < boardColSize[i]; k++) {
        if (board[i][k] + board[j][k] != 1) {
            return false;
        }
    }
    return true;
}

bool IsBalenceArray(int *a, int len)
{
    int sum = 0;
    for (int k = 0; k < len; k++) {
        sum += a[k];
    }
    if (len % 2 == 0) {
        return sum == len / 2 ? true : false;
    } else {
        if (sum == len / 2 || sum == (len + 1) / 2) {
            return true;
        } else {
            return false;
        }
    }
}

int GetMinSwapNum(int *a, int len)
{
    int swapNum = 0;
    // begin: 101010...¡A °¸?¦æ?1¡A©_?¦æ­n?0¡A§_?++
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            if (a[i] != 1) {
                swapNum++;
            }
        } else {
            if (a[i] != 0) {
                swapNum++;
            }
        }
    }
    // ¦pªG»Ý­n¥æ?ªº¦æ??©_?¦¸¡A?©úÆÓªk??¡A¦]?¤@¦¸¥æ?2¦æ
    if (swapNum % 2 == 1) {
        swapNum = -1;
    } else {
        swapNum /= 2;
    }    

    // ±µ¤U???01010101¡A©_?¦æ?1¡A°¸?¦æ?0¡A‰s?¤£¤@ý©?¦r
    int rn = 0;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 1) {
            if (a[i] != 1) {
                rn++;
            }
        } else {
            if (a[i] != 0) {
                rn++;
            }
        }
    }
    if (rn % 2 == 1) {
        rn = -1;
    } else {
        rn /= 2;
    }
    if (swapNum == -1) return rn;
    if (rn == -1) return swapNum;
    int ans = MIN(rn, swapNum);
    return ans;
}

int movesToChessboard(int** board, int boardSize, int* boardColSize)
{
    int ans = 0;
    memset(g_rows, 0x0, sizeof(g_rows));
    g_n = boardSize;
    g_rows[0] = 1;
    for (int i = 1; i < g_n; i++) {
        if (IsSameRow(board, i, 0, boardColSize)) {
            g_rows[i] = 1;
        } else if (IsReverseRow(board, i, 0, boardColSize)) {
            g_rows[i] = 0;
        } else {
            return -1;
        }
    }
    if (!IsBalenceArray(g_rows, g_n)) {
        return -1;
    }
    if (!IsBalenceArray(board[0], g_n)) {
        return -1;
    }
    int minRowSwap = GetMinSwapNum(g_rows, g_n);
    int minColSwap = GetMinSwapNum(board[0], g_n);
    ans = minColSwap + minRowSwap;
    return ans;
}

#define MAP_ROW 5
#define MAP_COL 5
int g_map[MAP_ROW][MAP_COL] = {{1,0,0,1,1},{0,1,1,0,0},{1,0,0,1,1},{0,1,1,0,0},{0,1,1,0,0}};
int g_col[MAP_ROW] = {5,5,5,5,5};

int main()
{
    int gridSize = MAP_ROW;
    int **grid = NULL;
    int *gridColSize = NULL;

    /* ¥Ó???¥Î¨Ò™]¤J‰ë?¤¤»Ý­nªº?¦s¦}®ÚÕu¥Î¨Ò™]¤Jªì©l¤Æ */
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

    int result = movesToChessboard(grid, gridSize, gridColSize);

    /* ?©ñ??¥Î¨Ò™]¤J‰ë?¤¤¥Ó?ªº?¦s */
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(gridColSize);
    free(grid);
}