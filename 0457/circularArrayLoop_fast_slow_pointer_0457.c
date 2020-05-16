#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

int GetNext(int* nums, int numsSize, int i)
{
    int ret = (((nums[i] + i) % numsSize) + numsSize) % numsSize;
    return ret;
}

bool circularArrayLoop1(int* nums, int numsSize)
{
    bool ret = false;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            continue;
        }
        int slow = i;
        int fast = GetNext(nums, numsSize, i);
        int v = nums[i];
        while (v * nums[fast] > 0 && v * nums[GetNext(nums, numsSize, fast)] > 0) {
            if (slow == fast) {
                if (slow == GetNext(nums, numsSize, slow)) {
                    break;
                }
                return true;
            }
            slow = GetNext(nums, numsSize, slow);
            int fast1 = GetNext(nums, numsSize, fast);
            fast = GetNext(nums, numsSize, fast1);
        }
        /* 优化，如果方向相同的所有点，不存在环，下次再循环时，不再进入快慢指针比较 */
        slow = i;
        while (v * nums[slow] > 0) {
            nums[slow] = 0;
            slow = GetNext(nums, numsSize, slow);
        }
    }
    return ret;
}

#define MAGIC_NUM 100000008

bool dfs(int* nums, int numsSize, int dir, int i)
{
    if (nums[i] == 0) {
        return false;
    }
    if (nums[i] == MAGIC_NUM) {
        return true;
    }
    int nDir = nums[i] > 0 ? 1 : -1;
    if (nDir != dir) {
        return false;
    }
    int next = GetNext(nums, numsSize, i);
    nums[i] = MAGIC_NUM;
    if (next != i && dfs(nums, numsSize, nDir, next)) {
        return true;
    }
    nums[i] = 0;
    return false;
}

bool circularArrayLoop(int* nums, int numsSize)
{
    bool ret = false;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            continue;
        }
        int dir = nums[i] > 0 ? 1 : -1;
        if (dfs(nums, numsSize, dir, i)) {
            return true;
        }
    }
    return ret;
}


int main()
{
    int A[] = {2,-1,1,2,2};
    bool ret = circularArrayLoop(A, sizeof(A) / sizeof(int));
    return ret;
}