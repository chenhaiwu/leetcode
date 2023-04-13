/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct _node{
    char name[11];
    int time;
    int money;
    char city[11];
} Node;

void PrintMatrix(Node* grid, int gridSize)
{
    for (int row = 0; row < gridSize; row++) {
        printf("%s\n", grid[row].name);
        printf("%d\n", grid[row].time);
        printf("%d\n", grid[row].money);
        printf("%s\n", grid[row].city);
    }
}

Node* PreHandle(char** transactions, int transactionsSize)
{
    Node *pNode = (Node *)malloc(sizeof(Node) * transactionsSize);
    memset(pNode, 0x0, sizeof(Node) * transactionsSize);
    for (int i = 0; i < transactionsSize; i++) {
        //"alice,20,800,mtv"
        char *s = transactions[i];
        char *head = s;
        while (s != NULL && *s != ',') {
            s++;
        }
        strncpy(pNode[i].name, head, s - head);

        s++;
        head = s;
        while (s != NULL && *s != ',') {
            s++;
        }
        char time[10] = {0};
        strncpy(time, head, s - head);
        pNode[i].time = atoi(time);
        
        s++;
        head = s;
        while (s != NULL && *s != ',') {
            s++;
        }
        char money[10] = {0};
        strncpy(money, head, s - head);
        pNode[i].money = atoi(money);
        
        s++;
        head = s;
        strcpy(pNode[i].city, head);
    }
    //PrintMatrix(pNode, transactionsSize);
    return pNode;
}

char** invalidTransactions(char** transactions, int transactionsSize, int* returnSize)
{
    int retSize = 0;
    char **result = NULL;
    result = malloc(transactionsSize * sizeof(char *));
    int *mark = (int *)malloc(sizeof(int) * transactionsSize);
    memset(mark, 0x0, sizeof(int) * transactionsSize);

    Node *pNode = PreHandle(transactions, transactionsSize);

    for (int i = 0; i < transactionsSize; i++) {
        if (pNode[i].money > 1000) {
            mark[i] = 1;
        }
        for (int j = i + 1; j < transactionsSize; j++) {
            if (((pNode[i].time >= pNode[j].time && pNode[i].time - pNode[j].time <= 60)
                || (pNode[j].time >= pNode[i].time && pNode[j].time - pNode[i].time <= 60))
                && (strcmp(pNode[i].name, pNode[j].name) == 0) && (strcmp(pNode[i].city, pNode[j].city) != 0)) {
                mark[i] = 1;
                mark[j] = 1;
            }
        }
    }

    for (int i = 0; i < transactionsSize; i++) {
        if (mark[i] == 1) {
            int len = strlen(transactions[i]);
            result[retSize] = (char *)malloc(sizeof(char) * (len + 1));
            strcpy(result[retSize], transactions[i]);
            result[retSize][len] = '\0';
            retSize++;
        }
    }

    *returnSize = retSize;
    return result;
}