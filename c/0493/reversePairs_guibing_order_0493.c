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

int reversePairs_baoli(int* nums, int numsSize)
{
    int cnt = 0;
    // printf("size=%d\n", numsSize);
    for (int i = 0; i < numsSize; i++) {
        long a = nums[i];
        for (int j = i + 1; j < numsSize; j++) {
            long b = nums[j];
            if (a > 2 * b) {
                cnt++;
            }
        }
    }
    return cnt;
}

void Merge(int* nums, int *tmps, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            tmps[k++] = nums[i++];
        } else {
            tmps[k++] = nums[j++];
        }
    }
    while (i <= mid) {
        tmps[k++] = nums[i++];
    }
    while (j <= right) {
        tmps[k++] = nums[j++];
    }
    for (int i = left; i <= right; i++) {
        nums[i] = tmps[i];
    }
}

int MergeSort(int* nums, int *tmps, int left, int right)
{
    int ans = 0;
    if (left >= right) {
        return 0;
    }
    int mid = left + (right - left) / 2;
    ans += MergeSort(nums, tmps, left, mid);
    ans += MergeSort(nums, tmps, mid + 1, right);
    /* 在归并排序的过程中，把left/right两个有序上升区间的符合条件个数的值算出来 */
    int lefti = left;
    int rightj = mid + 1;
    while (lefti <= mid && rightj <= right) {
        if ((long)nums[lefti] > 2 * (long)nums[rightj]) {
            ans += mid - lefti + 1;
            rightj++;
        } else {
            lefti++;
        }
    }

    Merge(nums, tmps, left, mid, right);
    return ans;
}

int reversePairs(int* nums, int numsSize)
{
    int ans = 0;
    int *tmps = (int *)malloc(sizeof(int) * numsSize);
    ans = MergeSort(nums, tmps, 0, numsSize - 1);
    free(tmps);
    return ans;
}

int main()
{
    int ret;
    int a[] = {1, 3, 2, 3, 1};
    ret = reversePairs(a, sizeof(a) / sizeof(int));
    int b[] = {2,4,3,5,1};
    ret = reversePairs(b, sizeof(b) / sizeof(int));
    // printf("ret=%s\n", ret);
    return 0;
}