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

char * longestDupSubstring1(char * s)
{
    int len = strlen(s);
    printf("%d\n", len);
    // if (len > 40000) {
        
    //     return "";
    // }
    int idx = -1;
    int ans = 0;
    for (int i = 0; i + ans < len; i++) {        
        for (int j = i + 1; j + ans < len;) {
            int m = i;
            int n = j;
            int curcnt = 0;
            while (m < len && n < len && s[m] == s[n]) {
                m++;
                n++;
                curcnt++;
            }
            if (ans < curcnt) {
                ans = curcnt;
                idx = i;
            }
            j = n == j ? (j + 1) : (n);
        }
    }
    if (idx == -1) return "";
    char *ret = (char *)malloc(ans + 1);
    for (int i = 0; i < ans; i++) {
        ret[i] = s[i + idx];
    }
    ret[ans] = '\0';
    return ret;
}


char * longestDupSubstring(char * s)
{
    int len = strlen(s);
    // printf("%d\n", len);
    // if (len > 40000) {
        
    //     return "";
    // }
    int idx = -1;
    int ans = 0;
    for (int i = 0; i + ans < len;) {
        int ijump = 0;
        for (int j = i + 1; j + ans < len;) {
            int m = i;
            int n = j;
            int curcnt = 0;
            while (m < len && n < len && s[m] == s[n]) {
                m++;
                n++;
                curcnt++;
            }
            if (ans < curcnt) {
                ans = curcnt;
                idx = i;
                
            }
            j = n == j ? (j + 1) : (n);
            ijump = m == i ? 0 : ans;
        }
        if (ijump == 0) i++;
        else i += ijump;
    }
    if (idx == -1) return "";
    char *ret = (char *)malloc(ans + 1);
    for (int i = 0; i < ans; i++) {
        ret[i] = s[i + idx];
    }
    ret[ans] = '\0';
    return ret;
}

int main()
{
    int ans = 0;
    char *s;
    s = longestDupSubstring("abcdaaaabcd");
    printf("%s\n",s);
    s = longestDupSubstring("banana");
    printf("%s\n",s);
    s = longestDupSubstring("abcd");
    printf("%s\n",s);
    s = longestDupSubstring("aaaa");
    printf("%s\n",s);
    return ans;
}