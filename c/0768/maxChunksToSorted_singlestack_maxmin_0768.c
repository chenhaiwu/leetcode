#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_NUM 20002
int g_premax[MAX_NUM];
int g_sufixmin[MAX_NUM];

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

/* ά���������飬�����ң�����ǰiλ�õ����ֵ�����ҵ��󣬵���ǰiλ�õ���Сֵ����ǰ������ֵС�ں������Сֵ������Է���
 * һ��������Ҫ������1����Ϊ���һ�������Ե���һ��
 */
int maxChunksToSorted_1(int* arr, int arrSize)
{
    int ans = 0;
    int max = INT_MIN;
    g_premax[0] = arr[0];
    for (int i = 1; i < arrSize; i++) {
        g_premax[i] = MAX(g_premax[i - 1], arr[i]);
    }
    g_sufixmin[arrSize - 1] = arr[arrSize - 1];
    for (int i = arrSize - 2; i >= 0; i--) {
        g_sufixmin[i] = MIN(g_sufixmin[i + 1], arr[i]);
    }
    PrintArray(g_premax, arrSize);
    PrintArray(g_sufixmin, arrSize);
    for (int i = 0; i < arrSize - 1; i++) {
        if (g_premax[i] <= g_sufixmin[i + 1]) {
            ans++;
        }
    }
    return ans + 1;
}

/* �㷨ʹ�õ���ջ������Ϊ��������������ʼ���������С��topֵ����pop�����ѵ�ǰֵ��ջ�����Էֵ����������ջ��� */
#define STACK_MAX 20002
typedef int stacktype;
typedef struct _stack {
    stacktype arr[STACK_MAX];
    int index;
} Stack;

void StackPush(Stack *s, int a)
{
    s->arr[s->index] = a;
    s->index++;
}

stacktype StackPop(Stack *s)
{
    s->index--;
    return s->arr[s->index];
}

int StackTop(Stack *s)
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

int maxChunksToSorted(int* arr, int arrSize)
{
    int ans = 0;
    Stack g_stack = {0};
    for (int i = 0; i < arrSize; i++) {
        if (StackIsEmpty(&g_stack) || arr[i] >= StackTop(&g_stack)) {
            StackPush(&g_stack, arr[i]);
        } else {
            int head = StackPop(&g_stack);
            while (!StackIsEmpty(&g_stack) && arr[i] < StackTop(&g_stack)) {
                StackPop(&g_stack);
            }
            StackPush(&g_stack, head);
        }
    }
    ans = StackDepth(&g_stack);
    return ans;
}

int main()
{
    int nums[5] = {4,2,1,1};
    int retsize = maxChunksToSorted(nums, sizeof(nums) / sizeof(int));
    return 0;
}
