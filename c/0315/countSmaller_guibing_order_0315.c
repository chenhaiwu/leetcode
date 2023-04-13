#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

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

int* countSmaller_baoli(int* nums, int numsSize, int* returnSize)
{
    *returnSize = numsSize;
    if (numsSize == 0) {
        return NULL;
    }
    int *ret = (int *)malloc(sizeof(int) * numsSize);
    if (numsSize == 1) {
        ret[0] = 0;
        return ret;
    }
    ret[numsSize - 1] = 0;
    for (int i = numsSize - 2; i >= 0; i--) {
        int ans = 0;
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] < nums[i]) {
                ans++;
            }
        }
        ret[i] = ans;
    }
    return ret;
}

void Merge(int* nums, int *indexs, int *counts, int *tmps, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (nums[indexs[i]] <= nums[indexs[j]]) {
            tmps[k] = indexs[i++];
            counts[tmps[k]] += j - mid - 1;
            k++;
        } else {
            tmps[k++] = indexs[j++];
        }
    }
    while (i <= mid) {
        tmps[k] = indexs[i++];
        counts[tmps[k]] += right - mid;
        k++;
    }
    while (j <= right) {
        tmps[k++] = indexs[j++];
    }
    for (int i = left; i <= right; i++) {
        indexs[i] = tmps[i];
    }
}

int MergeSort(int* nums, int *indexs, int *counts, int *tmps, int left, int right)
{
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    MergeSort(nums, indexs, counts, tmps, left, mid);
    MergeSort(nums, indexs, counts, tmps, mid + 1, right);
    /* 归并排序，已经从小到大有序了，则不必排序 */
    if (nums[indexs[mid]] <= nums[indexs[mid + 1]]) {
        return;
    }
    Merge(nums, indexs, counts, tmps, left, mid, right);
}

int* countSmaller(int* nums, int numsSize, int* returnSize)
{
    *returnSize = numsSize;
    int *indexs = (int *)malloc(sizeof(int) * numsSize);
    int *tmps = (int *)malloc(sizeof(int) * numsSize);
    int *counts = (int *)malloc(sizeof(int) * numsSize);

    for (int i = 0; i < numsSize; i++) {
        indexs[i] = i;
        counts[i] = 0;
        tmps[i] = i;
    }
    PrintArray(nums, numsSize);
    PrintArray(indexs, numsSize);
    MergeSort(nums, indexs, counts, tmps, 0, numsSize - 1);
    free(indexs);
    free(tmps);
    return counts;
}

int main()
{
    int a[] = {5, 2, 6, 1};
    int retSize;
    int *ret = countSmaller(a, sizeof(a) / sizeof(int), &retSize);
    PrintArray(ret, retSize);
    free(ret);
    // printf("ret=%s\n", ret);
    return 0;
}