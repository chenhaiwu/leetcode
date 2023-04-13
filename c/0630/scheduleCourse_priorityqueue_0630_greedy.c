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

/* �������ȿ��Է��֣�������ſ� (t1, d1) �� (t2, d2) ���� d1 <= d2�������ߵĽ���ʱ�䲻����ǰ�ߣ���ô������ѧϰǰ����ѧϰ�����������ŵġ���Ϊ�����ѧϰǰ�ߣ�����Ҫ���� x + t1 <= d1 �� x + t1 + t2 <= d2�������ѧϰ���ߣ�����Ҫ���� x + t2 <= d2 �� x + t1 + t2 <= d1����������е� x + t1 + t2 <= d1 ��������ô��Ȼ�� x + t1 <= d1 �� x + t1 + t2 <= d1 <= d2����ǰ��һ����������֮��� x = 0, (t1, d1) = (2, 3), (t2, d2) = (5, 100)����ôǰ�߳����Һ��߲������������ѧϰǰ����ѧϰ�����������ŵġ�

��������Ľ��ۣ����ǿ��Խ��γ̰������ʱ�� d �������򡣼���������ǰ i �ſ���������ѡȡ k �ſΣ������� k �ſε���ʱ����̣���Ϊ���ŷ���������ô������Ĳ���ʽ��

t1 + t2 <= d2
t1 + t2 + t3 <= d3
...
t1 + t2 + ... + tk <= dk
��ʱ������Ҫ�жϵ� i + 1 �ſ� (t0, d0) �Ƿ��ѡ�����ѡȡ�� k �ſε���ʱ�� t �� t0 ֮��С�ڵ��� d0����

t1 + t2 + ... + tk + t0 <= d0
��ô (t0, d0) һ����ѡ����ʱǰ i + 1 �ſε����ŷ�����ѡȡ t1, t2, ..., tk, t0 �� k + 1 �ſΡ�����ʹ�÷�֤����֤�����������ѡȡ���� k + 1 �ſΣ�����ѡȡ k + 1 �ſ�����ʱ��С�� t1 + t2 + ... + tk + t0����ô����ȥ�� (t0, d0) ���ſΣ�ʣ���ѡȡ����һ������������������ѡȡ t1, t2, ..., tk �ķ�������֮��ļ��� t1, t2, ..., tk �����ŷ�����ì�ܡ�

�����������ʽ�����㣬��ô�����ҳ� t1, t2, ..., tk ��ʱ�������һ�ſ� tj����� tj > t0����ô���ǿ��Խ� tj �� t0 ���棬�� t1, t2, ..., tj-1, tj+1, ..., tk, t0 ��һ�����ŷ���������ͬ������ʹ�÷�֤����֤������� tj <= t0����ô���ŷ�����ȻΪ t1, t2, ..., tk��

����������α���ÿһ�ſγ̣�ͨ������ķ������Ϳ��Եõ����ŷ��������ǾͿ���ͨ�����ȶ��������ɸ�����ѡ�����ֵ���ڱ���ÿһ�ſγ� (ti, di) ʱ�����ν������²�����

�����ǰ���ȶ��������пγ̵�ʱ��֮�� t �� ti ֮��С�ڵ��� di����ô�Ͱ� (ti, di) �������ȶ����У�

�����ǰ���ȶ��������пγ̵�ʱ��֮�� t �� ti ֮�ʹ��� di����ô�ҵ���ǰ���ȶ����пγ�ʱ�����Ŀγ� (tj, dj)����Ϊ�Ѷ�������� tj > ti�������Ƴ����ȶ��У����� (ti, di) �������ȶ�����
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