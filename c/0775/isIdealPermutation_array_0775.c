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

/* 暴力超时：通过191/208 case情况：
 * 一个局部倒置也是一个全局倒置，因此只需要检查有没有非局部倒置就可以了。
 * 这里的非局部倒置指的是 A[i] > A[j], i < j，其中 j - i > 1 
 * */
bool isIdealPermutation_1(int* A, int ASize)
{
    bool ret = true;
    for (int i = 0; i < ASize; i++) {
        for (int j = i + 2; j < ASize; j++) {
            if (A[i] > A[j]) {
                return false;
            }
        }
    }
    return ret;
}

/* 最小值时：通过从右边往左边找，当前是和前面的2个比，只要前面的一个值比后面的最小值大，
 * 则说明，前面的 i -2个值，存在非绝对倒置情况，则返回false.
 * */
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)
bool isIdealPermutation_2(int* A, int ASize)
{
    int minV = ASize;
    bool ret = true;
    for (int i = ASize - 1; i >= 2; i--) {
        minV = MIN(minV, A[i]);
        if (A[i - 2] > minV) {
            return false;
        }
    }
    return ret;
}

/* 数学归纳法：
 * 假设有一个长度为 n，其中元素为 0 到 n-1 的数组。对于这种数组，定义 理想 排列为该数组的一个不存在非局部倒置的排列。
 * 对于 理想 排列，0 应该在哪里呢？ 如果 0 的下标大于等于 2，一定会有 A[0] > A[2] = 0，这是一个非局部倒置。所以 0 只能出现 * 在下标 0 或者下标 1。当 A[1] = 0，显然 A[0] = 1，否则就会有 A[0] > A[j] = 1，这也是一个非局部倒置。当 A[0] = 0，这时问* 题就转化成了一个子问题。
 * 根据上述讨论，可以归纳出 理想 数组的充分必要条件为 Math.abs(A[i] - i) <= 1
*/
bool isIdealPermutation(int* A, int ASize)
{
    bool ret = true;
    for (int i = 0; i < ASize; i++) {
        if (abs(A[i] - i) > 1) {
            return false;
        }
    }
    return ret;
}

int main()
{
    int nums[] = {2,3,1,2,4,3};
    int retsize = isIdealPermutation(nums, sizeof(nums) / sizeof(int));
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
