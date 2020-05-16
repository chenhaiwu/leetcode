#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

int Max(int a, int b)
{
    if (a > b) return a;
    else return b;
}

int Cmp(void *a, void *b)
{
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    return s1 - s2;
}

bool IsSubString(char *s1, char *s2)
{
    char *p1 = s1;
    char *p2 = s2;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 + 1 != len2) {
        return false;
    }
    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 == *p2) {
            p1++;
            p2++;
        } else {
            p2++;
        }
    }
    if (*p2 != '\0') p2++;
    if (!p1 && !p2) {
        return true;
    } else {
        return false;
    }
}

int Step(int idx, char ** words, int wordsSize)
{
    int ret = 1;
    for (int i = idx + 1; i < wordsSize; i++) {
        if (IsSubString(words[idx], words[i])) {
            int ans = Step(i, words, wordsSize);
            ret = Max(ret, ans + 1);
        }
    }
    return ret;
}

// baoli¡Ay?¼É¤O¡A?¨C¤@ŸÄiªº??¡A§@??©lªº¦r²Å¦ê¡AµM¦Z¬Ý¤U¦Z­±ªº¨CŸÄ¦ê¬O§_?¨¬¤l¦ê˜ç¥ó¡A¬Oªº?+1¡AµM¦Z?¤@ŸÄi³Ì¤jªº¡C
int longestStrChain(char ** words, int wordsSize)
{
    int ret = 0;
    qsort(words, wordsSize, sizeof(char *), Cmp);
    for (int i = 0; i < wordsSize; i++) {
        int ans = Step(i, words, wordsSize);
        ret = Max(ans, ret);
    }
    return ret;
}