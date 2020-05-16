#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define K_MAX 17
int g_sets[K_MAX];
int g_setslen;
int g_sum;
int g_target;

int Compare(void *a, void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta - tb;
}

bool InitCheck(int* nums, int numsSize, int k)
{
    g_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        g_sum += nums[i];
    }
    if (g_sum % k != 0) {
        return false;
    }
    g_target = g_sum / k;
    if (nums[numsSize - 1] > g_target) {
        return false;
    }
    return true;
}

bool Search(int* nums, int row)
{
    if (row < 0) {
        return true;
    }
    /* 取出当前的最大元素，然后查找把他放到哪个set中 */
    int curData = nums[row--];
    for (int i = 0; i < g_setslen; i++) {
        if (g_sets[i] + curData <= g_target) {
            /* 可以放，然后选择放 */
            g_sets[i] += curData;
            bool nextRet = Search(nums, row);
            if (nextRet) {
                return true;
            }
            /* 当前数据是可以放，但是放完后面的不行了，所以选择不放 */
            g_sets[i] -= curData;
        }
        if (g_sets[i] == 0) {
            break;
        }
    }
    return false;
}

bool canPartitionKSubsets(int* nums, int numsSize, int k)
{
    if (!InitCheck(nums, numsSize, k)) {
        return false;
    }
    qsort(nums, numsSize, sizeof(int), Compare);
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    int row = numsSize - 1;
    while (nums[row] == g_target && row >= 0) {
        row--;
        k--;
    }
    g_setslen = k;
    memset(g_sets, 0x0, sizeof(g_sets));
    bool ret = Search(nums, row);
    return ret;
}

void main()
{
    int nums[] = {4, 3, 2, 3, 5, 2, 1};
    int k = 4;
    bool ret = canPartitionKSubsets(nums, sizeof(nums) / sizeof(int), k);
    printf("ret = %d\n", ret);
}