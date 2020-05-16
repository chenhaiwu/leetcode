#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/* ��ʱ ��ʵ��������һ��Ԫ�أ������ѡ�Ļ������ѡ���Ͳ�ѡ�Ĵ�С��ȡ������
int lengthOfLoop(int *nums, int numsSize, int prev, int curPos)
{
    if (curPos == numsSize) {
        return 0;
    }
    int taken = 0;
    if (nums[curPos] > prev) {
        taken = 1 + lengthOfLoop(nums, numsSize, nums[curPos], curPos + 1);
    }
    int notaken = lengthOfLoop(nums, numsSize, prev, curPos + 1);
    return taken > notaken ? taken : notaken;
}

int lengthOfLIS(int* nums, int numsSize)
{
    //memset(g_memo, -1, sizeof(g_memo));
    // if (numsSize > 20) return 0;
    int max = lengthOfLoop(nums, numsSize, INT_MIN, 0);
    return max;
}
*/

/* ��ʵ��������һ��Ԫ�أ������ѡ�Ļ������ѡ���Ͳ�ѡ�Ĵ�С��ȡ�����ߣ����ϼ��仯����Ҫ�ص��Ǵ�-1��ʼ�ǣ�������0���͸պü��� */
/*
#define MAXNUM 2501 //���Գ�������Сֵ
int g_memo[MAXNUM][MAXNUM];

int lengthOfLoop(int *nums, int numsSize, int prev, int curPos)
{
    if (curPos == numsSize) {
        return 0;
    }
    if (g_memo[prev + 1][curPos] > 0) {
        return g_memo[prev + 1][curPos];
    }
    int taken = 0;
    if (prev < 0 || nums[curPos] > nums[prev]) {
        taken = 1 + lengthOfLoop(nums, numsSize, curPos, curPos + 1);
    }
    int notaken = lengthOfLoop(nums, numsSize, prev, curPos + 1);
    g_memo[prev + 1][curPos] = taken > notaken ? taken : notaken;
    return g_memo[prev + 1][curPos];
}

int lengthOfLIS(int* nums, int numsSize)
{
    memset(g_memo, -1, sizeof(g_memo));

    int max = lengthOfLoop(nums, numsSize, -1, 0);
    return max;
}
*/

/* dp �㷨����Ҫ��˼·�ǣ�dp[i] ��ʾ��i��λ�õģ������ֵΪ���٣���һ����ǰ�����б�num[i]С��Ԫ�أ����е����ֵ+1 */
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MAXNUM 2501 //���Գ�������Сֵ
int g_dp[MAXNUM];
int lengthOfLIS(int* nums, int numsSize)
{
    int max = 0;
    memset(g_dp, 0x0, sizeof(int) * numsSize);
    g_dp[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        int maxTmp = 0;
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                maxTmp = MAX(maxTmp, g_dp[j]);
            }
        }
        g_dp[i] = maxTmp + 1;
        max = MAX(max, g_dp[i]);
    }
    return max;
}


int main()
{
    int nums[] = {10,9,2,5,3,7,101,18};
    int ret = lengthOfLIS(nums, sizeof(nums) / sizeof(int));
    printf("ret=%d\n", ret);
    return ret;
}