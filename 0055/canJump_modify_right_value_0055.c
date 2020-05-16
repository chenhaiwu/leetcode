#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)

/* 
 * 思路：从0个位置开始，一步一步往后跳，但是右值并不是固定的，把它设置成可增加的，然后进行遍历，只要当前的值是最后一个，就跳出
 * 右值修改的逻辑：取每一步，计算当前的可跳的最大值，不断更新最大值（作右值）
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