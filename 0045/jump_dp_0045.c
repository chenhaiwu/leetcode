#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

/* 
 * ˼·����0��λ�ÿ�ʼ��һ��һ����������������ֵ�����ǹ̶��ģ��������óɿ����ӵģ�Ȼ����б�����ֻҪ��ǰ��ֵ�����һ����������
 * ��ֵ�޸ĵ��߼���ȡÿһ�������㵱ǰ�Ŀ��������ֵ�����ϸ������ֵ������ֵ��
 */
#define MAX_NUM 10
unsigned int g_dp[MAX_NUM];

int jump_1(int* nums, int numsSize)
{
    if (numsSize == 0 || numsSize == 1) {
        return 0;
    }
    memset(g_dp, INT_MAX, sizeof(int) * numsSize);
    g_dp[0] = 0;
    int lasttill = 0;

    for (int i = 0; i < numsSize; i++) {
        int till = nums[i] + i;
        if (till >= numsSize - 1) {
            return g_dp[i] + 1;
        } else if (till > lasttill) {
            for (int j = i + 1; j <= till && j < numsSize; j++) {
                g_dp[j] = MIN(g_dp[j], g_dp[i] + 1);
            }
        }
        lasttill = till;
    }
    return g_dp[numsSize - 1];
}

int jump(int* nums, int numsSize)
{
    if (numsSize == 0 || numsSize == 1) {
        return 0;
    }
    int begin = 0;
    int end = 1;
    int ans = 0;
    int till = 0;
    while (end < numsSize) {
        for (int i = begin; i < end; i++) {
            till = MAX(till, nums[i] + i);
        }
        begin = end;
        end = till + 1;
        ans++;
    }
    return ans;
}

int main()
{
    int a[] = {3,2,1,1,4};
    int ret = jump(a, sizeof(a) / sizeof(int));
    printf("ret=%d\n", ret);
    return 0;
}