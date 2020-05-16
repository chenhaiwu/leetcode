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


int BitSet(int mask, int bit)
{
    return mask | (1 << bit);
}

int BitClr(int mask, int bit)
{
    return mask & (~(1 << bit));
}

bool BitTest(int mask, int bit)
{
    if ((mask & (1 << bit)) >> bit == 1) {
        return true;
    } else {
        return false;
    }
}

#define MAX_N 1000
int g_maps[MAX_N];

int maxProduct(char ** words, int wordsSize)
{
    memset(g_maps, 0x0, sizeof(g_maps));
    for (int i = 0; i < wordsSize; i++) {
        int len = strlen(words[i]);
        for (int j = 0; j < len; j++) {
            int idx = words[i][j] - 'a';
            g_maps[i] = BitSet(g_maps[i], idx);
        }
    }

    int ans = 0;
    for (int i = 0; i < wordsSize; i++) {
        for (int j = i + 1; j < wordsSize; j++) {
            if ((g_maps[i] & g_maps[j]) == 0) {
                int t = strlen(words[i]) * strlen(words[j]);
                ans = MAX(ans, t);
            }
        }
    }
    return ans;
}