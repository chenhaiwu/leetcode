#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

/* 暴力居然通过了，求包含nums[i]的最大值，然后求每个点，比较最大值，注意一个元素也可以的情况，所以求max要在第一层也检查 */
int maxProduct_1(int* nums, int numsSize)
{
    int ret = INT_MIN;
    int ji;
    for (int i = 0; i < numsSize; i++) {
        ji = nums[i];
        ret = MAX(ret, nums[i]);
        for (int j = i + 1; j <numsSize; j++) {
            ji *= nums[j];
            ret = MAX(ret, ji);
        }
    }
    return ret;
}

/* dp算法，因为有正负，本质上绝对值肯定是最大的，但是不知道负数个数，所以比较空间想到维护一个最大值，及一个最小值
    关键是最大值及最小在算法过程中的swap。
    如果遇到了一个负数，那么可以把本轮迭代的最大值变成1，最小值为：上一次的最大值，所以也就和上一个状态相关
 */
int maxProduct(int* nums, int numsSize)
{
    int ret = INT_MIN;
    int curMax = 1;
    int curMin = 1;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < 0) {
            int tmp = curMin;
            curMin = curMax;
            curMax = tmp;
        }
        curMax = MAX(nums[i], curMax * nums[i]);
        curMin = MIN(nums[i], curMin * nums[i]);
        ret = MAX(curMax, ret);
    }
    return ret;
}

/*
int main()
{
    int nums[] = {2,3,-2,4, -5};
    int ret = maxProduct(nums, sizeof(nums) / sizeof(int));
    return ret;
}
*/