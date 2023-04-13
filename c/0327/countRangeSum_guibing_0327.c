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

int countRangeSum_baoli(int* nums, int numsSize, int lower, int upper)
{
    int ans = 0;
    long *sumArray = (long *)malloc(sizeof(long) * (numsSize + 1));
    sumArray[0] = 0;
    for (int i = 1; i <= numsSize; i++) {
        sumArray[i] = sumArray[i - 1] + nums[i - 1];
        for (int j = 1; j <= i; j++) {
            long curj2i = sumArray[i] - sumArray[j - 1];
            if (curj2i <= upper && curj2i >= lower) {
                ans++;
            }
        }
    }
    free(sumArray);
    return ans;
}

void Merge(long *sumArray, long *tmpArray, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (sumArray[i] <= sumArray[j]) {
            tmpArray[k++] = sumArray[i++];
        } else {
            tmpArray[k++] = sumArray[j++];
        }
    }
    while (i <= mid) {
        tmpArray[k++] = sumArray[i++];
    }
    while (j <= right) {
        tmpArray[k++] = sumArray[j++];
    }
    for (int i = left; i <= right; i++) {
        sumArray[i] = tmpArray[i];
    }
}

int MergeSort(long *sumArray, long *tmpArray, int left, int right, int lower, int upper)
{
    int ans = 0;
    if (left >= right) {
        return ans;
    }
    int mid = left + (right - left) / 2;
    ans += MergeSort(sumArray, tmpArray, left, mid, lower, upper);
    ans += MergeSort(sumArray, tmpArray, mid + 1, right, lower, upper);
    /* 插入在归并排序中的计算序列个数 */
    int start = mid + 1;
    int end = mid + 1;
    int from = left;
    PrintArray(sumArray, 4);
    while (from <= mid) {
        while (start <= right && sumArray[start] - sumArray[from] < lower) {
            start++;
        }
        while (end <= right && sumArray[end] - sumArray[from] <= upper) {
            end++;
        }
        ans += end - start;
        from++;
    }

    Merge(sumArray, tmpArray, left, mid, right);
    return ans;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper)
{
    int ans = 0;
    long *sumArray = (long *)malloc(sizeof(long) * (numsSize + 1));
    sumArray[0] = 0;
    for (int i = 1; i <= numsSize; i++) {
        sumArray[i] = sumArray[i - 1] + nums[i - 1];
    }
    PrintArray(sumArray, numsSize + 1);
    long *tmpArray = (long *)malloc(sizeof(long) * (numsSize + 1));
    ans = MergeSort(sumArray, tmpArray, 0, numsSize, lower, upper);
    PrintArray(sumArray, numsSize + 1);
    free(tmpArray);
    free(sumArray);
    return ans;
}


int main()
{
    int a[] = {-2, 5, -1};
    int lower = -2;
    int upper = 2;
    int ret = countRangeSum(a, sizeof(a) / sizeof(int), lower, upper);
    // printf("ret=%s\n", ret);
    return 0;
}