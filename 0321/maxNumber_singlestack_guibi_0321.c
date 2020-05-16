#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

// #define DEGUG_CHW 
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}


/* �㷨ʹ�õ���ջ������Ϊ��������������ʼ���������С��topֵ����pop�����ѵ�ǰֵ��ջ�����Էֵ����������ջ��� */
#define STACK_MAX 20002
typedef int stacktype;
typedef struct _stack {
    stacktype arr[STACK_MAX];
    int index;
} Stack;

void StackInit(Stack *s)
{
    s->index = 0;
}

void StackPush(Stack *s, stacktype a)
{
    s->arr[s->index] = a;
    s->index++;
}

stacktype StackPop(Stack *s)
{
    s->index--;
    return s->arr[s->index];
}

stacktype StackTop(Stack *s)
{
    int idx = s->index - 1;
    return s->arr[idx];
}

int StackDepth(Stack *s)
{
    return s->index;
}

bool StackIsEmpty(Stack *s)
{
    return s->index == 0;
}

Stack g_stack1;
Stack g_stack2;
#define RET_MAX 20002
int g_array[RET_MAX];

void PreHandle(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    StackInit(&g_stack1);
    StackInit(&g_stack2);
}

void GetMaxSubArray(int* nums, int numsSize, int k, Stack *pStack)
{
    if (k == 0) {
        pStack->index = 0;
        return;
    }
    int pop = numsSize - k;
    for (int i = 0; i < numsSize; i++) {
        while (pop > 0 && !StackIsEmpty(pStack) && StackTop(pStack) < nums[i]) {
            pop--;
            StackPop(pStack);
        }
        StackPush(pStack, nums[i]);
    }
    /* ���ջ���棬һ��>= ����Ҫ��k��Ԫ��, ����ֻ����k��Ԫ�� */
    pStack->index = k;
}

int Cmp2Arrary(int *a, int start1, int len1, int *b, int start2, int len2)
{
    int m = start1;
    int n = start2;
    while (m < len1 && n < len2 && a[m] == b[n]) {
        m++;
        n++;
    }
    if (m == len1 && n == len2) {
        return 0;
    }
    if (m == len1 && n != len2) {
        return -1;
    }
    if (m != len1 && n == len2) {
        return 1;
    }
    if (a[m] < b[n]) {
        return -1;
    } else {
        return 1;
    }
}

void MergeArray()
{
    int len1 = StackDepth(&g_stack1);
    int len2 = StackDepth(&g_stack2);
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < len1 && j < len2) {
        if (g_stack1.arr[i] < g_stack2.arr[j]) {
            g_array[k] = g_stack2.arr[j];
            k++;
            j++;
        } else if (g_stack1.arr[i] > g_stack2.arr[j]) {
            g_array[k] = g_stack1.arr[i];
            k++;
            i++;
        } else {
            /* ��ȵ��������Ҫ�ȽϺ���˭�� */
            int m = i;
            int n = j;
            if (Cmp2Arrary(g_stack1.arr, m, g_stack1.index, g_stack2.arr, n, g_stack2.index) == 1) {
                g_array[k] = g_stack1.arr[i];
                k++;
                i++;
            } else {
                g_array[k] = g_stack2.arr[j];
                k++;
                j++;
            }
        }
    }
    if (i == len1) {
        for (; j < len2; j++) {
            g_array[k++] = g_stack2.arr[j];
        }
    }
    if (j == len2) {
        for (; i < len1; i++) {
            g_array[k++] = g_stack1.arr[i];
        }
    }
    // printf("final i=%d, j=%d, k=%d\n", i, j, k);
}

int CmpArray(int *ret, int k)
{
    for (int i = 0; i < k; i++) {
        if (g_array[i] == ret[i]) {
            continue;
        } else if (g_array[i] < ret[i]) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

void CopyArray(int *ret, int k)
{
    for (int i = 0; i < k; i++) {
        ret[i] = g_array[i];
    }
}

/* 1: ��num1��ѡ��i����[0 - min[n1, k])��0��ʾһ����ѡ��ʣ�µĴ�num2��ѡ�� 
 * 2: ѡ���������������������У�������ʹ�õ�����ջ��ɣ���Ȼ���������鰴˳��ϲ����ɣ��ٱȽ���������
*/
int* maxNumber(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize)
{
    int *ret = (int *)malloc(sizeof(int) * k);
    memset(ret, -1, sizeof(int) * k);
    int mx1 = MIN(nums1Size, k);
    for (int i = 0; i <= mx1; i++) {
        if (k - i > nums2Size) {
            continue;
        }
        /* �������г�ʼ��һ�� */
        PreHandle(nums1, nums1Size, nums2, nums2Size);
        /* ���������������ջ��ȫ�ֱ����� */
        GetMaxSubArray(nums1, nums1Size, i, &g_stack1);
        GetMaxSubArray(nums2, nums2Size, k - i, &g_stack2);
        MergeArray();
        // printf("merger:\n");
        PrintArray(g_array, k);
        if (CmpArray(ret, k)) {
            CopyArray(ret, k);
            // printf("ret max:\n");
            PrintArray(ret, k);
        }
    }
    *returnSize = k;
    return ret;
}

int main()
{
    int nums1[] = {3, 4, 6, 5};
    int nums2[] = {9, 1, 2, 5, 8, 3};
    int returnSize;
    int k = 5;
    int *ret = maxNumber(nums1, sizeof(nums1) / sizeof(int), nums2, sizeof(nums2) / sizeof(int), k, &returnSize);
    PrintArray(ret, k);
    return 0;
}