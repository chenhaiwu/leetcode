#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

int FindFirstPos(int *nums, int numsSize)
{
    int i = 0;
    for (i = numsSize - 1; i > 0; i--) {
        if (nums[i] > nums[i - 1]) {
            break;
        }
    }
    return i - 1;
}

int FindMinBigPos(int *nums, int numsSize, int pos)
{
    int min = INT_MAX;
    int idx;
    for (int i = pos + 1; i < numsSize; i++) {
        if (nums[i] > nums[pos] && min > nums[i]) {
            min = nums[i];
            idx = i;
        }
    }
    return idx;
}

void RevertArray(int* nums, int numsSize)
{
    int tmp;
    for (int i = 0; i < numsSize / 2; i++) {
        tmp = nums[i];
        nums[i] = nums[numsSize - 1 - i];
        nums[numsSize - 1 - i] = tmp;
    }
}

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;

    return ta > tb;
}

void nextPermutation(int* nums, int numsSize)
{
    if (numsSize <= 0) {
        return;
    }

    PrintArray(nums, numsSize);

    int firstPos = FindFirstPos(nums, numsSize);
    if (firstPos == -1) {
        RevertArray(nums, numsSize);
        return;
    }
    int minBigPos = FindMinBigPos(nums, numsSize, firstPos);
    int tmp = nums[firstPos];
    nums[firstPos] = nums[minBigPos];
    nums[minBigPos] = tmp;

    PrintArray(nums, numsSize);

    qsort(nums + firstPos + 1, numsSize - firstPos - 1, sizeof(int), Cmp);

    return;
}

int main()
{
    int nums[] = {3, 3, 5};
    nextPermutation(nums, sizeof(nums) / sizeof(int));
    PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
