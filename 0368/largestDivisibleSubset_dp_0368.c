#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define DEGUG_CHW 0
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

int FuncMin(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

#define MAX_LEN 1001

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}
int g_dp[MAX_LEN];
int g_last[MAX_LEN];

int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize)
{
    int ans = 0, maxIdx;
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    qsort(nums, numsSize, sizeof(int), Cmp);
    for (int i = 0; i < numsSize; i++) {
        g_dp[i] = 1;
        g_last[i] = -1;
    }
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0 && g_dp[i] <= g_dp[j]) {
                g_dp[i] = g_dp[j] + 1;
                g_last[i] = j;
            }
        }
        if (g_dp[i] > ans) {
            ans = g_dp[i];
            maxIdx = i;
        }
    }
    int *ret = (int *)malloc(sizeof(int) * ans);
    int k = 0;
    int maxV = nums[maxIdx];
    for (int i = maxIdx; i != -1; i = g_last[i]) {
        ret[k++] = nums[i];
    }
    *returnSize = ans;
    return ret;
}

int main()
{
    int a[] = {1, 2, 5, 4};
    int retSize;
    int *ret = largestDivisibleSubset(a, sizeof(a) / sizeof(int), &retSize);
    PrintArray(ret, retSize);
    free(ret);
    // printf("ret=%d\n");
    return 0;
}
