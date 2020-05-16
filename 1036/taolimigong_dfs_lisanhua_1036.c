#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX_N 1000000
#define MAX_BLOCK_N 201

int g_memo[MAX_BLOCK_N][2];
int g_path[MAX_BLOCK_N][2];

int Step(struct TreeNode* root)
{
}

/* 把block所有的点连接起来，先排序，然后在8个方向上，连接起来，如果连接不起，则直接return fasle */
bool Dfs(int** blocked, int blockedSize, int* source, int* target)
{
    int lefts = Step(sel.left);
    int rights = Step(sel.right);
    int parents = n - lefts - rights - 1;
    int half = n / 2;
    if (lefts > half || rights > half || parents > half) {
        return true;
    } else {
        return false;
    }
}

int Cmp(void *a, void *b)
{
    int *a = *(int **)a;
    int *b = *(int **)b;
    if (a[0] == b[0]) {
        return a[1] - b[1];
    }
    return a[0] - b[0];
}

bool isEscapePossible(int** blocked, int blockedSize, int* blockedColSize, 
    int* source, int sourceSize, int* target, int targetSize)
{
    memset(g_memo, -1, sizeof(g_memo));
    memset(g_path, -1, sizeof(g_path));
    qsort(blocked, blockedSize, sizeof(*blocked), Cmp);
    bool ans = false;
    ans = Dfs(blocked, blockedSize, source, target);
    return ans;
}
typedef struct point_s {
    int x;
    int y;
    int xseq;
    int yseq;
} Point_t;

int compPoint(const void*a,const void*b)
{
    Point_t *p1 = (Point_t *)a;
    Point_t *p2 = (Point_t *)b;

    return (p1->x - p2->x);
}

void setSeqx(Point_t *pt, int size) {
    int x = pt->x;
    int i = 0;

    pt[0].xseq = (x != 0);
    for (i = 1; i < size; i++) {
        if (x == pt[i].x) {
            pt[i].xseq = pt[i-1].xseq;
        } else if ((x+1) == pt[i].x) {
            pt[i].xseq = pt[i-1].xseq + 1;
        } else {
            pt[i].xseq = pt[i-1].xseq + 2;
        }
        x = pt[i].x;
    }
        for (; i < 202; i++) {
        pt[i].xseq = 10000;
    }
}

int compPointY(const void*a,const void*b)
{
    Point_t *p1 = (Point_t *)a;
    Point_t *p2 = (Point_t *)b;

    return (p1->y - p2->y);
}

void setSeqY(Point_t *pt, int size) {
    int y = pt->y;
    int i = 0;

    pt[0].yseq = (y != 0);
    for (i = 1; i < size; i++) {
        if (y == pt[i].y) {
            pt[i].yseq = pt[i-1].yseq;
        } else if ((y+1) == pt[i].y) {
            pt[i].yseq = pt[i-1].yseq + 1;
        } else {
            pt[i].yseq = pt[i-1].yseq + 2;
        }
        y = pt[i].y;
    }
        for (; i < 202; i++) {
        pt[i].yseq = 10000;
    }
}

int Metrix[420][420] = {0};
int initMetrix(Point_t *pt, int size, int* source, int* target, Point_t *start, Point_t *end){
    int i = 0, ret = 0;
    for (; i < size; i++) {
        if (memcmp(source, pt+i, sizeof(int)*2) == 0) {
            start->xseq = pt[i].xseq;
            start->yseq = pt[i].yseq;
            Metrix[pt[i].xseq][pt[i].yseq] = 2;
            ret++;
        } else if (memcmp(target, pt+i, sizeof(int)*2) == 0) {
            end->xseq = pt[i].xseq;
            end->yseq = pt[i].yseq;
            Metrix[pt[i].xseq][pt[i].yseq] = 3;
            ret++;
        } else {
            Metrix[pt[i].xseq][pt[i].yseq] = 1;
        }
    }

    return (ret - 2);
}

int dirs[4][2] = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};
static bool isPossible(int xMax, int yMax, int x, int y, Point_t *end)
{
    int i = 0;
    int r, c;
    
    for (; i < 4; i++) {
        r = x + dirs[i][0];
        c = y + dirs[i][1];

        if ((r == end->xseq) && (c == end->yseq))
            return true;
        
        if ((r >= 0) && (r < xMax) && (c >= 0) && (c < yMax) && Metrix[r][c] != 1 && Metrix[r][c] != 4) {
            Metrix[r][c] = 4;
            if (isPossible(xMax, yMax, r, c, end))
                return true;
        }
    }
    
    return false;
}

bool isEscapePossible(int** blocked, int blockedSize, int* blockedColSize, int* source, int sourceSize, int* target, int targetSize){
if (blockedSize == 0)
        return true;
    int i;
    int num = 0;
    int xMax = 0, yMax = 0;
    Point_t ptData[202];
    Point_t st, end;

   memset(Metrix, 0, sizeof(Metrix));
   memset(ptData, 0x7F, 202 * sizeof(Point_t));
   if ((source[0] == target[0]) && (source[1] == target[1]))
        return true;
   if (source[0] > target[0]) {
        ptData[0].x = target[0];
        ptData[1].x = source[0];
        ptData[0].y = target[1];
        ptData[1].y = source[1];
   }else{
       ptData[0].x = source[0];
       ptData[1].x = target[0];
       ptData[0].y = source[1];
       ptData[1].y = target[1];
   }
   
   for (i = 0; i < blockedSize; i++) {
        ptData[i+2].x = blocked[i][0];
        ptData[i+2].y = blocked[i][1];
   }

   qsort(ptData, blockedSize + 2, sizeof(ptData[0]), compPoint);
   setSeqx(ptData, blockedSize + 2);
   if (ptData[blockedSize + 1].x == 1000000-1)
       xMax = ptData[blockedSize + 1].xseq+1;
   else
       xMax = ptData[blockedSize + 1].xseq+2;
   
   qsort(ptData, blockedSize + 2, sizeof(ptData[0]), compPointY);
   setSeqY(ptData, blockedSize + 2);
   if (ptData[blockedSize + 1].y == 1000000-1)
       yMax = ptData[blockedSize + 1].yseq+1;
   else 
       yMax = ptData[blockedSize + 1].yseq+2;
   if (initMetrix(ptData, blockedSize + 2, source, target, &st, &end) > 0)
      return false;
   
    return isPossible(xMax, yMax, st.xseq, st.yseq, &end);
}

void main()
{
    int ans;
    ans = findPaths(2, 2, 2, 0, 0);
    printf("ans=%d\n", ans);
    ans = findPaths(1, 3, 3, 0, 1);
    printf("ans=%d\n", ans);
    ans = findPaths(2, 2, 2, 0, 1);
    printf("ans=%d\n", ans);
    return;
}