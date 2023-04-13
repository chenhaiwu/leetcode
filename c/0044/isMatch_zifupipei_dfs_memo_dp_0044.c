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

#define MAX_N 10000
int g_memo[MAX_N][MAX_N];
int g_slen;
int g_plen;

bool Step(char * s, int si, char * p, int pi)
{
    while (si < g_slen && pi < g_plen && (s[si] == p[pi] || p[pi] == '?')) {
        si++;
        pi++;
    }
    if (g_memo[si][pi] > 0) return g_memo[si][pi] == 1;
    if (si == g_slen) {
        bool bFlag = true;
        for (int i = pi; i < g_plen; i++) {
            if (p[i] != '*') {
                bFlag = false;
                break;
            }
        }
        g_memo[si][pi] = bFlag ? 1 : 2;
        return bFlag;
    }
    if (pi == g_plen) {
        g_memo[si][pi] = 2;
        return false;
    }
    if (p[pi] != '*' && s[si] != p[pi]) {
        g_memo[si][pi] = 2;
        return false;
    }
    for (int i = si; i <= g_slen; i++) {
        bool bFlag = Step(s, i, p, pi + 1);
        if (bFlag) {
            g_memo[si][pi] = 1;
            return true;
        }
    }
    g_memo[si][pi] = 2;
    return false;
}

bool Dfs(char * s, char * p)
{
    bool ans = false;
    g_slen = strlen(s);
    g_plen = strlen(p);
    if (g_plen == 0) {
        return g_slen == 0;
    }
    if (g_slen == 0) {
        int len = strlen(p);
        for (int i = 0; i < len; i++) {
            if (p[i] != '*') return false;
        }
        return true;
    }
    memset(g_memo, 0x0, sizeof(g_memo));
    ans = Step(s, 0, p, 0);
    return ans;
}

/* dfs超时，选择dp [i][j] : 表示s的i字符到p的j字符的匹配情况 */
bool Dp(char * s, char * p)
{
    bool ans = false;
    g_slen = strlen(s);
    g_plen = strlen(p);
    
    int **g_dp = (int **)malloc(sizeof(int*) * (g_slen + 1));
    memset(g_dp, 0x0, sizeof(int *) * (g_slen + 1));
    for (int i = 0; i <= g_slen; i++) {
        g_dp[i] = (int *)malloc(sizeof(int) * (g_plen + 1));
        memset(g_dp[i], 0x0, sizeof(int) * (g_plen + 1));
    }

    // 初始
    g_dp[0][0] = 1;
    for (int i = 1; i <= g_plen; i++) {
        g_dp[0][i] = g_dp[0][i - 1] && p[i - 1] == '*';
    }
    for (int i = 1; i <= g_slen; i++) {
        for (int j = 1; j <= g_plen; j++) {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                g_dp[i][j] = g_dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                g_dp[i][j] = g_dp[i - 1][j - 1] || g_dp[i][j - 1] || g_dp[i - 1][j];
            }
        }
    }
    ans = g_dp[g_slen][g_plen] == 1 ? true : false;

    for (int i = 0; i < g_slen; i++) {
        free(g_dp[i]);
    }
    free(g_dp);
    
    return ans;
}

bool isMatch(char * s, char * p)
{
    bool ans = false;
    if (p == NULL || s == NULL) return ans;
    // ans = Dfs(s, p);
    ans = Dp(s, p);
    return ans;
}

int main()
{
    char *s1 = "abceb";
    char *s2 = "a*c?b";
    char *str1 = (char *)malloc(strlen(s1) + 1);
    memset(str1, 0x0, strlen(s1) + 1);
    strcpy(str1, s1);
    char *str2 = (char *)malloc(strlen(s2) + 1);
    memset(str2, 0x0, strlen(s2) + 1);
    strcpy(str2, s2);
    bool ans = isMatch(str1, str2);
    return ans;
}