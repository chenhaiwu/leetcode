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

// #define MAX_N 10001

int* maxDepthAfterSplit(char * seq, int* returnSize)
{
    int len = strlen(seq);
    int *ret = (int *)malloc(sizeof(int) * len);
    int depth = 0;
    for (int i = 0; i < len; i++) {
        if (seq[i] == '(') {
            depth++;
            ret[i] = depth % 2;
        } else {
            ret[i] = depth % 2;
            depth--;
        }
    }
    *returnSize = len;
    return ret;
}


int main()
{
    return 0;
}