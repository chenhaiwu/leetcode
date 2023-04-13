#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 17
#define CHAR_N 100

char *strrevese(char *s1)
{
    int len = strlen(s1);
    for (int i = 0; i < len / 2; i++) {
        char c = s1[i];
        s1[i] = s1[len - i - 1];
        s1[len - i - 1] = c;
    }
    return s1;
}

char *AddNum(char *num, int start1, int len1, int start2, int len2)
{
    int len = MAX(len1, len2);
    len += 2;
    char *s = (char *)malloc(len);
    memset(s, 0x0, len);
    int n1 = start1 + len1 - 1;
    int n2 = start2 + len2 - 1;
    int carry = 0;
    int i = 0;
    while (carry || n1 >= start1 || n2 >= start2) {
        int t1 = (n1 >= start1) ? num[n1] - '0' : 0;
        int t2 = (n2 >= start2) ? num[n2] - '0' : 0;
        s[i++] = (t1 + t2 + carry) % 10 + '0';
        carry = (t1 + t2 + carry >= 10) ? 1 : 0;
        n1--;
        n2--;
    }
    printf("prev %s\n", s);
    s = strrevese(s);
    printf("after %s\n", s);
    return s;
}

bool Check3NumSum2(char *num, int start1, int len1, int start2, int len2, int start3, int len3)
{
    bool ans;
    char *sum = AddNum(num, start1, len1, start2, len2);
    int len = strlen(sum);
    if (len != len3) {
        ans = false;
    } else {
        ans = (strncmp(sum, num + start3, len3) == 0);
    }
    free(sum);
    return ans;
}

bool Check3NumSum(char *num, int start1, int len1, int start2, int len2, int start3, int len3)
{
    bool ans = false;
    char *s1 = (char *)malloc(len1 + 1);
    memset(s1, 0x0, len1 + 1);
    memcpy(s1, num + start1, len1);
    char *s2 = (char *)malloc(len2 + 1);
    memset(s2, 0x0, len2 + 1);
    memcpy(s2, num + start2, len2);
    char *s3 = (char *)malloc(len3 + 1);
    memset(s3, 0x0, len3 + 1);
    memcpy(s3, num + start3, len3);
    printf("old s1=%s, s2=%s, s3=%s\n", s1, s2, s3);
    s1 = strrevese(s1);
    s2 = strrevese(s2);
    s3 = strrevese(s3);
    printf("new s1=%s, s2=%s, s3=%s\n", s1, s2, s3);

    int forward = 0;
    int i = 0;
    for (i = 0; i < len1 && i < len2; i++) {
        int n1 = s1[i] - '0';
        int n2 = s2[i] - '0';
        int n3 = s3[i] - '0';

        if (n1 + n2 + forward == n3) {
            forward = 0;
            continue;
        } else if (n1 + n2 + forward == n3 + 10) {
            forward = 1;
        } else {
            goto FreeFlag;
        }
    }
    if (i == len1) {
        while (i < len2) {
            int n2 = s2[i] - '0';
            int n3 = s3[i] - '0';
            if (n2 + forward != n3 && n2 + forward != n3 + 10) {
                ans = false;
                goto FreeFlag; 
            }
            i++;
            if (n2 + forward >= 10) {
                forward = 1;
            } else {
                forward = 0;
            }            
        }
        if (forward == 1) {
            ans = (i == len3 - 1 && s3[len3 - 1] == '1');
        } else {
            ans = (i == len3);
        }
        goto FreeFlag; 
    }
    if (i == len2) {
        while (i < len1) {
            int n2 = s1[i] - '0';
            int n3 = s3[i] - '0';
            if (n2 + forward != n3 && n2 + forward != n3 + 10) {
                ans = false;
                goto FreeFlag; 
            }
            i++;
            if (n2 + forward >= 10) {
                forward = 1;
            } else {
                forward = 0;
            }            
        }
        if (forward == 1) {
            ans = (i == len3 - 1 && s3[len3 - 1] == '1');
        } else {
            ans = (i == len3);
        }
        goto FreeFlag;
    }
FreeFlag:
    free(s1);
    free(s2);
    free(s3);
    return ans;
}

bool StepWithSecond(char *num, int len, int start1, int len1, int start2, int len2)
{
    if (start2 + len2 == len) {
        return true;
    }

    bool ans = false;

    // 先验证结果
    int len3Base = MAX(len1, len2);
    int start3;
    int len3;
    for (int k = 0; k < 2; k++) {
        start3 = start2 + len2;
        len3 = len3Base + k;
        if (start3 + len3 > len) {
            continue;
        }
        if (num[start3] == '0' && len3 > 1) continue;
        ans = Check3NumSum2(num, start1, len1, start2, len2, start3, len3);
        if (ans) {
            break;
        }
    }
    // 取第三个数
    if (!ans) {
        return false;
    } else {
        ans = StepWithSecond(num, len, start2, len2, start3, len3);
        if (ans) {
            return ans;
        }
    }
    return ans;
}

bool StepWithFirstOne(char *num, int len, int start1, int len1)
{
    if (start1 + len1 == len) {
        return true;
    }

    bool ans = false;

    // 第二个数取的长度，[start1 + len1, (len - start - i) / 2] 这里先不细化
    int left2Len = (len - start1 - len1) / 2;
    for (int j = 1; j <= left2Len; j++) {
        int start2 = start1 + len1;
        int len2 = j;
        if (num[start2] == '0' && len2 > 1) continue;

        ans = StepWithSecond(num, len, start1, len1, start2, len2);
        if (ans) {
            return ans;
        }
    }
    return ans;
}

bool Step(int start, char *num, int len)
{
    if (start == len) {
        return true;
    }

    bool ans = false;
    // 第一个数取的长度, [0, len - start / 2]
    int left1Len = (len - start) / 2;
    for (int i = 1; i <= left1Len; i++) {
        int start1 = start;
        int len1 = i;
        if (num[start1] == '0' && len1 > 1) continue;
        ans = StepWithFirstOne(num, len, start1, len1);
        if (ans) {
            return ans;
        }
    }
    return ans;
}

int Dfs(char *num)
{
    int len = strlen(num);
    bool ans;

    ans = Step(0, num, len);
    return ans;
}

bool isAdditiveNumber(char * num)
{
    bool ans;
    int len = strlen(num);
    if (len <= 2) {
        return false;
    }
    // dfs
    ans = Dfs(num);
    return ans;
}

void main()
{
    // char *s1 = "112358";
    // char *s1 = "199111992";
    // char *s1 = "199001200";199100199
    char *s1 = "199100199";
    int len = strlen(s1);
    char *num = (char *)malloc(len + 1);
    memset(num, 0x0, len + 1);
    strncpy(num, s1, len);
    bool ans = isAdditiveNumber(num);
    printf("ans=%d\n", ans);
    return;
}