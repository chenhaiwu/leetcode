#define STACK_MAX 10240
#define MAX_CHARS 26
typedef struct _stack {
    char arr[STACK_MAX];
    int index;
} Stack;

void StackPush(Stack *s, int a)
{
    s->arr[s->index] = a;
    s->index++;
}

char StackPop(Stack *s)
{
    s->index--;
    return s->arr[s->index];
}

int StackTop(Stack *s)
{
    int idx = s->index - 1;
    return s->arr[idx];
}

Stack g_stack;
char g_flags[MAX_CHARS];
char g_used[MAX_CHARS];

char *ValidCheck(char *words, int *del, int *flag)
{
    char *ret = NULL;
    int cnt = 0;
    if (words == NULL) {
        *flag = 1;
        return words;
    }
    int len = strlen(words);
    printf("len=%d\n", len);
    memset(g_flags, 0x0, sizeof(g_flags));
    for (int i = 0; i < len; i++) {
        g_flags[words[i] - 'a']++;
        if (g_flags[words[i] - 'a'] > 1) {
            cnt++;
        }
    }
    if (cnt == 0) {
        ret = (char *)malloc((len + 1) * sizeof(char));
        memset(ret, 0x0, (len + 1) * sizeof(char));
        memcpy(ret, words, len);
        *flag = 1;
        return ret;
    }
    *del = cnt;
    return NULL;
}

char *removeDuplicateLetters(char *words)
{
    char *ret = NULL;
    int retFlag = 0;
    int del = 0;
    ret = ValidCheck(words, &del, &retFlag);
    if (retFlag == 1) {
        return ret;
    }
    memset(&g_stack, 0x0, sizeof(Stack));
    memset(&g_used, 0x0, sizeof(g_used));
    Stack *stack = &g_stack;

    int len = strlen(words);
    for (int i = 0; i < len; i++) {
        char curChar = words[i];
        g_flags[curChar - 'a']--;
        if (g_used[curChar - 'a'] == 1) {
            continue;
        }
        // 单调递增，栈顶 >= 当前元
        while (stack->index > 0 && StackTop(stack) >= curChar &&
            g_flags[StackTop(stack) - 'a'] > 0) {
            char delChar = StackPop(stack);
            //printf("delChar=%c\n", delChar);
            g_used[delChar - 'a'] = 0;
        }
        StackPush(stack, curChar);
        g_used[curChar - 'a'] = 1;
    }

    int finalLen = stack->index;
    ret = (char *)malloc((finalLen + 1) * sizeof(char));
    memset(ret, 0x0, (finalLen + 1) * sizeof(char));
    for (int i = finalLen - 1; i >= 0; i--) {
        ret[i] = StackPop(&g_stack);
    }
    return ret;
}