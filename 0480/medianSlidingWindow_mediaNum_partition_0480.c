#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* 
 * 这题，我们知道，前后两个区间的数，其实不一定要有序，right区间都比left区间要大就行了。
 * 所以，我们没必要进行qsort，只要找到中位数，能区分原来的数在哪个区间即可。然后对原来的数，
 * 小于大于中位数的，分别用前项指针定位即可。但是不能使用二分法，因为有可能有些值相等，要采用三分法，
 * 保证相等的值，都放到中间来。三分法就不写了，也不会更快。
 */

void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(int *nums, int low, int high)
{
    int midIdx = low;
    int pivot = nums[low];
    for (int i = low + 1; i <= high; i++) {
        if (nums[i] < pivot) {
            if (i != midIdx + 1) {
                Swap(&nums[i], &nums[midIdx + 1]);
            }
            midIdx++;
        }
    }
    Swap(&nums[low], &nums[midIdx]);
    return midIdx;
}

int GetTargetPosVal(int *nums, int low, int high, int targetIdx)
{
    while (1) {
        int pos = Partition(nums, low, high);
        if (pos == targetIdx) {
            break;
        } else if (pos < targetIdx) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    return nums[targetIdx];
}

void CopyKValues(int *tmps, int* nums, int start, int k)
{
    for (int i = 0; i < k; i++) {
        tmps[i] = nums[start + i];
    }
}

/* 这样做超时的原因是：如果是偶数时，get两次中位数，导致超时，现在只是在取得中位数后，
 * 再对后面的一半数取个最小值，虽然时间也有1300ms左右，但还是通过了。
*/
double* medianSlidingWindow_1_31_41(int* nums, int numsSize, int k, int* returnSize)
{
    *returnSize = numsSize - k + 1;
    double *ret = (double *)malloc(sizeof(double) * numsSize);
    int *tmps = (int *)malloc(sizeof(int) * k);
    int targetmid1 = (k - 1) / 2;
    int targetmid2 = k / 2;
    for (int i = 0; i <= numsSize - k; i++) {
        CopyKValues(tmps, nums, i, k);
        if (k % 2 == 1) {
            PrintArray(tmps, k);
            int v1 = GetTargetPosVal(tmps, 0, k - 1, targetmid1);
            ret[i] = (double)v1;
        } else {
            PrintArray(tmps, k);
            int v1 = GetTargetPosVal(tmps, 0, k - 1, targetmid1);
            int v2 = GetTargetPosVal(tmps, 0, k - 1, targetmid2);
            ret[i] = ((double)v1 + (double)v2) / 2;
        }
    }
    free(tmps);
    return ret;
}

double GetTargetPosVal_2(int *nums, int numsSize, int low, int high, int targetIdx, bool isOdd)
{
    if (numsSize == 1) {
        return (double)nums[0];
    }
    // if (numsSize == 2) {
    //     return ((double)nums[0] + (double)nums[1] ) / 2;
    // }
    while (1) {
        int pos = Partition(nums, low, high);
        if (pos == targetIdx) {
            if (isOdd) {
                int v2 = INT_MAX;
                for (int t = targetIdx + 1; t < numsSize; t++) {
                    if (nums[t] >= nums[targetIdx] && nums[t] < v2) {
                        v2 = nums[t];
                    }
                }
                return ((double)nums[targetIdx] + (double)v2) / 2;
            } else {
                return (double)nums[targetIdx]; 
            }
            break;
        } else if (pos < targetIdx) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }    
}

double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    *returnSize = numsSize - k + 1;
    double *ret = (double *)malloc(sizeof(double) * numsSize);
    int *tmps = (int *)malloc(sizeof(int) * k);
    int targetmid1 = (k + 1) / 2 - 1;

    for (int i = 0; i <= numsSize - k; i++) {
        CopyKValues(tmps, nums, i, k);
        if (k % 2 == 1) {
            PrintArray(tmps, k);
            ret[i] = GetTargetPosVal_2(tmps, k, 0, k - 1, targetmid1, false);
        } else {
            PrintArray(tmps, k);
            ret[i] = GetTargetPosVal_2(tmps, k, 0, k - 1, targetmid1, true);
        }
    }
    free(tmps);
    return ret;
}

int main()
{
    int a[] = {1,2,3,4,2,3,1,4,2};
    int aSize = sizeof(a) / sizeof(int);
    int k = 3;
    int retSize;
    double *ret = medianSlidingWindow(a, aSize, k, &retSize);
    for (int i = 0; i < retSize; i++) {
        printf("%lf ", ret[i]);
    }
    printf("\n");
    free(ret);
    return 0;
}