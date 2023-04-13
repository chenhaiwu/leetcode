#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define STACK_MAX 5001
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

/**
 * Definition for singly-linked list.
*/
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
    int len = n - m + 1;
    if (len == 1) {
        return head;
    }
    struct ListNode *p = head;
    int inc = 0;
    while (m > 1) {
        m--;
        p = p->next;
    }
    struct ListNode *pm = p;
    for (int i = 0; i < len; i++) {
        StackPush(&g_stack, p->val);
        p = p->next;
    }
    
    for (int i = 0; i < len; i++) {
        int a = StackPop(&g_stack);
        p->val = a;
        p = p->next;
    }
    return head;
}

void main()
{

}