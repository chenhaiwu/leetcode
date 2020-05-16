#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

/* 
 *  
 */

#define MAX_NUM 26
typedef struct _mynode {
    char c;
    int cnt;
} MyNode;
MyNode g_flag[MAX_NUM];

int Cmp(const void *a, const void *b)
{
    MyNode *ta = (MyNode *)a;
    MyNode *tb = (MyNode *)b;
    if (ta->cnt == tb->cnt) {
        return ta->c - tb->c;
    }
    return tb->cnt - ta->cnt;
}

void PreHandle(char * s)
{
    memset(g_flag, 0x0, sizeof(g_flag));
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        g_flag[s[i] - 'a'].cnt++;
        g_flag[s[i] - 'a'].c = s[i];
    }
}

int FindBigNodeIdx(char lastChar)
{
    if (lastChar == '#') {
        return 0;
    }
    if (g_flag[0].c != lastChar) {
        return 0;
    } else {
        return g_flag[1].cnt == 0 ? -1 : 1;
    }
}

char * reorganizeString(char * s)
{
    int len = strlen(s);
    PreHandle(s);
    qsort(g_flag, MAX_NUM, sizeof(MyNode), Cmp);
    char *ret = (char *)malloc(len + 1);
    ret[len] = '\0';
    char lastChar = '#';
    for (int i = 0; i < len; i++) {
        int nodeIdx = FindBigNodeIdx(lastChar);
        if (nodeIdx == -1) {
            return "";
        }
        lastChar = g_flag[nodeIdx].c;
        ret[i] = lastChar;
        g_flag[nodeIdx].cnt--;
        qsort(g_flag, MAX_NUM, sizeof(MyNode), Cmp);
    }
    return ret;
}

int main()
{
    int *ret = reorganizeString("aaab");
    printf("ret=%s\n", ret);
    return 0;
}