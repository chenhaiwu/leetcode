#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_NUM 20002
int g_sufixmin[MAX_NUM];

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

/* 维持两个数组，从左到右，到当前i位置的最大值；从右到左，到当前i位置的最小值，当前面的最大值小于后面的最小值，则可以分在
 * 一个块里。最后还要再增加1，因为最后一个数可以单独一个
 */
void PreHandle(char *s)
{
    int len = strlen(s);
    g_sufixmin[len] = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == '0') {
            g_sufixmin[i] = g_sufixmin[i + 1] + 1;
        } else {
            g_sufixmin[i] = g_sufixmin[i + 1];
        }
    }
}

bool FindNext1Pos(char *s, int start, int *ret)
{
    int bFlag = false;
    int pos = start;
    int len = strlen(s);
    int i;
    for (i = start; i < len; i++) {
        if (s[i] == '1') {
            bFlag = false;
            break;
        }
    }
    *ret = i;
    return bFlag;
}

int GetTotal(char * s, int start)
{
    int ret = 0;
    int cur = start;
    int first1Pos;
    int find1to0;
    int find0to1;
    bool bFind = FindNext1Pos(s, cur, &first1Pos);
    if (bFind) {
        find1to0 = 1 + GetTotal(s, first1Pos);
        find0to1 = g_sufixmin[first1Pos];
        ret = MIN(find0to1, find1to0);
        return ret;
    } else {
        return 0;
    }
    return ret;
}

int minFlipsMonoIncr_1(char * s)
{
    PreHandle(s);
    int ret = GetTotal(s, 0);
    return ret;
}

#define MAX_NUM_2 20002
int g_px[MAX_NUM_2];
int minFlipsMonoIncr_2(char * s)
{
    int len = strlen(s);
    g_px[0] = 0;
    for (int i = 0; i < len; i++) {
        g_px[i + 1] = g_px[i] + (s[i] == '1' ? 1 : 0);
    }
    int ans = INT_MAX;
    for (int i = 0; i <= len; i++) {
        ans = MIN(ans, g_px[i] + (len - i) - (g_px[len] - g_px[i]));
    }
    return ans;
}

int minFlipsMonoIncr(char * s)
{
    int len = strlen(s);
    int dp_0 = 0;
    int dp_1 = 0;
    int ans = INT_MAX;
    for (int i = 0; i < len; i++) {
        if (s[i] == '1') {
            dp_0 = dp_0 + 1;
            dp_1 = MIN(dp_1, dp_0);
        } else {
            dp_1 = MIN(dp_1 + 1, dp_0 + 1);
        }
    }
    return MIN(dp_0, dp_1);
}




int main()
{
    int nums[5] = {4,2,1,1};
    int retsize = maxChunksToSorted(nums, sizeof(nums) / sizeof(int));
    return 0;
}
