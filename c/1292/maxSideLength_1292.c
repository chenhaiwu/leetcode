#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)


#define MAXR 301
#define MAXC 301
int dp[MAXR][MAXC];

int maxSideLength(int** mat, int matSize, int* matColSize, int threshold)
{
    int ret = 0;
    int m = matSize;
    int n = matColSize[0];
    int MaxN = MIN(m, n);
    memset(dp, 0x0, sizeof(dp));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] =  mat[i - 1][j - 1] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
        }
    }
    for (int k = 1; k <= MaxN; k++) {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (i - k < 0 || j - k < 0) {
                    continue;
                }
                int tmp = dp[i][j] - dp[i - k][j] - dp[i][j - k] + dp[i - k][j - k];
                if (tmp <= threshold) {
                    ret = MAX(ret, k);
                }
            }
        }
    }
    return ret;
}