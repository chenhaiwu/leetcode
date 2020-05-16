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

int GetNum(char *s, int *numlen)
{
    int ans = 0;
    int len = 0;
    int v = 0;
    while (*s != '\0' && *s <= '9' && *s >= '0') {
        int t = *s - '0';
        v = v * 10 + t;
        len++;
        s++;
    }
    *numlen = len;
    return v;
}

int Cal(char *s, int *i)
{
    char *c = s;
    int ans = 0;
    int flag = 1;
    while (*c != ')' && *c != '\0') {
        if (*c == '+') {
            flag = 1;
            c++;
        } else if (*c == '-') {
            flag = 0;
            c++;
        } else if (*c <= '9' && *c >= '0') {
            int num1len = 0;
            int num1 = GetNum(c, &num1len);
            c += num1len;
            if (flag == 1) {
                ans += num1;
            } else {
                ans -= num1;
            }
            
        } else if (*c == '(') {
            c++;
            int num1len = 0;
            int num1 = Cal(c, &num1len);
            if (flag == 1) {
                ans += num1;
            } else {
                ans -= num1;
            }
            c += num1len;
        } else {
            c++;
        }
    }
    *i = c - s + 1;
    return ans;
}

int calculate(char * s)
{
    int inc = 0;
    if (s == NULL || strlen(s) == 0) return 0;
    int ans = Cal(s, &inc);
    return ans;
}

// int main()
// {
//     // char *a = "(1+(4+5+2)-3)+(6+8)";
//     char *a = "1 + 1";
//     int len = strlen(a);
//     char *s = (char *)malloc(len + 1);
//     memset(s, 0x0, len + 1);
//     strcpy(s, a);
//     int ans = calculate(s);
//     return ans;
// }