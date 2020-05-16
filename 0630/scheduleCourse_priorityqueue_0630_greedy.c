#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define DEGUG_CHW
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}

void PrintMatrix(int** grid, int gridSize, int* gridColSize)
{
#ifdef DEGUG_CHW
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridColSize[row]; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
#endif
}

/* 我们首先可以发现，如果两门课 (t1, d1) 和 (t2, d2) 满足 d1 <= d2，即后者的结束时间不晚于前者，那么我们先学习前者再学习后者总是最优的。因为如果先学习前者，即需要满足 x + t1 <= d1 且 x + t1 + t2 <= d2；如果先学习后者，则需要满足 x + t2 <= d2 且 x + t1 + t2 <= d1。如果后者中的 x + t1 + t2 <= d1 成立，那么显然有 x + t1 <= d1 且 x + t1 + t2 <= d1 <= d2，即前者一定成立；反之如果 x = 0, (t1, d1) = (2, 3), (t2, d2) = (5, 100)，那么前者成立且后者不成立。因此先学习前者再学习后者总是最优的。

基于上面的结论，我们可以将课程按照完成时间 d 递增排序。假设我们在前 i 门课中最多可以选取 k 门课，并且这 k 门课的总时长最短（称为最优方案），那么有下面的不等式：

t1 + t2 <= d2
t1 + t2 + t3 <= d3
...
t1 + t2 + ... + tk <= dk
此时我们需要判断第 i + 1 门课 (t0, d0) 是否可选。如果选取的 k 门课的总时长 t 与 t0 之和小于等于 d0，即

t1 + t2 + ... + tk + t0 <= d0
那么 (t0, d0) 一定可选，此时前 i + 1 门课的最优方案是选取 t1, t2, ..., tk, t0 这 k + 1 门课。可以使用反证法来证明，假设可以选取超过 k + 1 门课，或者选取 k + 1 门课且总时长小于 t1 + t2 + ... + tk + t0，那么我们去除 (t0, d0) 这门课，剩余的选取方案一定满足条件，且优于选取 t1, t2, ..., tk 的方案，与之间的假设 t1, t2, ..., tk 是最优方案相矛盾。

如果上述不等式不满足，那么我们找出 t1, t2, ..., tk 中时间最长的那一门课 tj，如果 tj > t0，那么我们可以将 tj 用 t0 代替，即 t1, t2, ..., tj-1, tj+1, ..., tk, t0 是一种最优方案。这里同样可以使用反证法来证明。如果 tj <= t0，那么最优方案仍然为 t1, t2, ..., tk。

因此我们依次遍历每一门课程，通过上面的方法，就可以得到最优方案。我们就可以通过优先队列在若干个数中选出最大值，在遍历每一门课程 (ti, di) 时，依次进行如下操作：

如果当前优先队列中所有课程的时间之和 t 与 ti 之和小于等于 di，那么就把 (ti, di) 加入优先队列中；

如果当前优先队列中所有课程的时间之和 t 与 ti 之和大于 di，那么找到当前优先队列中课程时间最大的课程 (tj, dj)（即为堆顶），如果 tj > ti，则将它移出优先队列，并把 (ti, di) 加入优先队列中
 */

int Cmp(const void *a, const void *b)
{
    int* ta = *(int **)a;
    int* tb = *(int **)b;
    if (ta[1] == tb[1]) {
        return ta[0] - tb[0];
    }
    return ta[1] - tb[1];
}

typedef struct _node {
    int t;
    struct _node *pNext;
} Node;

typedef struct _LinkHead {
    Node *head;
    int nodeNum;
    int totalDays;
} PriListHead;

PriListHead* CreatePriList()
{
    PriListHead *pList = (PriListHead *)malloc(sizeof(PriListHead));
    pList->head = NULL;
    pList->nodeNum = 0;
    pList->totalDays = 0;
    return pList;
}

void AddPrioList(PriListHead* pPrioList, int t, int d)
{
    Node * pNewNode = (Node *)malloc(sizeof(Node));
    pNewNode->t = t;
    Node *pNext = pPrioList->head;
    Node *pPrev = NULL;
    while (pNext && pNext->t > t) {
        pPrev = pNext;
        pNext = pNext->pNext;
    }
    if (!pPrev) {
        pNewNode->pNext = pPrioList->head;
        pPrioList->head = pNewNode;
    } else {
        pPrev->pNext = pNewNode;
        pNewNode->pNext = pNext;
    }
    pPrioList->nodeNum++;
    pPrioList->totalDays += t;
}

void DelPrioList(PriListHead* pPrioList)
{
    Node *pDel = pPrioList->head;
    if (pDel == NULL) {
        return;
    } 
    pPrioList->head = pDel->pNext;
    pPrioList->nodeNum--;
    pPrioList->totalDays -= pDel->t;
    free(pDel);
}

int scheduleCourse(int** courses, int coursesSize, int* coursesColSize)
{
    int t, d, tmpEndDay;
    //PrintMatrix(courses, coursesSize, coursesColSize);
    qsort(courses, coursesSize, sizeof(courses[0]), Cmp);
    // PrintMatrix(courses, coursesSize, coursesColSize);
    PriListHead *pPrioList = CreatePriList();
    for (int i = 0; i < coursesSize; i++) {
        t = courses[i][0];
        d = courses[i][1];
        tmpEndDay = pPrioList->totalDays + t;
        if (tmpEndDay <= d) {
            AddPrioList(pPrioList, t, d);
        } else if (pPrioList->head && pPrioList->head->t > t) {
            DelPrioList(pPrioList);
            AddPrioList(pPrioList, t, d);
        }
    }
    return pPrioList->nodeNum;
}

/*
#define MAP_ROW 4
#define MAP_COL 2
int g_map[MAP_ROW][MAP_COL] = {{100,200}, {200,1300}, {1000,1250}, {2000,3200}};

int main()
{
    int gridSize = MAP_ROW;
    int **grid = NULL;
    int *gridColSize = NULL;

    grid = malloc(gridSize * sizeof(int *));
    if (grid == NULL) {
        return -1;
    }
    gridColSize = malloc(gridSize * sizeof(int));
    if (gridColSize == NULL) {
        return -1;
    }
    for (int i = 0; i < gridSize; i++) {
        gridColSize[i] = MAP_COL;
        grid[i] = malloc(MAP_COL * sizeof(int));
        if (grid[i] == NULL) {
            return -1;
        }
    }
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            grid[i][j] = g_map[i][j];
        }
    }
    int retsize = scheduleCourse(grid, gridSize, gridColSize);
    return 0;
}
*/