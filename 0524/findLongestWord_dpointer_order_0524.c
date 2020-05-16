#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

int Cmp(void *a, void *b)
{
    char *ta = *(char **)a;
    char *tb = *(char **)b;
    if (strlen(ta) == strlen(tb)) {
        return strcmp(ta, tb);
    }
    return strlen(tb) - strlen(ta);
}

char * findLongestWord(char * s, char ** d, int dSize)
{
    qsort(d, dSize, sizeof(char *), Cmp);
    char *ret = "";
    int maxLen = 0;
    for (int i = 0; i < dSize; i++) {
        char *p = d[i];
        char *q = s;
        int len = strlen(d[i]);
        while (*p != '\0' && *q != '\0') {
            if (*p == *q) {
                p++;
            }
            q++;
        }
        if (*p == '\0' && len > maxLen) {
            maxLen = len;
            ret = d[i];
        }
    }
    return ret;
}