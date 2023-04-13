#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAX_N 100001
char g_flag[MAX_N];

int CheckSpec(char *s, char *sc)
{
    int ans = -1;
    if (strncmp(s, "&quot;", 6) == 0) {
        *sc = '"';
        return 6;
    }
    if (strncmp(s, "&apos;", 6) == 0) {
        *sc = '\'';
        return 6;
    }
    if (strncmp(s, "&amp;", 5) == 0) {
        *sc = '&';
        return 5;
    }
    if (strncmp(s, "&gt;", 4) == 0) {
        *sc = '>';
        return 4;
    }
    if (strncmp(s, "&lt;", 4) == 0) {
        *sc = '<';
        return 4;
    }
    if (strncmp(s, "&frasl;", 7) == 0) {
        *sc = '/';
        return 7;
    }
    return ans;
}

char * entityParser(char * s)
{
    int len = strlen(s);
    memset(g_flag, 0x0, sizeof(g_flag));

    for (int i = 0; i < len; ) {
        if (s[i] != '&') {
            g_flag[i] = s[i];
            i++;
            continue;
        } else {
            char sc;
            int speclen = CheckSpec(&s[i], &sc);
            if (speclen == -1) {
                g_flag[i] = s[i];
                i++;
                continue;
            } else {
                g_flag[i] = sc;
                i += speclen;
            }
        }
    }
    char *ret = (char *)malloc(len + 1);
    int retlen = 0;
    for (int i = 0; i < len; i++) {
        if (g_flag[i] != 0) {
            ret[retlen++] = g_flag[i];
        }
    }
    ret[retlen] = '\0';
    return ret;
}

void main()
{
    char *ans;
    ans = entityParser("&amp; is an HTML entity but &ambassador; is not.");
    printf("%s\n", ans);
    return;
}