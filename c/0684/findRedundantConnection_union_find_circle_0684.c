#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
/*
这题需要分三种情况讨论
有环，有2入度
=> 找一条边同时满足这两个条件，删掉2入度的且在环中的边
=> 用并查集，因为希望找的是入度2的边，所以这两条边最后union，union失败的边就是要找的
有环，无2入度
=> 找一条在环中的边，看成无向图找形成环的边
=> 并查集的经典应用
无环，有2入度 (1、2两种情况处理完后还没有结果输出，说明是情况3)
=> 找去掉后仍然连通的边
=> 因为多余的边是在原本就是树的基础上找两个现有的点连的边，所以删哪一条都行，按照题意可删最后一条


这是上面的分析：首先最后的结果一定是无环的。
其实1和3可以再合并，也就是说，从后往前找：如果找到入度为2的边，然后把这条边去掉，剩下的只要无环，就一定是所要找的。
不管一开始他是有环的还是无环的，只要最后结果是无环的，那么就是要找的
（有环，只有一条边，无环的话，从后往前找，则一定也是正确答案）
如果是入度为1，则去掉这条边，最后是无环的，也可以。

所以关键函数：检查一条有向图是否是有环的，可以使用并查集，每次少算一条边，然后统计边数，只要每条边的入度都为1，
可以考虑从新赋值fa，每次联一次就计数--，最后计数是1，就表示没有环。如果有环的话，就不--，一定大于1.

本题是无环：则只需要考虑，从往后前检查，每skip一条边，只要不存在环，即可。检查环的函数仍然是通用的。

*/

int Find(int i, int *fa)
{
    if (fa[i] != i) {
        fa[i] = Find(fa[i], fa);
    }
    return fa[i];
}

bool IsNotCircleWithoutEdgeId(int** edges, int edgesSize, int skipedge, int *fa)
{
    int ans = edgesSize;
    for (int i = 1; i <= edgesSize; i++) {
        fa[i] = i;
    }
    for (int i = 0; i < edgesSize; i++) {
        if (i == skipedge) {
            continue;
        }
        int fx = Find(edges[i][0], fa);
        int fy = Find(edges[i][1], fa);
        if (fx != fy) {
            ans--;
            fa[fy] = fx;
        }
    }
    // 检查减后的计数值，如果是1，则表示无环，如果有环的话，这个值一定大于1.
    // printf("ans=%d\n", ans);
    return ans == 1;
}

int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize)
{
    int *ret = (int *)malloc(sizeof(int) * 2);
    *returnSize = 2;
    // int *indegree = (int *)malloc(sizeof(int) * (edgesSize + 1));
    // memset(indegree, 0x0, sizeof(int) * (edgesSize + 1));
    int *fa = (int *)malloc(sizeof(int) * (edgesSize + 1));
    // for (int i = 0; i < edgesSize; i++) {
    //     indegree[edges[i][1]]++;
    // }
    for (int i = edgesSize - 1; i >= 0; i--) {
        // if (indegree[edges[i][1]] == 2) {
            if (IsNotCircleWithoutEdgeId(edges, edgesSize, i, fa)) {
                ret[0] = edges[i][0];
                ret[1] = edges[i][1];
                goto RET;
            }
        // }
    }
    // for (int i = edgesSize - 1; i >= 0; i--) {
    //     if (indegree[edges[i][1]] == 1) {
    //         if (IsNotCircleWithoutEdgeId(edges, edgesSize, i, fa)) {
    //             ret[0] = edges[i][0];
    //             ret[1] = edges[i][1];
    //             goto RET;
    //         }
    //     }
    // }
RET:
    free(fa);
    // free(indegree);
    return ret;
}