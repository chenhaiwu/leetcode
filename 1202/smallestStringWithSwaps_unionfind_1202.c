#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define NODE_MAX 200001
int g_pre[NODE_MAX];

int Find(int i)
{
    if (i != g_pre[i]) {
        g_pre[i] = Find(g_pre[i]);
    }
    return g_pre[i];
}

void Join(int i, int j)
{
    int pi = Find(i);
    int pj = Find(j);
    if (pi == pj) {
        return;
    } else if (pi < pj) {
        g_pre[pj] = pi;
    } else {
        g_pre[pi] = pj;
    }
    // for (int i = 0; i <= 24; i++) printf("%d ", g_pre[i]);
    // printf("\n");
}

void HanldeAllParnet(int len)
{
    for (int i = 0; i < len; i++) {
        Find(i);
    }
    // for (int i = 0; i <= 24; i++) printf("%d ", g_pre[i]);
    // printf("\n");
}

int g_hashtype[NODE_MAX];
typedef struct node {
    int idx;
    int num;
    int *list;
} Node;

void UnionOps(char *s, int **pairs, int pairsSize, int *pairsColSize)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        g_pre[i] = i;
        g_hashtype[i] = 0;
    }
    for (int i = 0; i < pairsSize; i++) {
        // printf("join %d %d\n", pairs[i][0], pairs[i][1]);
        Join(pairs[i][0], pairs[i][1]);
    }
    HanldeAllParnet(len);
    for (int i = 0; i < len; i++) {
        g_hashtype[g_pre[i]]++;
    }
}

int FindExitGroupIdx(Node *groupList, int groupSize, int i)
{
    int j = 0;
    for (j = 0; j < groupSize; j++) {
        if (groupList[j].idx == i) {
            break;
        }
    }
    return j;
}

void HandlerGroup(Node *groupList, int *pGroupSize, int len)
{
    int groupSize = 0;
    for (int i = 0; i < len; i++) {
        if (g_pre[i] == i) {
            groupList[groupSize].idx = g_pre[i];
            groupList[groupSize].num = 1;
            groupList[groupSize].list = (int *)malloc(sizeof(int) * g_hashtype[i]);
            groupList[groupSize].list[0] = i;
            // printf("Group id = %d, num=%d, i=%d\n", groupSize, g_hashtype[i], i);
            groupSize++;
        } else {
            int j = FindExitGroupIdx(groupList, groupSize, g_pre[i]);
            groupList[j].list[groupList[j].num] = i;
            groupList[j].num += 1;
            // printf("id=%d\n", i);
        }
    }
    *pGroupSize = groupSize;
}

int Cmp(void *a, void *b)
{
    return *(char *)a - *(char *)b;
}

void OrderGroup(char *s, char *ret, Node *groupList, int groupSize)
{
    for (int i = 0; i < groupSize; i++) {
        char *order = (char *)malloc(groupList[i].num);
        for (int j = 0; j < groupList[i].num; j++) {
            order[j] = s[groupList[i].list[j]];
            // printf("group id=%d, idx=%d, c=%c\n", i, groupList[i].list[j], order[j]);
        }
        qsort(order, groupList[i].num, sizeof(char), Cmp);
        for (int j = 0; j < groupList[i].num; j++) {
            ret[groupList[i].list[j]] = order[j];
            // printf("after group id=%d, idx=%d, c=%c\n", i, groupList[i].list[j], ret[groupList[i].list[j]]);
        }
    }
}

void FreeGroupList(Node **pGroupList, int groupSize)
{
    Node *groupList = *pGroupList;
    for (int i = 0; i < groupSize; i++) {
        if (groupList->list != NULL) {
            free(groupList->list);
            groupList->list = NULL;
        }
    }
    free(groupList);
    *pGroupList = NULL;
}

char *smallestStringWithSwaps(char *s, int **pairs, int pairsSize, int *pairsColSize)
{
    int len = strlen(s);
    char *ret = (char *)malloc(len + 1);
    memset(ret, 0x0, len + 1);
    UnionOps(s, pairs, pairsSize, pairsColSize);
    Node *groupList = (Node *)malloc(sizeof(Node) * len);
    memset(groupList, 0x0, sizeof(Node) * len);
    int groupSize = 0;
    HandlerGroup(groupList, &groupSize, len);
    OrderGroup(s, ret, groupList, groupSize);
    printf("groupsize=%d\n", groupSize);
    FreeGroupList(&groupList, groupSize);
    // printf("ret:%s\n", ret);
    return ret;
}

void main()
{
    int nums[] = {4, 3, 2, 3, 5, 2, 1};
    int k = 4;
    bool ret = canPartitionKSubsets(nums, sizeof(nums) / sizeof(int), k);
    printf("ret = %d\n", ret);
}