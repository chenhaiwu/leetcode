/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: ¦Ò¥Í‰b?¥N?
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
// #include "securec.h"

#define MAX_RET_N 100
#define MAX_NODE_N 1000
typedef struct _node {
    int idx;
    int len;
} MyNode;
MyNode g_node[MAX_NODE_N];
int g_path[MAX_NODE_N];
int g_dictsize;
int g_pathlen;
char **g_dict;
char **g_ret;
int g_retcnt;
int g_fail_memo[MAX_NODE_N];

void Dfs(char * s, int pos)
{
    int slen = strlen(s);
    if (pos == slen) {
        char *ss = (char *)malloc(slen + 10 + g_pathlen);
        memset(ss, 0x0, sizeof(ss));
        for (int i = 0; i < g_pathlen; i++) {
            strcat(ss, g_dict[g_path[i]]);
            strcat(ss, " ");
        }
        int tlen = strlen(ss);
        ss[tlen - 1] = '\0';
        // printf("ret:%s\n", ss);
        g_ret[g_retcnt] = ss;
        g_retcnt++;
        return;
    }
    if (g_fail_memo[pos] != 0) return;

    int failcnt = 0;
    for (int i = 0; i < g_dictsize; i++) {
        int idx = g_node[i].idx;
        int len = g_node[i].len;
        /* ???‰Y?¡A³Ì¥D­nªº¬O?¤@˜ç¡Aª¾¹D°h¥X´N¥i¥H¤F¡C */
        if (g_fail_memo[pos + len] != 0) {
            failcnt++;
            continue;
        }
        if (slen - pos >= len && memcmp(g_dict[idx], s + pos, len) == 0) {
            g_path[g_pathlen] = idx;
            g_pathlen++;
            Dfs(s, pos + len);
            g_pathlen--;
        } else {
            failcnt++;
        }
    }
    if (failcnt == g_dictsize) {
        g_fail_memo[pos] = 1;
    }
}

int Cmp(void *a, void *b)
{
    MyNode *pa = (MyNode *)a;
    MyNode *pb = (MyNode *)b;
    #if 1
    return pa->len - pb->len;
    #else
    char s1[100];
    char s2[100];
    memset(s1, 0x0, sizeof(s1));
    memset(s2, 0x0, sizeof(s2));
    if (pa->len == pb->len) {
        strcat(s1, g_dict[pa->idx]);
        strcat(s1, g_dict[pb->idx]);
        strcat(s2, g_dict[pb->idx]);
        strcat(s2, g_dict[pa->idx]);
        return strcmp(s1, s2);
    } else {
        return pa->len - pb->len;
    }
    #endif
}

void PreHandle(char ** wordDict, int wordDictSize)
{
    for (int i = 0; i < wordDictSize; i++) {
        g_node[i].idx = i;
        g_node[i].len = strlen(wordDict[i]);
    }
    g_dict = wordDict;
    qsort(g_node, wordDictSize, sizeof(MyNode), Cmp);
    // for (int i = 0; i < wordDictSize; i++) {
    //     printf("[%d %d] ", g_node[i].len, g_node[i].idx);
    // }
    g_dictsize = wordDictSize;
}

char ** wordBreak(char * s, char ** wordDict, int wordDictSize, int* returnSize)
{
    PreHandle(wordDict, wordDictSize);

    g_retcnt = 0;
    g_ret = (char **)malloc(sizeof(char *) * MAX_RET_N);
    memset(g_ret, 0x0, sizeof(char *) * MAX_RET_N);

    memset(g_path, 0xFFFFFFFF, sizeof(g_path));
    memset(g_fail_memo, 0, sizeof(g_fail_memo));
    g_pathlen = 0;
    Dfs(s, 0);

    // return value
    // if (g_retcnt == 0) {
    //     g_ret[0] = "";
    //     g_retcnt = 1;
    // }
    *returnSize = g_retcnt;
    return g_ret;
}


// #define MAP_ROW 5
// char *g_map[] = {"cat", "cats", "and", "sand", "dog"};

// int main()
// {
//     int gridSize = MAP_ROW;
//     char **grid = NULL;
//     char **result = NULL;
//     int returnSize;
//     char *s = "catsanddog";

//     /* ¥Ó???¥Î¨Ò™]¤J‰ë?¤¤»Ý­nªº?¦s¦}®ÚÕu¥Î¨Ò™]¤Jªì©l¤Æ */
//     grid = (char **)malloc(gridSize * sizeof(char *));
//     for (int i = 0; i < gridSize; i++) {
//         int len = strlen(g_map[i]);
//         grid[i] = (char *)malloc(len + 1);
//         memset(grid[i], 0x0, len + 1);
//     }
//     for (int i = 0; i < gridSize; i++) {
//         strcpy(grid[i], g_map[i]);
//         printf("%s\n", grid[i]);
//     }

//     /* `¦æ??¥Î¨Ò?¥Xªº±µ¤f¨ç? */
//     result = wordBreak(s, grid, gridSize, &returnSize);

//     /* ?©ñ??¨ç?¤¤¥Ó?ªº?¦s */
//     for (int row = 0; row < returnSize; row++) {
//         printf("%s\n", result[row]);
//         free(result[row]);
//     }
//     free(result);

//     for (int i = 0; i < gridSize; i++) {
//         free(grid[i]);
//     }
//     free(grid);
// }