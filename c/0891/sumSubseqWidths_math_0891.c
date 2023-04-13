#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/*  算法1：数学方法： 先排个序，然后总个数为：
    for (选一个最大值)
        for (选一个最小值)
            (max - min) * (C1/n-1, C2/n-2, ... Cn-2/n-2)
    空间复杂度：O(N + M)；时间复杂度：极限情况下：O(20000 * M)
    结果：58/64
    数学2：针对上面的公式进行化简，没看特别懂，但是考试时，注意直接跳出
*/

/* 算法1
*/
#define MAX_MOD 1000000007
void PrintArray(int *a, int len)
{
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}
#define MAX_MOV 32
#define MAX_NUM 20001
long long g_npow[MAX_NUM];
int g_first = 0;

void PreInitNValue()
{
    if (g_first == 0) {
        memset(g_npow, 0x0, sizeof(int) * MAX_NUM);
        g_npow[0] = 1;
        for (int i = 1; i < MAX_NUM; i++) {
            g_npow[i] = g_npow[i - 1] * 2 % MAX_MOD;
        }
        g_first = 1;
    }
}

int sumSubseqWidths1(int* A, int ASize)
{
    int ret = 0;
    qsort(A, ASize, sizeof(int), Cmp);
    PrintArray(A, ASize);
    PreInitNValue();
    if (ASize <= 1) {
        return 0;
    }
    if (ASize == 2) {
        return A[0] - A[1];
    }
    int max, min;
    long long c;
    long long sum = 0;
    for (int i = 0; i < ASize; i++) {
        max = A[i];
        for (int j = ASize - 1; j > i; j--) {
            min = A[j];
            int n = j - i - 1;
            c = g_npow[n];
            c = c * (max - min) % MAX_MOD;
            sum = (sum + c) % MAX_MOD;
        }
    }
    return (int)sum;
}

int sumSubseqWidths(int* A, int ASize)
{
    int ret = 0;
    qsort(A, ASize, sizeof(int), Cmp);
    PrintArray(A, ASize);
    if (ASize <= 1) {
        return 0;
    }
    if (ASize == 2) {
        return A[1] - A[0];
    }
    long long sum = 0;
    long long p = 1; // 2的j次方
    long long item1 = 0;
    for (int i = 0; i < ASize; i++) {
        sum = (sum + A[i] * (p - 1) - item1) % MAX_MOD;
        p = (p << 1) % MAX_MOD;
        item1 = (item1 * 2 + A[i]) % MAX_MOD;
    }
    return (int)((sum + MAX_MOD) % MAX_MOD);
}

void main()
{
    int a[] = {5,1,2,3,4};
    int ret = sumSubseqWidths(a, sizeof(a) / sizeof(int));
    printf("ret = %d\n", ret);
}