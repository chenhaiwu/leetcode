/* 
 * �}�d��[�D�I??����?�B] 
 * �}�d���A�`�N�n����a�Q��?�q?�q����?�A
 * �D?�q�q�A�u�n�s?��??0����?�Y�i�C
 * �D�C��?�q�q���A��������?�G�ݭn�t�~�@��??�A��l?0�A�b�D?�q?��?�{��++�C�D0���ȴN�O?��?�q�q��������?�C
 * �}�d���D�n?�O�n����p��Q��?�q���q�C
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
   ���O�����n��C�督�h���A�M�Z�A�h�d��?���L��?�q���q�C
   ��?�u�n?���A�p�G���{�h��?�A�@��?�q���q�@�w���h�E�����A�M�Z�C�V�@�督�A�N�i�H?��2��?�q���q
   ���\�A�̤֪����V�O�A?�q���q - 1
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

/* �I?�f�r�C���簣�@�ġA�i�H�O���̦h���󾹡A�`�N�簣���O�f�r���A�u���@�ķP�V�����A
 * �p�G�f�r?�����ΟķP�V�P�@��?�q?�A?�簣�@��?���@�� */
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