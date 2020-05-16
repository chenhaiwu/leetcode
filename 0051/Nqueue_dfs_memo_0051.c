/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: ¦Ò¥Í‰b?¥N?
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
// #include "securec.h"

// ¤K¬Ó¦Z??, ŸÏ1?©l¨ì8 ²`«×¤W¨«¤@¨B¡A¦bÆÎ«×¤W¥h±´¯Á¹M?
#define MAX_N 1000
#define MAX_RET_N 5000
int g_board[MAX_N][MAX_N];
int g_n;
// char ***g_ret;
int g_retcnt;

#define ND 3
/* ?¬dn¬Ó¦Zªº??¡A¦]?¬OŸÏ¤W©¹¤U¨C¤@¦æ?´yªº¡A©Ò¥H¥u­n?¬d¥ª¤W¡A¥k¤W±×?¡A¤W??¡A¤TŸÄ¤è¦Vªºª½?§Y¥i */
int g_dirs[ND][2] = { {-1, 0}, {-1, -1}, {-1, 1} };

void CopyToRet(char ***g_ret)
{
    char **nm = (char **)malloc(sizeof(char *) * g_n);
    memset(nm, 0x0, sizeof(char *) * g_n);
    for (int i = 0; i < g_n; i++) {
        nm[i] = (char *)malloc(sizeof(char) * (g_n + 1));
        memset(nm[i], 0x0, sizeof(char) * (g_n + 1));
    }
    for (int i = 0; i < g_n; i++) {
        for (int j = 0; j < g_n; j++) {
            if (g_board[i][j] == 1) {
                nm[i][j] = 'Q';
            } else {
                nm[i][j] = '.';
            }
        }
    }
    g_ret[g_retcnt] = nm;
    g_retcnt++;
}

void PrintQueue(char ***g_ret)
{
    for (int t = 0; t < g_retcnt; t++) {
        for (int i = 0; i < g_n; i++) {
            for (int j = 0; j < g_n; j++) {
                printf("%c ", g_ret[t][i][j]);
            }
            printf("\n");
        }
    }
}

bool CheckOneLine(int row, int col, int dir)
{
    bool bRet = true;
    for (;;) {
        int nx = row + g_dirs[dir][0];
        int ny = col + g_dirs[dir][1];
        if (nx < 0 || nx >= g_n || ny < 0 || ny >= g_n) {
            break;
        }
        if (g_board[nx][ny] == 1) {
            return false;
        }
        row = nx;
        col = ny;
    }
    return bRet;
}

bool CheckQueue(int row, int col)
{
    for (int i = 0; i < ND; i++) {
        if (!CheckOneLine(row, col, i)) {
            return false;
        }
    }
    return true;
}

// posªí¥Ü?«e²Ä¤LŸÄ¬Ó¦Z, ŸÏ0?©lªí¥Ü²Ä1ŸÄ¡C
void Dfs(int pos, char ***g_ret)
{
    if (pos == g_n) {
        // PrintQueue();
        CopyToRet(g_ret);
        return;
    }
    for (int col = 0; col < g_n; col++) {
        if (CheckQueue(pos, col)) {
            g_board[pos][col] = 1;
            Dfs(pos + 1, g_ret);
            g_board[pos][col] = 0;
        }
    }
}

char *** solveNQueens(int n, int* returnSize, int** returnColumnSizes)
{
    g_n = n;
    g_retcnt = 0;
    memset(g_board, 0x0, sizeof(g_board));
    char ***g_ret = (char ***)malloc(sizeof(char **) * MAX_RET_N);
    Dfs(0, g_ret);
    // PrintQueue();
    *returnColumnSizes = (int *)malloc(sizeof(int) * (g_retcnt));
    memset(*returnColumnSizes, 0x0, sizeof(int) * (g_retcnt));
    for (int i = 0; i < g_retcnt; i++) {
        (*returnColumnSizes)[i] = n;
    }
    *returnSize = g_retcnt;
    // printf("cnt=%d\n", g_retcnt);
    // printf("cnt=%d\n", g_retcnt);
    return g_ret;
}