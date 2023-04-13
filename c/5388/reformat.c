/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

// #include "securec.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 1; i <= numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

char FindNextChar(char *s, int idx, bool ischar)
{
    int cnt = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (ischar) {
            if (isalpha(s[i])) {
                if (cnt == idx) {
                    return s[i];
                }
                cnt++;
            }
        } else {
            if (isdigit(s[i])) {
                if (cnt == idx) {
                    return s[i];
                }
                cnt++;
            }
        }
    }
    return "";
}

char * reformat(char * s)
{
    int len = strlen(s);
    char *ret = (char *)malloc(len + 1);
    memset(ret, 0x0, len + 1);
    int dnum = 0;
    int cnum = 0;
    int ci = 0;
    int ni = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(s[i])) {
            cnum++;
        } else {
            dnum++;
        }
    }
    if (abs(dnum - cnum) > 1) {
        return "";
    }
    bool iscurchar = cnum > dnum ? true : false;
    for (int i = 0; i < len; i++) {
        if (iscurchar) {
            ret[i] = FindNextChar(s, ci, iscurchar);
            ci++;
            iscurchar = false;printf("%s\n", ret);
        } else {
            ret[i] = FindNextChar(s, ni, iscurchar);
            ni++;
            iscurchar = true;printf("%s\n", ret);
        }
    }
    return ret;
}

int main()
{
    char *ret = reformat("a0b1c2");
    printf("%s\n", ret);
    return 0;
}