#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

/* ������Ȼͨ���ˣ������nums[i]�����ֵ��Ȼ����ÿ���㣬�Ƚ����ֵ��ע��һ��Ԫ��Ҳ���Ե������������maxҪ�ڵ�һ��Ҳ��� */
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

/* dp�㷨����Ϊ�������������Ͼ���ֵ�϶������ģ����ǲ�֪���������������ԱȽϿռ��뵽ά��һ�����ֵ����һ����Сֵ
    �ؼ������ֵ����С���㷨�����е�swap��
    ���������һ����������ô���԰ѱ��ֵ��������ֵ���1����СֵΪ����һ�ε����ֵ������Ҳ�ͺ���һ��״̬���
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