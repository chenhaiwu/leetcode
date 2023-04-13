#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_FOLDER_NUM 4001
#define MAX_FOLDER_LEN 101
#define MIN(a, b) (a) < (b) ? (a) : (b)

void PrintText(char ** folder, int folderSize)
{
    for (int i = 0; i < folderSize; i++) {
        printf("%s\n", folder[i]);
    }
}

int Cmp(void *a, void *b)
{
    char *p1 = *(char **)(a);
    char *p2 = *(char **)(b);
    return strcmp(p1, p2);
}

char ** removeSubfolders(char ** folder, int folderSize, int* returnSize)
{
    char **ret = (char **)malloc(folderSize * sizeof(char *));
    int cnt = 0;
    if (folderSize == 0 || folder == NULL) {
        *returnSize = cnt;
        return NULL;
    }
    PrintText(folder, folderSize);
    qsort(folder, folderSize, sizeof(char *), Cmp);
    PrintText(folder, folderSize);
    int folerLen = strlen(folder[0]);
    ret[0] = (char *)malloc(sizeof(char) * (folerLen + 1));
    strcpy(ret[0], folder[0]);
    ret[0][folerLen] = '\0';
    cnt++;
    printf("print ret0\n");
    PrintText(ret, cnt);

    for (int i = 1; i < folderSize; i++) {

        int len1 = strlen(ret[cnt - 1]);
        int len2 = strlen(folder[i]);
        int len = MIN(len1, len2);
        if (strncmp(ret[cnt - 1], folder[i], len) == 0 && len1 < len2 && folder[i][len] == '/') {
            continue;
        }
        ret[cnt] = (char *)malloc(sizeof(char) * (len2 + 1));
        strcpy(ret[cnt], folder[i]);
        ret[cnt][len2] = '\0';
        cnt++;
        PrintText(ret, cnt);
    }
    *returnSize = cnt;
    return ret;
}


int main()
{
    //int retsize = removeSubfolders(s, words, 4);
    // PrintArray(nums, sizeof(nums) / sizeof(int));
    return 0;
}
