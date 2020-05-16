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

long long CalNum(char *s, int *idx)
{
    long long ans = 0;
    int len = 0;
    while (*s != '\0' && *s <= '9' && *s >= '0') {
        ans = ans * 10 + *s - '0';
        s++;
        len++;
    }
    *idx = len;
    return ans;
}

int Cal(char *s, int *idx)
{
    int ans = 0;
    bool isAdd = true;
    char *p = s;
    while (*p != '\0' && *p != ')') {
        if (*p == '+') {
            isAdd = true;
            p++;
        } else if (*p == '-') {
            isAdd = false;
            p++;
        } else if (*p <= '9' && *p >= '0') {
            int num1len;
            int num1 = CalNum(p, &num1len);
            p += num1len;
            if (isAdd) {
                ans += num1;
            } else {
                ans -= num1;
            }
        } else if (*p == '(') {
            p++;
            int num1len = 0;
            int num1 = Cal(p, &num1len);
            if (isAdd) {
                ans += num1;
            } else {
                ans -= num1;
            }
            p += num1len;
        } else {
            p++;
        }
    }
    *idx = p - s + 1;
    return ans;
}

int calculate(char * s)
{
    if (s == NULL) {
        return 0;
    }
    int idx;
    int ans = Cal(s, &idx);
    return ans;
}