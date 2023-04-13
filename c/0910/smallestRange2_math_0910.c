#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

/* 题目中一定存在一个点A[i]，使得i左边的点-k，右边的点+k，然后可以获取本题的解。
 * 那本题的解一定是在最大值-最小值，最大值，可能是a[i] + k, a[n-1]+k，最小值为a[0]+k, a[i+1]-k
 * 循环的最大次数为n-1，当i=n-1时，表示原来的最大值-最小值就是答案，可以用于初始值
 */

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;

    return ta > tb;
}

int smallestRangeII(int* A, int ASize, int K)
{
    PrintArray(A, ASize);
    qsort(A, ASize, sizeof(int), Cmp);
    PrintArray(A, ASize);
    int ans = A[ASize - 1] - A[0];
    for (int i = 0; i < ASize - 1; i++) {
        int a = A[i];
        int b = A[i + 1];
        int mx = MAX(a + K, A[ASize - 1] - K);
        int mn = MIN(A[0] + K, b - K);
        ans = MIN(ans, mx - mn);
        // printf("mx=%d, mn=%d,ans=%d\n", mx, mn, ans);
    }
    return ans;
}

int main()
{
    int nums[5] = {1,3,6};
    // int nums[] = {10,3,2,1,9,8,7,11,13,16};
    int retsize = smallestRangeII(nums, sizeof(nums) / sizeof(int), 3);
    return 0;
}
