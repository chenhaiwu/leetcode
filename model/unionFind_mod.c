/* 
 * 并查集[求网??接次?、] 
 * 并查集，注意要巧秒地利用?通?量的��?，
 * 求?通量，只要�s?父??0的��?即可。
 * 求每��?通量中，元素的��?：需要另外一��??，初始?0，在求?通?的?程中++。非0的值就是?��?通量中元素��?。
 * 并查集主要?是要思路如何利用?通分量。
 */

#define NODE_MAX 100001
int g_pre[NODE_MAX];
int g_reginCnt[NODE_MAX];
bool g_bDelFlag[NODE_MAX];
int g_groupCnts;

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
}

void HanldeAllParnet(int len)
{
    for (int i = 0; i < len; i++) {
        Find(i);
    }
}

int GetNewGroupCnts(int n, int** connections, int connectionsSize, int exp)
{
    for (int i = 0; i < n; i++) {
        g_pre[i] = i;
        g_reginCnt[i] = 0;
        g_bDelFlag[i] = false;
    }
    for (int i = 0; i < connectionsSize; i++) {
        if (g_bDelFlag[i] || i == exp) {
            continue;
        }
        int from = connections[i][0];
        int to = connections[i][1];
        Join(from, to);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int t = Find(i);
        if (g_reginCnt[t] == 0) {
            ans++;
        }
        g_reginCnt[t]++;
    }
    return ans;
}

/*
   但是不必要把每���ㄔh掉，然后再去查找?有几��?通分量。
   我?只要?明，如果���{多的?，一��?通分量一定有多余的�ㄐA然后每�V一���ㄐA就可以?��2��?通分量
   那么，最少的移�V是，?通分量 - 1
*/
int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize)
{
    g_groupCnts = GetNewGroupCnts(n, connections, connectionsSize, -1);
    if (g_groupCnts == 1) {
        return 0;
    }
    int curGroupCnts = g_groupCnts;
    if (connectionsSize < n - 1) return -1;
    return curGroupCnts - 1;
}

/* 网?病毒列中�蝪ㄓ@�纂A可以保�偃怞h的机器，注意�蝪ㄙ漪O病毒中，只有一�譟P染源的，
 * 如果病毒?中有���譟P染同一��?通?，?�蝪ㄓ@��?有作用 */
void InitParent(int** graph, int graphSize)
{
    for (int i = 0; i < graphSize; i++) {
        g_pre[i] = i;
        g_hashtype[i] = 0;
        g_delnum[i] = 0;
    }
    for (int i = 0; i < graphSize; i++) {
        for (int j = 0; j < graphSize; j++) {
            if (graph[i][j] == 1) {
                Join(i, j);
            }
        }
    }
    for (int i = 0; i < graphSize; i++) {
        int t = Find(i);
        g_hashtype[t]++;
    }
}

int minMalwareSpread(int** graph, int graphSize, int* graphColSize, int* initial, int initialSize)
{
    int maxNum = 0;
    int id = INT_MAX;
    InitParent(graph, graphSize);
    for (int i = 0; i < initialSize; i++) {
        int t = Find(initial[i]);
        g_delnum[t]++;
    }
    for (int i = 0; i < initialSize; i++) {
        int delV = initial[i];
        int devLP = Find(delV);
        if (g_delnum[devLP] == 1) {
            if (g_hashtype[devLP] == maxNum) {
                id = MIN(id, delV);
            } else if (g_hashtype[devLP] > maxNum) {
                id = delV;
                maxNum = g_hashtype[devLP];
            }
        }
    }
    if (id == INT_MAX) {
        for (int i = 0; i < initialSize; i++) {
            id = MIN(id, initial[i]);
        }
    }
    return id;
}