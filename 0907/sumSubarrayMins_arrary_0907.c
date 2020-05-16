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
    结果：58/64 ，只能计算到1000就发现超时了，根本无力支撑30000个元素
    数学2：前驱数据，后续数组，想法

考虑所有满足 A[j] 为最右且最小的元素的子序列个数 #(j)，那么结果就是 sum #(j) * A[j]。（我们必须考虑最右这样才可以构造互不相交的子序列，否则会出现多次计算，因为一个数组的最小值可能不唯一。）

这就变成考虑最小的下标 i <= j 满足 A[i], A[i+1], ..., A[j] 都 >= A[j] 以及最大的下标 k >= j 满足 A[j+1], A[j+2], ..., A[k] 都 > A[j]。

算法

例如，A = [10, 3, 4, 5, _3_, 2, 3, 10] 我们需要计算 #(j = 4)，也就是第二个数字 3 ，被标记的那个，我们会发现 i = 1 和 k = 5。

由此，实际的总数为 #(j) = (j - i + 1) * (k - j + 1) 其中 j - i + 1 选择子序列的左端点 i, i+1, ..., j，而 k - j + 1 选择子序列的右端点 j, j+1, ..., k。

对于每个询问（也就是根据 j 计算出 (i, k)）是一个经典问题，可以用一个栈来解决。我们会重点解答如何找到 i，而找到 k 的做法与之类似。

构造前序数组

做法是维护一个栈，A 的单调下降子序列（事实上是维护一个 A 的下标索引）。对于下一个询问，候选界限为 i* - 1，其中 A[i*] 以递增顺序存储。

现在考虑升序下标 j ，我们可以按照 i* 递减顺序移走所有 A[i*] <= A[j]。

例如，假设 A = [10, 5, 3, 7, 0, 4, 5, 2, 1, _8_] 那么当考虑 j = 9 (A[j] = 8)，我们有一个存储边界的栈类似于 [-1, 0, 3, 6]（代表 A[i*] = -inf, 10, 7, 5）。我们从栈中弹出 6 和 3 因为 5 <= 8 且 7 <= 8，因此得到询问的边界为 i* - 1 = 0。

注意这个过程线性的，因为只进行了线性次的入栈和出栈。
 
    申请两个数组，用于存当前位置的left, right，左边比自己小的，右边比自己小的，然后就可求和。left数组使用单调增，第一个元素为-1，从左到右入栈，right数组使用单调增栈，从右往左入栈。
*/

/* 算法1
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

//算法2
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