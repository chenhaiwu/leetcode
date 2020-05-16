#define MAX_N 101
char g_ret[MAX_N * 3];
int g_len;
int g_used;

char GetNextChar(int *a, int *b, int *c)
{
    int m = *a;
    int n = *b;
    int p = *c;
    if (g_used == 1) m = 0;
    if (g_used == 2) n = 0;
    if (g_used == 3) p = 0;
    if (m >= n && m >= p && m > 0) {
        *a = m - 1;
        g_used = 0;
        return 'a';
    }
    if (n >= m && n >= p && n > 0) {
        *b = n - 1;
        g_used = 0;
        return 'b';
    }
    if (p >= n && p >= m && p > 0) {
        *c = p- 1;
        g_used = 0;
        return 'c';
    }
    return '0';
}

char * longestDiverseString(int a, int b, int c)
{
    memset(g_ret, 0x0, sizeof(g_ret));
    g_len = 0;
    g_used = 0;
    
    while (1) {
        char tmp = GetNextChar(&a, &b, &c);
        if (tmp == '0') {
            break;
        }
        g_ret[g_len++] = tmp;
        if (g_len >= 2 && g_ret[g_len - 2] == g_ret[g_len - 1] && g_ret[g_len - 2] == 'a') {
            g_used = 1;
        }
        if (g_len >= 2 && g_ret[g_len - 2] == g_ret[g_len - 1] && g_ret[g_len - 2] == 'b') {
            g_used = 2;
        }
        if (g_len >= 2 && g_ret[g_len - 2] == g_ret[g_len - 1] && g_ret[g_len - 2] == 'c') {
            g_used = 3;
        }
    }
    return g_ret;
}