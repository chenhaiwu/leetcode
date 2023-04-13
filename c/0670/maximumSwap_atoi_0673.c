#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)

/* 
 * 思路：因为给定的数字是在0, 10 8次方，然后数字的个数最多也就8个，然后二维遍历n *n 也不多，不会超时。
 * 1：先把数字转化成字符串
 * 2：再对当前位置，查找后面，有一个最大的字母，然后做一下调换
 * 3：再把字符串转化成数字，就是答案
 */
#define MAXL 100
char g_str[MAXL];
char * itoa_1(int n)
{
    int i = 0;
    do {
        g_str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    //g_str[i] = '\0';
    printf("i=%d\n", i);
    return g_str;
}

int atoi_1(char *s)
{
    int ret = 0;
    int len = strlen(s);
    for (int i = len - 1; i >= 0; i--) {
        ret = ret * 10 + s[i] - '0';
    }
    return ret;
}

int FindMax(char *s, int begin, int *pos)
{
    int len = strlen(s);
    int max = s[begin] - '0';
    for (int i = begin - 1; i >= 0; i--) {
        if (s[i] - '0' > max) {
            *pos = i;
            max = s[i] - '0';
        }
    }
    if (max != s[begin] - '0') {
        for (int i = *pos; i >= 0; i--) {
            if (s[i] - '0' == max) {
                *pos = i;
            }
        }
    }
    return max != s[begin] - '0';
}

int maximumSwap(int num)
{
    memset(g_str, 0x0, sizeof(g_str));
    char *s = itoa_1(num);
    printf("s=%s, str=%s\n", s, g_str);
    int len = strlen(s);
    int pos = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (FindMax(s, i, &pos)) {
            char c = s[i];
            s[i] = s[pos];
            s[pos] = c;
            break;
        }
    }
    printf("2:s=%s, str=%s\n", s, g_str);
    int ret = atoi_1(s);
    printf("3:s=%s, g_str=%s\n", s, g_str);
    printf("ret = %d\n", ret);
    return ret;
}

int main()
{
    int a = 1993;
    int ret = maximumSwap(a);
    printf("ret=%d\n", ret);
    return 0;
}