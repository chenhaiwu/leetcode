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
    printf("total cnt=%d\n", numsSize);
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int firstMissingPositive(int* nums, int numsSize)
{
    int ret = numsSize + 1;
    for (int i = 0; i < numsSize; i++) {
        while (nums[i] > 0 && nums[i] < numsSize + 1 && nums[i] != nums[nums[i] - 1]) {
            swap(&nums[i], &(nums[nums[i] - 1]));
        }
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    return ret;
}

int main()
{
    int nums[] = {3,4,-1,1};
    int ret = firstMissingPositive(nums, sizeof(nums) / sizeof(int));
    return ret;
}
