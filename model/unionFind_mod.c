/* 
 * ¦}¬d¶°[¨DÊI??±µ¦¸?¡B] 
 * ¦}¬d¶°¡Aª`·N­n¥©¬í¦a§Q¥Î?³q?¶qªºŸÄ?¡A
 * ¨D?³q¶q¡A¥u­n‰s?¤÷??0ªºŸÄ?§Y¥i¡C
 * ¨D¨CŸÄ?³q¶q¤¤¡A¤¸¯ÀªºŸÄ?¡G»Ý­n¥t¥~¤@ŸÄ??¡Aªì©l?0¡A¦b¨D?³q?ªº?µ{¤¤++¡C«D0ªº­È´N¬O?ŸÄ?³q¶q¤¤¤¸¯ÀŸÄ?¡C
 * ¦}¬d¶°¥D­n?¬O­n«ä¸ô¦p¦ó§Q¥Î?³q¤À¶q¡C
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
   ¦ý¬O¤£¥²­n§â¨C˜ç£¥h±¼¡AµM¦Z¦A¥h¬d§ä?¦³¤LŸÄ?³q¤À¶q¡C
   §Ú?¥u­n?©ú¡A¦pªG£û{¦hªº?¡A¤@ŸÄ?³q¤À¶q¤@©w¦³¦h§Eªº£¡AµM¦Z¨C‰V¤@˜ç£¡A´N¥i¥H?þ2ŸÄ?³q¤À¶q
   ¨º¤\¡A³Ì¤Öªº²¾‰V¬O¡A?³q¤À¶q - 1
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

/* ÊI?¯f¬r¦C¤¤ ç°£¤@ŸÄ¡A¥i¥H«O“°³Ì¦hªºÉó¾¹¡Aª`·N ç°£ªº¬O¯f¬r¤¤¡A¥u¦³¤@ŸÄ·P¬V·½ªº¡A
 * ¦pªG¯f¬r?¤¤¦³‰ÎŸÄ·P¬V¦P¤@ŸÄ?³q?¡A? ç°£¤@ŸÄ?¦³§@¥Î */
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