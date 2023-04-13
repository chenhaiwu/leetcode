#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/*  算法1：暴力算法，从i开始，j结束，的和，并记录最大值
    空间复杂度：O(1)；时间复杂度：极限情况下：O(N * N)
    算法2： kadane 算法，计算以j为结束的最大子串和，则
    数列长度i+1的最大子列和 = max(以第i+1个数结尾的子列和， 数列长度i的最大子列和)
    空间复杂度：O(1)；时间复杂度：极限情况下：O(N)
    kadane算法，如果Kadane算法非常简单，很好理解。在这个题的条件下最大值结果无非是以下两种情况的一种：
最大值max在原数组中。
最大值max在环形数组中。
第一种情况无非就是Kadane算法。我们思考第二种情况。假设输入数组为A，那么A[0]和A[A.length-1]在第二种情况下一定会被选中。那么我们的思路就是找到一个A的subArray并且让这个subArray和最小。假设i是subArray的起点，j是subArray的重点，那么i>=0&&j<=A.length-2。这就是A[1,A.length-2]的Kadane问题了
*/

/* 算法1
int maxSubarraySumCircular(int* A, int ASize)
{
    int max = INT_MIN;
    int idx;
    for (int i = 0; i < ASize; i++) {
        int sum = 0;
        for (int j = i; j < i + ASize; j++) {
            idx = j < ASize ? j : j - ASize;
            sum += A[idx];
            if (max < sum) {
                max = sum;
            }
        }
    }
    return max;
}
*/

/* 算法2
*/
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)
int maxSubarraySumCircular(int* A, int ASize)
{
    int sum = A[0];
    int max1 = A[0];
    int maxEndingHere = A[0];
    for (int i = 1; i < ASize; i++) {
        sum += A[i];
        maxEndingHere = MAX(maxEndingHere + A[i], A[i]);
        max1 = MAX(maxEndingHere, max1);
    }

    int min2 = A[1];
    int minEndingHere = A[1];
    for (int i = 2; i < ASize - 1; i++) {
        minEndingHere = MIN(minEndingHere + A[i], A[i]);
        min2 = MIN(minEndingHere, min2);
    }
    int max2 = sum - min2;
    return MAX(max1, max2);
}

void main()
{
    int a[] = {9,1,-2,3};
    int ret = maxSubarraySumCircular(a, sizeof(a) / sizeof(int));
    printf("ret = %d\n", ret);
}