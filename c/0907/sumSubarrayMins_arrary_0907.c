#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/*  �㷨1����ѧ������ ���Ÿ���Ȼ���ܸ���Ϊ��
    for (ѡһ�����ֵ)
        for (ѡһ����Сֵ)
            (max - min) * (C1/n-1, C2/n-2, ... Cn-2/n-2)
    �ռ临�Ӷȣ�O(N + M)��ʱ�临�Ӷȣ���������£�O(20000 * M)
    �����58/64 ��ֻ�ܼ��㵽1000�ͷ��ֳ�ʱ�ˣ���������֧��30000��Ԫ��
    ��ѧ2��ǰ�����ݣ��������飬�뷨

������������ A[j] Ϊ��������С��Ԫ�ص������и��� #(j)����ô������� sum #(j) * A[j]�������Ǳ��뿼�����������ſ��Թ��컥���ཻ�������У��������ֶ�μ��㣬��Ϊһ���������Сֵ���ܲ�Ψһ����

��ͱ�ɿ�����С���±� i <= j ���� A[i], A[i+1], ..., A[j] �� >= A[j] �Լ������±� k >= j ���� A[j+1], A[j+2], ..., A[k] �� > A[j]��

�㷨

���磬A = [10, 3, 4, 5, _3_, 2, 3, 10] ������Ҫ���� #(j = 4)��Ҳ���ǵڶ������� 3 ������ǵ��Ǹ������ǻᷢ�� i = 1 �� k = 5��

�ɴˣ�ʵ�ʵ�����Ϊ #(j) = (j - i + 1) * (k - j + 1) ���� j - i + 1 ѡ�������е���˵� i, i+1, ..., j���� k - j + 1 ѡ�������е��Ҷ˵� j, j+1, ..., k��

����ÿ��ѯ�ʣ�Ҳ���Ǹ��� j ����� (i, k)����һ���������⣬������һ��ջ����������ǻ��ص�������ҵ� i�����ҵ� k ��������֮���ơ�

����ǰ������

������ά��һ��ջ��A �ĵ����½������У���ʵ����ά��һ�� A ���±���������������һ��ѯ�ʣ���ѡ����Ϊ i* - 1������ A[i*] �Ե���˳��洢��

���ڿ��������±� j �����ǿ��԰��� i* �ݼ�˳���������� A[i*] <= A[j]��

���磬���� A = [10, 5, 3, 7, 0, 4, 5, 2, 1, _8_] ��ô������ j = 9 (A[j] = 8)��������һ���洢�߽��ջ������ [-1, 0, 3, 6]������ A[i*] = -inf, 10, 7, 5�������Ǵ�ջ�е��� 6 �� 3 ��Ϊ 5 <= 8 �� 7 <= 8����˵õ�ѯ�ʵı߽�Ϊ i* - 1 = 0��

ע������������Եģ���Ϊֻ���������Դε���ջ�ͳ�ջ��
 
    �����������飬���ڴ浱ǰλ�õ�left, right����߱��Լ�С�ģ��ұ߱��Լ�С�ģ�Ȼ��Ϳ���͡�left����ʹ�õ���������һ��Ԫ��Ϊ-1����������ջ��right����ʹ�õ�����ջ������������ջ��
*/

/* �㷨1
*/
/*
#define MAX_MOD 1000000007
#define MAX_NUM 30001

void PrintArray(int *a, int len)
{
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int GetMin(int *A, int start, int len)
{
    int min = INT_MAX;
    int end = len + start;
    for (int i = start; i < end; i++) {
        if (min > A[i]) {
            min = A[i];
        }
    }
    return min;
}

int sumSubarrayMins1(int* A, int ASize)
{
    int ret = 0;
    // PrintArray(A, ASize);
    long long sum = 0;
    long long p = 1;
    int min = 0;
    for (int win = 1; win <= ASize; win++) {
        for (int i = 0; i <= ASize - win; i++) {
            min = GetMin(A, i, win);
            sum = (sum + min) % MAX_MOD;    
        }
    }
    return (int)(sum);
}
*/

//�㷨2
#define MAX_MOD 1000000007
#define MAX_NUM 30001
typedef struct _stack {
    int arr[MAX_NUM];
    int index;
} Stack;

void StackPush(Stack *s, int a)
{
    s->arr[s->index] = a;
    s->index++;
}

int StackPop(Stack *s)
{
    s->index--;
    return s->arr[s->index];
}

int StackTop(Stack *s)
{
    int idx = s->index - 1;
    return s->arr[idx];
}

bool StackIsEmpty(Stack *s)
{
    return s->index == 0;
}

Stack g_leftstack;
Stack g_rightstack;
int g_left[MAX_NUM];
int g_right[MAX_NUM];

void PrintInfo(int len)
{
    Stack *stack = &g_leftstack;
    for (int i = 0; i < stack->index; i++) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
    stack = &g_rightstack;
    for (int i = 0; i < stack->index; i++) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", g_left[i]);
    }
    printf("\n");
    for (int i = 0; i < len; i++) {
        printf("%d ", g_right[i]);
    }
    printf("\n");
}

void PreHandle(int ASize)
{
    memset(g_left, 0x0, sizeof(int) * ASize);
    memset(g_right, 0x0, sizeof(int) * ASize);
    memset(g_leftstack.arr, 0x0, sizeof(int) * ASize);
    g_leftstack.index = 0;
    memset(g_rightstack.arr, 0x0, sizeof(int) * ASize);
    g_rightstack.index = 0;
}

void FuncHandle(int* A, int ASize)
{
    Stack *stack = &g_leftstack;
    for (int i = 0; i < ASize; i++) {
        while(!StackIsEmpty(stack) && A[i] <= A[StackTop(stack)]) {
            StackPop(stack);
        }
        g_left[i] = StackIsEmpty(stack) ? -1 : StackTop(stack);
        StackPush(stack, i);
    }

    stack = &g_rightstack;
    for (int i = ASize - 1; i >= 0; i--) {
        while(!StackIsEmpty(stack) && A[i] < A[StackTop(stack)]) {
            StackPop(stack);
        }
        g_right[i] = StackIsEmpty(stack) ? ASize : StackTop(stack);
        StackPush(stack, i);
    }
    PrintInfo(ASize);
}

int Calcu(int* A, int ASize)
{
    long long sum = 0;
    long long p = 0;
    for (int i = 0; i < ASize; i++) {
        p = (i - g_left[i]) * (g_right[i] - i) * A[i] % MAX_MOD;
        sum = (sum + p) % MAX_MOD;
    }
    return (int)sum;
}

int sumSubarrayMins(int* A, int ASize)
{
    long long ret = 0;
    PreHandle(ASize);
    FuncHandle(A, ASize);
    ret = Calcu(A, ASize);
    return ret;
}

void main()
{
    int a[] = {3,1,2,4};
    int ret = sumSubarrayMins(a, sizeof(a) / sizeof(int));
    printf("ret = %d\n", ret);
}