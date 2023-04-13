#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

typedef struct _node {
    int v;
    int n;
} Node;

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

int Cmp2(const void *a, const void *b)
{
    Node *ta = (Node *)a;
    Node *tb = (Node *)b;
    return ta->v > tb->v;
}

#define NODE_MAX 1000
Node g_node[NODE_MAX];
int g_nodeNum;
#define RET_NUM_MAX 100
#define MAX_FOUR 4
int g_retSize;
int g_result[RET_NUM_MAX][MAX_FOUR];
int g_path[MAX_FOUR];

void PrintNode()
{
    for (int i = 0; i < g_nodeNum; i++) {
        printf("v=%d, n=%d\n", g_node[i].v, g_node[i].n);
    }
}

void PreHandle(int* nums, int numsSize, int target)
{
    qsort(nums, numsSize, sizeof(int), Cmp);
    g_node[0].v = nums[0];
    g_node[0].n = 1;
    g_nodeNum = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == g_node[g_nodeNum - 1].v) {
            g_node[g_nodeNum - 1].n += 1;
        } else {
            g_node[g_nodeNum].v = nums[i];
            g_node[g_nodeNum].n = 1;
            g_nodeNum++;
        }
    }
    // PrintNode();
    qsort(g_node, g_nodeNum, sizeof(Node), Cmp2);
    PrintNode();
}

void FindResult()
{
    for (int i = 0; i < MAX_FOUR; i++) {
        g_result[g_retSize][i] = g_path[i];
    }
    g_retSize++;
}

void dfs(int start, int left, int target)
{
    if (left == 0 && target == 0) {
        FindResult();
        return;
    }
    if (start >= g_nodeNum) {
        return;
    }
    if (target > 0 && g_node[start].v > target) {
        return;
    }

    /* i表示针对当前这个位置，选择的次数 */
    for (int i = 0; i <= left && i <= g_node[start].n; i++) {
        if (i > 0) {
            g_path[MAX_FOUR - left + i - 1] = g_node[start].v;
        }
        int curSelVal = i * g_node[start].v;
        if (curSelVal > 0 && curSelVal > target) {
            continue;
        }
        dfs(start + 1, left - i, target - i * g_node[start].v);
    }
}
/* 使用dfs，再减枝也只能过221 / 282 个case，做成超过size反回，可以变成241个 */
int** fourSum_dfs(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes)
{
    if (numsSize < MAX_FOUR) {
        *returnSize = 0;
        return NULL;
    }
    PreHandle(nums, numsSize, target);

    g_retSize = 0;
    dfs(0, 4, target);

    int **result = NULL;
    result = (int **)malloc(g_retSize * sizeof(int *));
    *returnColumnSizes = (int *)malloc(g_retSize * sizeof(int));
    *returnSize = g_retSize;

    for (int i = 0; i < g_retSize; i++) {
        (*returnColumnSizes)[i] = MAX_FOUR;
        result[i] = (int *)malloc(MAX_FOUR * sizeof(int));
        for (int num = 0; num < MAX_FOUR; num++) {
            result[i][num] = g_result[i][num];
        }
    }
    return result;
}

/* 考虑双指针做法了 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (numsSize < MAX_FOUR) {
        *returnSize = 0;
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), Cmp);

    int **ret = (int **)malloc(sizeof(int *) * numsSize * 6);
    *returnColumnSizes = malloc(sizeof(int) * numsSize * 6);
    int retSize = 0;

    int first = 0;
    int right = numsSize - 1;

    while (first + 2 < right) {
        int second = first + 1;
        int t3 = target - nums[first];
        while (second + 1 < right) {
            int i = second + 1;
            int j = right;
            int t2 = t3 - nums[second];
            while (i < j) {
                if (nums[i] + nums[j] < t2) {
                    i++;
                } else if (nums[i] + nums[j] > t2) {
                    j--;
                } else {
                    ret[retSize] = malloc(sizeof(int) * MAX_FOUR);
                    ret[retSize][0] = nums[first];
                    ret[retSize][1] = nums[second];
                    ret[retSize][2] = nums[i];
                    ret[retSize][3] = nums[j];
                    (*returnColumnSizes)[retSize] = MAX_FOUR;
                    retSize++;

                    while(nums[i] == nums[++i] && i < j) {}
                    while(nums[j] == nums[--j] && i < j) {}
                }
            }
            while(nums[second] == nums[++second] && second + 1 < right) {}
        }
        while(nums[first] == nums[++first] && first + 2 < right) {}
    }

    *returnSize = retSize;
    return ret;
}


/*
int main()
{
    int **result = NULL;
    int returnSize;
    int *returnColumnSizes = NULL;
    int nums[] = {1,-2,-5,-4,-3,3,3,5};
    int target = -11;

    result = fourSum(nums, sizeof(nums) / sizeof(int), target, &returnSize, &returnColumnSizes);

    for (int row = 0; row < returnSize; row++) {
        for (int col = 0; col < returnColumnSizes[row]; col++) {
            printf("%d ", result[row][col]);
        }
        printf("\n");
        free(result[row]);
    }
    free(returnColumnSizes);
    free(result);
    return 0;
}
*/