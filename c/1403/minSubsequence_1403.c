/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdio.h>


// #define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

int Cmp(void *a, void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return tb - ta;
}

int* minSubsequence(int* nums, int numsSize, int* returnSize)
{
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }
    qsort(nums, numsSize, sizeof(int), Cmp);
    PrintArray(nums, numsSize);
    int halfsum = 0;
    int i = 0;
    for (i = 0; i < numsSize; i++) {
        halfsum += nums[i];
        if (halfsum > sum - halfsum) {
            break;
        }
    }
    int len = i + 1;
    *returnSize = len;
    int *ret = (int *)malloc(sizeof(int) * len);
    for (int k = 0; k < len; k++) {
        ret[k] = nums[k];
    }
    return ret;
}

// int main()
// {
//     int a[] = {4,3,10,9,8};
//     // int b[] = {10, 11, 2};
//     int len;
//     int *ans = minSubsequence(a, sizeof(a) / sizeof(int), &len);
//     PrintArray(ans, len);
//     free(ans);
//     return 0;
// }