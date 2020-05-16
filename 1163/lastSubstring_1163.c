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

#define MAX_N 400001
#define CHAR_N 26
// 二维数组降到一维即可，其它行数据无用
int g_map[MAX_N];
int g_maxIdxlen;
char *g_s;
int g_len;
int g_maxIdx;

int Cmp(void *a, void *b)
{
    int ta = *(int *)(a);
    int tb = *(int *)(b);
    int minLen = MIN(g_len - ta, g_len - tb);
    int ans = strncmp(&g_s[tb], &g_s[ta], minLen);
    if (ans == 0) {
        return ta - tb;
    } else {
        return ans;
    }
}

void InitHandle()
{
    g_len = strlen(g_s);
    g_maxIdxlen = 0;
    g_maxIdx = -1;
    memset(g_map, 0x0, sizeof(g_map));
    for (int i = 0; i < g_len; i++) {
        int idx = g_s[i] - 'a';
        if (idx > g_maxIdx) {
            g_maxIdx = idx;
            if (g_maxIdx == CHAR_N - 1) {
                break;
            }
        }
    }

    for (int i = 0; i < g_len; i++) {
        int idx = g_s[i] - 'a';
        if (idx == g_maxIdx) {
            g_map[g_maxIdxlen++] = i;
        }
    }
}

char *Qsortsubstring(char *s)
{
    g_s = s;
    InitHandle();
    if (g_maxIdx == 0) return s;

    // 对最大字母开头的那一行进行字符串排序，注意最大的子串，一定是以那个排序最大的到结束。
    // 排序后，把最大的字串放到第一个元素上面来
    qsort(g_map, g_maxIdxlen, sizeof(int), Cmp);

    int beginIdx = g_map[0];
    return &g_s[beginIdx];
}

char *DirectCmp(char *s)
{
    int ans = 0;
    int len = strlen(s);
    for (int i = 1; i < len; i++) {
        if (s[i] < s[i - 1]) {
            continue;
        }
        if (strcmp(&s[i], &s[ans]) > 0) {
            ans = i;
        }
    }
    return &s[ans];
}

char * lastSubstring(char * s)
{
    char *ret;
    // ret = Qsortsubstring(s);
    ret = DirectCmp(s);
    return ret;
}

int main()
{
    int ans = 0;
    char *s;
    s = lastSubstring("abab");
    printf("%s\n",s);
    s = lastSubstring("leetcode");
    printf("%s\n",s);
    s = lastSubstring("adadc");
    printf("%s\n",s);
    s = lastSubstring("adadac");
    printf("%s\n",s);
    return ans;
}