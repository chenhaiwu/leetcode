#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/*  �㷨1����������
    �ռ临�Ӷȣ�O(1)��ʱ�临�Ӷȣ���������£�O(N * N)
    �㷨2��kadane�㷨��������jΪ����������Ӵ��ͣ���
    ���г���i+1��������к� = max(�Ե�i+1������β�����кͣ� ���г���i��������к�)
    �ռ临�Ӷȣ�O(1)��ʱ�临�Ӷȣ���������£�O(N)
    �㷨������
���������飬 ����֮ǰ�������������� max_ending_here, max_so_far
���� max_ending_here ���ڼ�¼���������У� ����ѵ�ǰԪ�� x ǿ�ƹ涨Ϊ�����е����һ��Ԫ��ʱ�� ���ҵ�����������е��ܺ��Ƕ���
������������������б�Ȼ����һ����βԪ�أ� ����ֻ��Ҫ��ÿ��λ�ü������ max_ending_here �У� �ҵ����ֵ�� ����ȫ�ֵ���������е�ֵ��
max_so_far ���ڼ�¼���������У� �����ֵ����� max_ending_here
һ�α���֮�� ���� max_so_far �д洢�ļ�Ϊ�����Ƭ�εĺ�ֵ��

    �Ƚ�������в�֣� ָ��������ĳһ��Ԫ�� A[i] ��Ϊ��������е�ĩβԪ��ʱ�� ���ҵ�����������е����ֵ�Ƕ���
�����ͻᷢ�֣� A[i] ��ΪĩβԪ��ʱ���ҵ������������ subarrayisubarray_isubarray 
i �� ��ȻΪA[i] �������� A[i-1] ��ΪĩβԪ��ʱ���ҵ������������ subarrayi?1subarray_{i-1}subarray 
i?1  ƴ���� A[i]��������ֻ��Ҫ��ͷ��β�������飬 ���μ����ÿһ��λ�õ� A[i] ��ΪĩβԪ��ʱ�� ���ҵ���������������ֵ max_ending_here_{i}, �����ڴ˻����ϼ���� A[i+1] ��ΪĩβԪ��ʱ�� ���ҵ���������������ֵ max_ending_here_{i+1}, ����һ�α����Ĺ����У� ��¼��max_ending_here �е����ֵ����ȫ����������е����ֵ

*/

/* �㷨1
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

/* �㷨2
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

// �㷨3 DP
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_NODE 50000
//0: sell, 1: buy, dp[i][j] ��ʾ��ǰ״̬����i��ʱ�ڴ����Ǯ�����ֵ
int g_dp[MAX_NODE][2];

int maxProfit(int* prices, int pricesSize)
{
    if (pricesSize == 0) return 0;
    g_dp[0][0] = 0; //sell
    g_dp[0][1] = -prices[0]; //buy
    for (int i = 1; i < pricesSize; i++) {
        g_dp[i][0] = MAX(g_dp[i - 1][0], g_dp[i - 1][1] + prices[i]);
        // ע�⣺��Ϊ��Ŀ����ֻ�ܽ���һ�Σ����״ֻ̬���ܴ� 1 �� 0�������ܴ� 0 �� 1
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