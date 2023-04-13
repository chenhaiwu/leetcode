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
#define MAX_RET_N 100
char **g_ret;
int g_retcnt;
int g_left;
int g_right;

void GetMoreLeftRight(char *s)
{
    g_left = 0;
    g_right = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            g_left++;
        } else if (s[i] == ')') {
            if (g_left > 0) {
                g_left--;
            } else {
                g_right++;
            }
        }
    }
}

bool IsValid(char *s)
{
    int left = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            left++;
        } else if (s[i] == ')') {
            left--;
            if (left < 0) {
                return false;
            }
        }
    }
    return left == 0 ? true : false;
}

void Dfs(char * s, int step, int left, int right)
{
    int len = strlen(s);
    if (step > len) return;
    if (left == 0 && right == 0) {
        if (IsValid(s)) {
            char *ss = (char *)malloc(len + 1);
            strcpy(ss, s);
            ss[len] = '\0';
            printf("ret:%s\n", ss);
            g_ret[g_retcnt] = ss;
            g_retcnt++;
        }
        return;
    }
    char news[len];
    for (int i = step; i < len; i++) {
        if (i > 0 && s[i] == s[i - 1]) continue;
        if (left > 0 && s[i] == '(') {
            memcpy(news, s, i);
            news[i] = '\0';
            strcpy(news + i, s + i + 1);
            printf("news:%s\n", news);
            Dfs(news, i, left - 1, right);
        }
        if (right > 0 && s[i] == ')') {
            printf("s:%s\n", s);
            memcpy(news, s, i);
            news[i] = '\0';
            printf("news:%s\n", news);
            strcpy(news + i, s + i + 1);
            printf("news:%s\n", news);
            Dfs(news, i, left, right - 1);
        }
    }
}

char ** removeInvalidParentheses(char * s, int* returnSize)
{
    GetMoreLeftRight(s);
    g_retcnt = 0;
    g_ret = (char **)malloc(sizeof(char *) * MAX_RET_N);
    memset(g_ret, 0x0, sizeof(char *) * MAX_RET_N);

    Dfs(s, 0, g_left, g_right);

    // return value
    if (g_retcnt == 0) {
        g_ret[0] = "";
        g_retcnt = 1;
    }
    *returnSize = g_retcnt;
    return g_ret;
}

// void main()
// {
//     char *s = "a(";
//     int retsize;
//     char **ret = removeInvalidParentheses(s, &retsize);
//     for (int i = 0; i < retsize; i++) {
//         printf("%s\n", ret[i]);
//         free(ret[i]);
//     }
//     free(ret);
//     return;
// }