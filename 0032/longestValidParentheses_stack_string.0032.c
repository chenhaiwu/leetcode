#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define STACK_MAX 20001
#define MAX_N 50001
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

Stack g_stack;
int g_flag[MAX_N];
int longestValidParentheses(char * s)
{
    Stack *g = &g_stack;
    int len = strlen(s);
    int ans = INT_MIN;
    if (len == 0) return 0;
    StackInit(g);
    memset(g_flag, 0x0, sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        char tmp = s[i];
        if (tmp == '(') {
            StackPush(g, i);
        } else {
            if (StackIsEmpty(g)) continue;
            else {
                int idx = StackPop(g);
                g_flag[idx] = 1;
                g_flag[i] = 1;
            }
        }
    }
    for (int i = 0; i < len; ) {
        int tmp = 0;
        while (g_flag[i++]) {
            tmp++;
        }
        ans = MAX(ans, tmp);
    }
    return ans;
}

int main()
{
    int ret = longestValidParentheses("(()");
    printf("ret=%d\n", ret);
    ret = longestValidParentheses(")()())");
    printf("ret=%d\n", ret);
    ret = longestValidParentheses("()(()");
    printf("ret=%d\n", ret);
    return 0;
}