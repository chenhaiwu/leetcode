#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/*  算法1：暴力方法
    空间复杂度：O(1)；时间复杂度：极限情况下：O(N * N)
    算法2：kadane算法，计算以j为结束的最大子串和，则
    数列长度i+1的最大子列和 = max(以第i+1个数结尾的子列和， 数列长度i的最大子列和)
    空间复杂度：O(1)；时间复杂度：极限情况下：O(N)
    算法描述：
遍历该数组， 遍历之前设置了两个变量 max_ending_here, max_so_far
其中 max_ending_here 用于记录遍历过程中， 如果把当前元素 x 强制规定为子数列的最后一个元素时， 能找到的最大子数列的总和是多少
由于真正的最大子数列必然存在一个结尾元素， 所以只需要从每个位置计算出的 max_ending_here 中， 找到最大值， 就是全局的最大子数列的值。
max_so_far 用于记录遍历过程中， 所发现的最大的 max_ending_here
一次遍历之后， 变量 max_so_far 中存储的即为最大子片段的和值。

    先将问题进行拆分， 指定数组中某一个元素 A[i] 作为最大子数列的末尾元素时， 能找到的最大子数列的求和值是多少
这样就会发现， A[i] 作为末尾元素时能找到的最大子数列 subarrayisubarray_isubarray 
i ， 必然为A[i] 本身，或是 A[i-1] 作为末尾元素时能找到的最大子数列 subarrayi?1subarray_{i-1}subarray 
i?1  拼接上 A[i]所以我们只需要从头到尾遍历数组， 依次计算出每一个位置的 A[i] 作为末尾元素时， 能找到的最大子数列求和值 max_ending_here_{i}, 就能在此基础上计算出 A[i+1] 作为末尾元素时， 能找到的最大子数列求和值 max_ending_here_{i+1}, 在这一次遍历的过程中， 记录下max_ending_here 中的最大值就是全局最大子数列的求和值

*/

/* 算法1
int maxProfit1(int* A, int ASize)
{
    int max = 0;
    int idx;
    for (int i = 0; i < ASize; i++) {
        int sum = 0;
        for (int j = i + 1; j < ASize; j++) {
            sum = A[j] - A[i];
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
int maxProfit(int* A, int ASize)
{
    int maxEndingHere = 0;
    int maxSofar = 0;
    for (int i = 1; i < ASize; i++) {
        int sum = A[i] - A[i - 1];
        maxEndingHere = MAX(maxEndingHere + sum, sum);
        maxSofar = MAX(maxEndingHere, maxSofar);
    }
    return maxSofar;
}

// 算法3 DP
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_NODE 50000
//0: sell, 1: buy, dp[i][j] 表示当前状态下在i天时口袋里的钱的最大值
int g_dp[MAX_NODE][2];

int maxProfit(int* prices, int pricesSize)
{
    if (pricesSize == 0) return 0;
    g_dp[0][0] = 0; //sell
    g_dp[0][1] = -prices[0]; //buy
    for (int i = 1; i < pricesSize; i++) {
        g_dp[i][0] = MAX(g_dp[i - 1][0], g_dp[i - 1][1] + prices[i]);
        // 注意：因为题目限制只能交易一次，因此状态只可能从 1 到 0，不可能从 0 到 1
        g_dp[i][1] = MAX(g_dp[i - 1][1], -prices[i]);
    }
    return g_dp[pricesSize - 1][0];
}

/*
void main()
{
    int a[] = {7,1,5,3,6,4};
    int ret = maxProfit(a, sizeof(a) / sizeof(int));
    printf("ret = %d\n", ret);
}
*/