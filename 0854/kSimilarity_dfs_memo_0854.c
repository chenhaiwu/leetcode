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

int g_steps;
void Swap(char *A, int i, int j)
{
    char t = A[i];
    A[i] = A[j];
    A[j] = t;
}

void Step(char * A, char * B, int start, int cursteps)
{
    if (cursteps >= g_steps) return;
    int len = strlen(A);
    if (start == len) return;
    if (strcmp(A, B) == 0) {
        g_steps = cursteps;
        return;
    }
    int i = start;
    // 从start开始找到第一个A/B不相等的字符
    while (i < len && A[i] == B[i]) {
        i++;
    }
    // i 位置不相等，从i + 1位置开始找一个与A[i]相等的值，然后开始交换
    for (int j = i + 1; j < len; j++) {
        if (A[j] == B[i]) {
            Swap(A, i, j);
            Step(A, B, i + 1, cursteps + 1);
            Swap(A, j, i);
        }
    }
}

void Dfs(char * A, char * B)
{
    int start = 0;
    int cursteps = 0;
    Step(A, B, start, cursteps);
}

int kSimilarity(char * A, char * B)
{
    int ans;
    int len = strlen(A);
    if (strcmp(A, B) == 0) {
        return 0;
    }
    g_steps = INT_MAX;
    Dfs(A, B);
    ans = g_steps;
    return ans;
}


int main()
{
    char *str1 = "bccaba";
    char *str2 = "abacbc";
    int len = strlen(str1);
    char *s1 = (char *)malloc(len + 1);
    char *s2 = (char *)malloc(len + 1);
    memset(s1, 0x0, len + 1);
    memset(s2, 0x0, len + 1);
    strcpy(s1, str1);
    strcpy(s2, str2);
    printf("%s, %s\n", s1, s2);
    int ans;
    ans = kSimilarity(s1, s2);
    return ans;
}