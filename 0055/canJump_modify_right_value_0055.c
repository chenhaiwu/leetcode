#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)

/* 
 * ˼·����0��λ�ÿ�ʼ��һ��һ����������������ֵ�����ǹ̶��ģ��������óɿ����ӵģ�Ȼ����б�����ֻҪ��ǰ��ֵ�����һ����������
 * ��ֵ�޸ĵ��߼���ȡÿһ�������㵱ǰ�Ŀ��������ֵ�����ϸ������ֵ������ֵ��
 */
bool canJump(int* nums, int numsSize)
{
    if (numsSize == 0) {
        return true;
    }
    int right = nums[0];
    for (int i = 0; i <= right; i++) {
        int now = nums[i] + i;
        right = MAX(right, now);
        if (now >= numsSize - 1) {
            return true;
        }
    }
    return false;
}

int main()
{
    int a[] = {3,2,1,0,4};
    int ret = canJump(a, sizeof(a) / sizeof(int));
    printf("ret=%d\n", ret);
    return 0;
}