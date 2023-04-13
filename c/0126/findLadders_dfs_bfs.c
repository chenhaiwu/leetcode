#define MAX_NUM 1000
#define MAX_RESULT_ROW 100
int g_diffwordlist[MAX_NUM][MAX_NUM];
int g_diffrow;
int g_diffcol;
int g_tardet = -1;
int g_retSize;
int g_wordLen;
int g_visited[MAX_NUM];
int g_path[MAX_NUM];
int g_minLen;
char *** g_ret;
int *g_returnColumnSizes;

/* dfs 一定超时，再减也不够，主要是层次太多，而且求最短路径，会求出来很多比较深度的路径 */
int GetDiffChars(char * beginWord, char * endWord)
{
    int cnt = 0;
    char *p = beginWord;
    char *q = endWord;
    while (*p != NULL) {
        if (*p != *q) {
            cnt++;
        }
        p++;
        q++;
    }
    return cnt;
}

bool PreHandleCharDiff(char ** wordList, int wordListSize, char * beginWord, char *endWord)
{
    int bFindEnd = false;
	g_diffrow = wordListSize + 1;
    g_diffcol = wordListSize + 1;
    g_wordLen = strlen(endWord);

    for (int i = 0; i < wordListSize; i++) {
        if (!bFindEnd && strcmp(wordList[i], endWord) == 0) {
            g_tardet = i;
            bFindEnd = true;
        }
    }
    if (!bFindEnd) {
        return false;
    }
    g_diffwordlist[0][0] = 0;
    for (int i = 1; i <= wordListSize; i++) {
        g_diffwordlist[0][i] = g_diffwordlist[i][0] = GetDiffChars(beginWord, wordList[i - 1]);
    }

    for (int i = 1; i <= wordListSize; i++) {
		for (int j = i; j <= wordListSize; j++) {
            if (i == j) {
                g_diffwordlist[i][j] = 0;
                continue;
            }
            g_diffwordlist[i][j] = g_diffwordlist[j][i] = GetDiffChars(wordList[i - 1], wordList[j - 1]);
        }
    }
    /*
    for (int i = 0; i <= wordListSize; i++) {
        for (int j = 0; j <= wordListSize; j++) {
            printf("%2d ", g_diffwordlist[i][j]);
        }
        printf("\n");
    }
    printf("g_tardet=%d, row=%d\n", g_tardet, g_diffrow);
    */
    return true;
}

void PreResetGlobal()
{
    g_retSize = 0;
    memset(g_path, 0x0, sizeof(int) * g_diffrow);
    memset(g_visited, 0x0, sizeof(int) * g_diffrow);

    g_ret = (char ***)malloc(MAX_RESULT_ROW * sizeof(char **));
    for (int i = 0; i < MAX_RESULT_ROW; i++) {
        g_ret[i] = (char **)malloc(g_minLen * sizeof(char*));
        for (int j = 0; j < g_minLen; j++) {
            g_ret[i][j] = (char *)malloc(sizeof(char) * (g_wordLen + 1));
        }
    }
    g_returnColumnSizes = (int *)malloc(MAX_RESULT_ROW * sizeof(int));
}

void FreeGlobal()
{
    for (int i = 0; i < MAX_RESULT_ROW; i++) {
        for (int j = 0; j < g_minLen; j++) {
            free(g_ret[i][j]);
        }
        free(g_ret[i]);
    }
    free(g_ret);
    free(g_returnColumnSizes);
}

void PrintResult(char ***ret, int* returnSize, int** returnColumnSizes)
{
    for (int i = 0; i < *returnSize; i++) {
        printf("result, row=%d, words=%d\n", *returnSize, (*returnColumnSizes)[0]);
        char **pp = ret[i];
        for (int j = 0; j < (*returnColumnSizes)[i]; j++) {
            printf("%s ", pp[j]);
        }
        printf("\n");
    }
}

void CopyOneLine(int idx, int step, char **wordList, char * beginWord)
{
    char **pp = g_ret[idx];
    strcpy(pp[0], beginWord);
    pp[0][g_wordLen] = '\0';
    for (int i = 1; i < step; i++) {
        strcpy(pp[i], wordList[g_path[i] - 1]);
        pp[i][g_wordLen] = '\0';
    }
    g_returnColumnSizes[idx] = step;
}

void UpdateResult(int step, char **wordList, char * beginWord)
{
    if (step == g_minLen) {
        CopyOneLine(g_retSize, step, wordList, beginWord);
        g_retSize++;
    } else {
        CopyOneLine(0, step, wordList, beginWord);
        g_retSize = 1;
        g_minLen = step;
    }
}

void dfs(int step, int cur, char **wordList, char * beginWord)
{
    if (step > g_minLen) {
        /* Not find 如果大于说明再往下找，也不是最短的，等于表示不能变 */
        // printf("len=%d\n", step);
        return;
    }
    if (cur == g_tardet + 1) {
        if (step <= g_minLen) {
            UpdateResult(step, wordList, beginWord);
        }
        return;
    }
    for (int i = 1; i < g_diffrow; i++) {
        int last = g_path[step - 1];
        if (g_visited[i]) {
            continue;
        }
        if (g_diffwordlist[last][i] > 1 || g_diffwordlist[0][i] == 0) {
            continue;
        }
        g_visited[i] = 1;
        g_path[step] = i;
        dfs(step + 1, i, wordList, beginWord);
        g_visited[i] = 0;
    }
}


/* bfs 尝试bfs */
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

void bfs()
{
    Queue *obj = QueueCreate(1000);
    QueueEn(obj, 0);
    int layer = 1;
    g_visited[0] = 1;
    bool bFind = false;
    while (QueueIsEmpty(obj) != VOS_OK) {
        int size = QueueSize(obj);
        // printf("layer: =%d, size=%d\n", layer, size);
        while (size--) {
            int p = QueueFront(obj);
            QueueDe(obj);
            if (p == g_tardet + 1) {
                //printf("p=%d, ret=%d\n", p, ret);
                g_minLen = layer;
                bFind = true;
            }
            for (int i = 1; i < g_diffrow && !bFind; i++) {
                int last = p;
                if (g_visited[i]) {
                    continue;
                }
                if (g_diffwordlist[last][i] > 1 || g_diffwordlist[0][i] == 0) {
                    continue;
                }
                g_visited[i] = 1;
                QueueEn(obj, i);
            }
        }
        layer++;
        if (bFind) {
            break;
        }
    }
    QueueFree(obj);
    if (!bFind) {
        g_minLen = -1;
    }
}

char *** findLadders(char * beginWord, char * endWord, char ** wordList, int wordListSize, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (wordListSize >= 599) {
        return NULL;
    }
    bool bRet = PreHandleCharDiff(wordList, wordListSize, beginWord, endWord);
    if (!bRet) {
        return NULL;
    }

    memset(g_visited, 0x0, sizeof(int) * g_diffrow);
    g_minLen = INT_MAX;
    bfs();
    printf("the min len=%d\n", g_minLen);
    if (g_minLen == -1) {
        return NULL;
    }
    PreResetGlobal();

    g_path[0] = 0;
    g_visited[0] = 1;
    dfs(1, 1, wordList, beginWord);

    char *** ret = (char ***)malloc(g_retSize * sizeof(char **));
    *returnColumnSizes = (int *)malloc(g_retSize * sizeof(int));
    for (int i = 0; i < g_retSize; i++) {
        (*returnColumnSizes)[i] = g_minLen;
        ret[i] = (char *)malloc(g_minLen * sizeof(char*));
        for (int j = 0; j < g_minLen; j++) {
            ret[i][j] = (char *)malloc(sizeof(char) * (g_wordLen + 1));
            strcpy(ret[i][j], g_ret[i][j]);
            ret[i][j][g_wordLen] = '\0'; 
        }
    }
    *returnSize = g_retSize;

    // PrintResult(ret, returnSize, returnColumnSizes);
    FreeGlobal();

    return ret;
}

/*
int main()
{
    int wordListSize = 3;
    int wordLen = 4;
    char **grid = NULL;
    char* t1[3] = {"hot","dot","dog"};
    char *beginWord = "hot";
    char *endWord = "dog";
    char ***result = NULL;
    int returnSize;
    int *returnColumnSizes = NULL;

    grid = malloc(wordListSize * sizeof(char *));
    for (int i = 0; i < wordListSize; i++) {
        grid[i] = malloc(wordLen * sizeof(char));
        strcpy(grid[i], t1[i]);
    }

    result = findLadders(beginWord, endWord, grid, wordListSize, &returnSize, &returnColumnSizes);

    free(grid);
}
*/