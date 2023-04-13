#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>


/* bfs ??bfs */
typedef struct _queue{
    int head;
    int tail;
    int size;
    int *queue
} Queue;

#define INIT    (-1)
#define VOS_OK  0
#define VOS_NOK (-1)
Queue *QueueCreate(int k)
{
    Queue *p = (Queue *)malloc(sizeof(Queue));
    p->size = k;
    p->head = INIT;
    p->tail = INIT;
    p->queue = (int *)malloc(sizeof(int) * (k + 1));
    return p;
}

int QueueIsEmpty(Queue *obj)
{
    if (obj->head == INIT) {
        return VOS_OK;
    }
    return VOS_NOK;
}

int QueueIsFull(Queue *obj)
{
    if ((obj->tail + 1) % obj->size == obj->head) {
        return VOS_OK;
    }
    return VOS_NOK;
}

int QueueSize(Queue *obj)
{
    if (VOS_OK == QueueIsEmpty(obj)) {
        return 0;
    }
    if (VOS_OK == QueueIsFull(obj)) {
        return obj->size;
    }
    if (obj->head > obj->tail) {
        return obj->head - obj->tail - 1;
    } else {
        return obj->tail - obj->head + 1;
    }
}

int QueueEn(Queue *obj, int value)
{
    if (VOS_OK == QueueIsFull(obj)) {
        return VOS_NOK;
    }
    if (VOS_OK == QueueIsEmpty(obj)) {
        obj->head = 0;
    }
    obj->tail = (obj->tail + 1) % obj->size;
    obj->queue[obj->tail] = value;
    return VOS_OK;
}

int QueueDe(Queue *obj)
{
    if (VOS_OK == QueueIsEmpty(obj)) {
        return VOS_NOK;
    }
    if (obj->head == obj->tail) {
        obj->head = INIT;
        obj->tail = INIT;
        return VOS_OK;
    }
    obj->head = (obj->head + 1) % obj->size;
    return VOS_OK;
}

int QueueFront(Queue *obj)
{
    if (VOS_OK == QueueIsEmpty(obj)) {
        return -1;
    }
    return obj->queue[obj->head];
}

void QueueFree(Queue *obj)
{
    if (obj == NULL) {
        return;
    }
    if (obj->queue != NULL) {
        free(obj->queue);
        obj->queue = NULL;
    }
    free(obj);
    obj = NULL;
}

#define MAX_QUENU_N 10000000
#define MAX_MOD 1000000007

bool IsExitMatrix(int m, int n, int i, int j)
{
    bool ans = false;
    if (i == -1 || i == m || j == -1 || j == n) {
        ans = true;
    }
    return ans;
}

int Bfs(int m, int n, int N, int i, int j)
{
    int queueLen = MAX_QUENU_N;
    Queue *q = QueueCreate(queueLen);
    int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    QueueEn(q, i);
    QueueEn(q, j);
    int steps = N;
    int ans = 0;
    while (QueueIsEmpty(q) != VOS_OK && steps >= 0) {
        int size = QueueSize(q);
        size /= 2;
        while (size--) {
            int curi = QueueFront(q);
            QueueDe(q);
            int curj = QueueFront(q);
            QueueDe(q);
            if (IsExitMatrix(m, n, curi, curj)) {
                ans = (ans + 1) % MAX_MOD;
            } else {
                for (int i = 0; i < 4; i++) {
                    int newi = curi + dir[i][0];
                    int newj = curj + dir[i][1];
                    QueueEn(q, newi);
                    QueueEn(q, newj);
                }
            }
        }
        steps--;
    }
    return ans;
}

/* dfs */
#define MAX_N 51
/* 剩余N步时，在i, j位置上，可以出界的次数 */
int g_memo[MAX_N][MAX_N][MAX_N];
int g_dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int Step(int m, int n, int N, int i, int j)
{
    if (N < 0) return 0;
    if (IsExitMatrix(m, n, i, j)) return 1;
    if (g_memo[N][i][j] != -1) return g_memo[N][i][j];

    if (g_memo[N][i][j] == -1) {
        g_memo[N][i][j] = 0;
        for (int k = 0; k < 4; k++) {
            g_memo[N][i][j] += Step(m, n, N - 1, i + g_dir[k][0], j + g_dir[k][1]);
            g_memo[N][i][j] %= MAX_MOD;
        }
    }
    return g_memo[N][i][j];
}

int Step2(int steps, int m, int n, int N, int i, int j)
{
    if (steps == N + 1) return 0;
    if (IsExitMatrix(m, n, i, j)) return 1;
    int leftsteps = N - steps;
    if (g_memo[leftsteps][i][j] != -1) return g_memo[leftsteps][i][j];

    if (g_memo[leftsteps][i][j] == -1) {
        g_memo[leftsteps][i][j] = 0;
        for (int k = 0; k < 4; k++) {
            g_memo[leftsteps][i][j] += Step(m, n, N - 1, i + g_dir[k][0], j + g_dir[k][1]);
            g_memo[leftsteps][i][j] %= MAX_MOD;
        }
    }
    return g_memo[leftsteps][i][j];
}

int Dfs(int m, int n, int N, int i, int j)
{
    memset(g_memo, -1, sizeof(g_memo));

    int ans = Step(m, n, N, i, j);
    // int ans = Step2(0, m, n, N, i, j);
    return ans;
}


/* 状态转移方程，dp[steps][i][j] 在棋盘上ij位置走steps出界的次数 = 在它的四面走steps-1步出界的次数和
 * 总次数，就是把所有1-N步都出界的相加
 * 初始状态：四周出界都为1，但是注意四个角为2
 */
int g_dp[MAX_N][MAX_N][MAX_N];
int Dp(int m, int n, int N, int i, int j)
{
    int curi = i;
    int curj = j;
    memset(g_dp, 0, sizeof(g_dp));
    int ans = 0;

    /* 初始化，4个角会+=1两次 */
    for (int i = 0; i < m; i++) {
        g_dp[1][i][0] += 1;
        g_dp[1][i][n - 1] += 1;
    }
    for (int i = 0; i < n; i++) {
        g_dp[1][0][i] += 1;
        g_dp[1][m - 1][i] += 1;
    }

    /* 根据递推公式求算 */
    for (int s = 2; s <= N; s++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 4; k++) {
                    int newi = i + g_dir[k][0];
                    int newj = j + g_dir[k][1];
                    if (IsExitMatrix(m, n, newi, newj)) continue;                    
                    g_dp[s][i][j] += g_dp[s - 1][newi][newj];
                    g_dp[s][i][j] %= MAX_MOD;
                }
            }
        }
    }

    /* 统计所有的可能数组合 */
    for (int i = 1; i <= N; i++) {
        ans += g_dp[i][curi][curj];
        ans %= MAX_MOD;
    }
    return ans;
}

int findPaths(int m, int n, int N, int i, int j)
{
    int ans;
    if (IsExitMatrix(m, n, i, j)) {
        return -1;
    }
    // ans = Bfs(m, n, N, i, j);

    // ans = Dfs(m, n, N, i, j);

    ans = Dp(m, n, N, i, j);
    return ans;
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