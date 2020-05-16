#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_N 501

void RevertWord(char *s)
{
    char tmp;
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        tmp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = tmp;
    }
}

void HanldeFirst0Forward(int start, char *s)
{
    int len = strlen(s);
    for (int i = start; i < len; i++) {
        if (s[i] == '0') {
            s[i] = '1';
            break;
        } else {
            s[i] = '0';
        }
    }
}

int numSteps(char * s)
{
    RevertWord(s);
    int len = strlen(s);
    char *str = (char *)malloc(len + 2);
    memset(str, 0x0, len + 2);
    strcpy(str, s);
    str[len] = '0';
    str[len + 1] = '\0';
    int ans = 0;
    // s[i] == '0'，不做任何处理，直接ans++,如果为1，则往后找第一个非0的数，中间1变0，找到0变1
    for (int i = 0; i < len;) {
        if (str[i] == '1') {
            if (i == len - 1) break;
            HanldeFirst0Forward(i, str);
            // printf("ans=%d, i=%d, %s\n", ans, i, &str[i]);
        } else {
            // printf("ans=%d, i=%d, %s\n", ans, i, &str[i]);
            i++;
        }
        ans++;
    }

    return ans;
}

// int main()
// {
//     char *s = "1";
//     char *p = (char *)malloc(strlen(s) + 1);
//     memset(p, 0x0, strlen(s) + 1);
//     strcpy(p, s);
//     int ans;
//     ans = numSteps(p);
//     printf("%d\n", ans);
//     return 0;
// }