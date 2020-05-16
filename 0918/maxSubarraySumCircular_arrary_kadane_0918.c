#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/*  �㷨1�������㷨����i��ʼ��j�������ĺͣ�����¼���ֵ
    �ռ临�Ӷȣ�O(1)��ʱ�临�Ӷȣ���������£�O(N * N)
    �㷨2�� kadane �㷨��������jΪ����������Ӵ��ͣ���
    ���г���i+1��������к� = max(�Ե�i+1������β�����кͣ� ���г���i��������к�)
    �ռ临�Ӷȣ�O(1)��ʱ�临�Ӷȣ���������£�O(N)
    kadane�㷨�����Kadane�㷨�ǳ��򵥣��ܺ���⡣�����������������ֵ����޷����������������һ�֣�
���ֵmax��ԭ�����С�
���ֵmax�ڻ��������С�
��һ������޷Ǿ���Kadane�㷨������˼���ڶ��������������������ΪA����ôA[0]��A[A.length-1]�ڵڶ��������һ���ᱻѡ�С���ô���ǵ�˼·�����ҵ�һ��A��subArray���������subArray����С������i��subArray����㣬j��subArray���ص㣬��ôi>=0&&j<=A.length-2�������A[1,A.length-2]��Kadane������
*/

/* �㷨1
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

/* �㷨2
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