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
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

#define MAX_N 50001
int g_sum[MAX_N];

int Qiuhe(int* a, int len)
{
    int ans = 0;
    for (int i = 0; i < len; i++) {
        ans += a[i];
    }
    return ans;
}

/* 从最高点开始往两边找，并增加1，注意条件非常牛：就是以最终符合条件了，就不再遍历增加 
 * 超时。不过要学习一个这个数据根据最弱的结果来检查条件的方法。
 */
int LineBaoli(int* a, int len)
{
    int ans;
    for (int i = 0; i < len; i++) g_sum[i] = 1;
    // int g_sum[len];
    bool bFlag = true;
    while (bFlag) {
        bFlag = false;
        for (int i = 0; i < len; i++) {
            if (i < len - 1 && a[i] > a[i + 1] && g_sum[i] <= g_sum[i + 1]) {
                bFlag = true;
                g_sum[i] = g_sum[i + 1] + 1;
            }
            if (i > 0 && a[i] > a[i - 1] && g_sum[i] <= g_sum[i - 1]) {
                bFlag = true;
                g_sum[i] = g_sum[i - 1] + 1;
            }
        }
    }
    ans = Qiuhe(g_sum, len);
    return ans;
}

int g_left[MAX_N];
int g_right[MAX_N];
int ShuanxiangShua(int *a, int len)
{
    int ans;
    for (int i = 0; i < len; i++) {
        g_left[i] = 1;
        g_right[i] = 1;
    }
    for (int i = 0; i < len - 1; i++) {
        if (a[i + 1] > a[i]) {
            g_right[i + 1] = g_right[i] + 1;
        }
    }
    for (int i = len - 1; i > 0; i--) {
        if (a[i - 1] > a[i]) {
            g_left[i - 1] = g_left[i] + 1;
        }
    }
    for (int i = 0; i < len; i++) {
        g_left[i] = MAX(g_left[i], g_right[i]);
    }
    ans = Qiuhe(g_left, len);
    return ans;
}

int candy(int* ratings, int ratingsSize)
{
    if (ratingsSize == 0) return 0;
    int ans;
    // ans = LineBaoli(ratings, ratingsSize);
    ans = ShuanxiangShua(ratings, ratingsSize);
    return ans;
}

int main()
{
    int ans;
    int a[] = {1, 0, 2};
    ans = candy(a, sizeof(a) / sizeof(int));
    int b[] = {1, 2, 2};
    ans = candy(b, sizeof(b) / sizeof(int));
    return ans;
}