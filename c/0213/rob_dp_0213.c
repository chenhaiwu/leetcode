
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

int Max(int a, int b)
{
    if (a < b) {
        return b;
    }
    return a;
}

int Min(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

#define MAX_LEN 5001

int g_dp[MAX_LEN];

// ���@�ƪ��Фl�A�]�O198?�ت�����
int robsingle(int* nums, int numsSize)
{
    if (numsSize == 0) {
        return 0;
    }
    if (numsSize == 1) {
        return nums[0];
    }
    g_dp[0] = nums[0];
    g_dp[1] = Max(nums[0], nums[1]);
    for (int i = 2; i < numsSize; i++) {
        if (g_dp[i - 2] + nums[i] > g_dp[i - 1]) {
            g_dp[i] = g_dp[i - 2] + nums[i];
        } else {
            g_dp[i] = g_dp[i - 1];
        }
    }
    /* ?������k�A?�q�m?idx???�A�]?�̦Z�@��??�n��?��0�Ĥ����A�ҥH�p�G?�F??�A?���ݭn�A��nums[0] */
    return g_dp[numsSize - 1];
}

// ?���O??���A�i�H��ҡA����0�ġA�M����0�Ī��Фl�A�M�Z���w���̤j��
int rob(int* nums, int numsSize)
{
    if (numsSize == 0) {
        return 0;
    }
    if (numsSize == 1) {
        return nums[0];
    }
    if (numsSize == 2) {
        return Max(nums[0], nums[1]);
    }
    int p0sel = robsingle(nums, numsSize - 1);
    int p0unsel = robsingle(&nums[1], numsSize - 1);
    return Max(p0sel, p0unsel);
}

int main()
{
    int a[] = {2,3,2};
    int ret = rob(a, sizeof(a) / sizeof(int));
    // PrintArray(ret, retSize);
    // free(ret);
    printf("ret=%d\n", ret);
    return 0;
}