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

/* 维持两个数组，从左到右，到当前i位置的最大值；从右到左，到当前i位置的最小值，当前面的最大值小于后面的最小值，则可以分在
 * 一个块里。最后还要再增加1，因为最后一个数可以单独一个
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

/* 算法使用单调栈，而且为单调递增，从左开始遍历，如果小于top值，则pop，并把当前值入栈，可以分的组块就是最后栈深度 */
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
