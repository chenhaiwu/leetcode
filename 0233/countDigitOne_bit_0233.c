/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: 考生实现代码
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
// #include "securec.h"

#define MAX_RET_N 100

int countDigitOne(int n)
{
    int ans = 0;
    // xyzdabc 每次只盯着当前位d，考虑这个d位有多少个1
    for (long long k = 1; k <= n; k *= 10) {
        int xyzd = n / k;
        int xyz = xyzd / 10;
        int d = xyzd % 10;
        int abc = n % k;
        ans += xyz * k;
        if (d == 1) {
            ans += abc;
            ans += 1;
        } else if (d > 1) {
            ans += k;
        }
        if (xyz == 0) {
            break;
        }
    }
    return ans;
}

// int main()
// {
//     int ans;
//     ans = countDigitOne(13);
//     return ans;
// }