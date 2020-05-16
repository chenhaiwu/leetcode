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

#define MAX_N 500
int g_memo[MAX_N][MAX_N];
// int **g_memo;
char *g_s1;
char *g_s2;
char *g_s3;
int g_s1len;
int g_s2len;
int g_s3len;
#define MAX_VALUE 0x55555555

bool Step(int a, int b)
{
    if (a + b == g_s3len) {
        return true;
    }

    int c = a + b;

    if (a == g_s1len) {
        return strcmp(&g_s2[b], &g_s3[c]) == 0;
    }
    if (b == g_s2len) {
        return strcmp(&g_s1[a], &g_s3[c]) == 0;
    }
    if (g_s1[a] != g_s3[c] && g_s2[b] != g_s3[c]) {
        return false;
    }
    if (g_memo[a][b] != -1) {
        return g_memo[a][b] == 1 ? true : false;
    }
    bool ans = false;
    if (a < g_s1len && g_s1[a] == g_s3[c]) {
        ans = Step(a + 1, b);
    }
    if (!ans && b < g_s2len && g_s2[b] == g_s3[c]) {
        ans = Step(a, b + 1);
    }
    g_memo[a][b] = ans ? 1 : 0;
    return ans;
}

bool Dfs(char * s1, char * s2, char *s3)
{
    bool ans = false;
    g_s1 = s1;
    g_s2 = s2;
    g_s3 = s3;
    g_s1len = strlen(s1);
    g_s2len = strlen(s2);
    g_s3len = strlen(s3);
    if (g_s1len + g_s2len != g_s3len) {
        return ans;
    }
    // g_memo = (int **)malloc(g_s1len * sizeof(int **));
    // for (int i = 0; i < g_s1len; i++) {
    //     g_memo[i] = (int *)malloc(g_s2len * sizeof(int));
    //     memset(g_memo[i], INT_MAX, g_s2len * sizeof(int));
    // }
    memset(g_memo, INT_MAX, sizeof(g_memo));
    ans = Step(0, 0);
    return ans;
}

bool isInterleave(char * s1, char * s2, char * s3)
{
    bool ans = false;
    ans = Dfs(s1, s2, s3);
    // ans = Dp(s, p);
    return ans;
}

// int main()
// {
//     char *s1 = "aabcc";
//     char *s2 = "dbbca";
//     char *s3 = "aadbbcbcac";
//     char *s4 = "aadbbbaccc";
//     bool ans = isInterleave(s1, s2, s3);
//     ans = isInterleave(s1, s2, s4);
//     return ans;
// }