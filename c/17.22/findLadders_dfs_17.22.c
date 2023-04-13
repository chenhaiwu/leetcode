#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DEGUG_CHW 1
void PrintArray(int* nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
#endif
}
void PrintWords(char ** nums, int numsSize)
{
#ifdef DEGUG_CHW
    for (int i = 0; i < numsSize; i++) {
        printf("%s\n", nums[i]);
    }
    printf("\n");
#endif
}

char **g_wordList;
int g_wordsNum;
int **g_canSel;
int *g_path;
int *g_visit;
int g_pathSize;
int g_targetID;

int IsCanSwitch(char * s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) {
        return 0;
    }
    int cnt = 0;
    for (int i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            cnt++;
            if (cnt >= 2) {
                return 0;
            }
        }
    }
    return cnt == 1 ? 1 : 0;
}

void PreHandle(char* beginWord, char* endWord, char** wordList, int wordListSize)
{
    g_wordsNum = wordListSize + 1;
    g_wordList = (char **)malloc(sizeof(char *) * (wordListSize + 1));
    for (int i = 0; i <= wordListSize; i++) {
        int len = 0;
        if (i == 0) {
            len = strlen(beginWord) + 1;
            g_wordList[i] = (char *)malloc(len);
            memset(g_wordList[i], 0x0, len);
            strcpy(g_wordList[i], beginWord);
        } else {
            len = strlen(wordList[i - 1]) + 1;
            g_wordList[i] = (char *)malloc(len);
            memset(g_wordList[i], 0x0, len);
            strcpy(g_wordList[i], wordList[i - 1]);
        }
    }
    g_canSel = (int **)malloc(sizeof(int *) * g_wordsNum);
    for (int i = 0; i < g_wordsNum; i++) {
        g_canSel[i] = (int *)malloc(sizeof(int) * g_wordsNum);
        memset(g_canSel[i], -1, sizeof(int) * g_wordsNum);
    }
    for (int i = 0; i < g_wordsNum; i++) {
        int cnt = 0;
        for (int j = 0; j < g_wordsNum; j++) {
            int isSel = IsCanSwitch(g_wordList[i], g_wordList[j]);
            if (isSel == 1) {
                g_canSel[i][cnt++] = j;
            }
            
        }
    }

    g_path = (int *)malloc(sizeof(int) * g_wordsNum);
    memset(g_path, 0x0, sizeof(int) * g_wordsNum);
    g_pathSize = 0;
    g_visit = (int *)malloc(sizeof(int) * g_wordsNum);
    memset(g_visit, 0x0, sizeof(int) * g_wordsNum);
}

char** ResultPrepare(int* returnSize)
{
    char **ret = (char **)malloc(sizeof(char *) * (g_pathSize));
    for (int i = 0; i < g_pathSize; i++) {
        int idx = g_path[i];
        int len = strlen(g_wordList[idx]) + 1;
        ret[i] = (char *)malloc(len);
        memset(ret[i], 0x0, len);
        strcpy(ret[i], g_wordList[idx]);
    }
    *returnSize = g_pathSize;
    return ret;
}

void AfterHandle()
{
    for (int i = 0; i < g_wordsNum; i++) {
        free(g_canSel[i]);
        free(g_wordList[i]);
    }
    free(g_canSel);
    free(g_wordList);
    free(g_path);
    free(g_visit);
}

int Step(int step, int curId, int targetId)
{
    if (step > g_wordsNum) {
        return -1;
    }
    if (curId == targetId) {
        g_pathSize = step;
        return 1;
    }
    int ret = 0;
    for (int i = 0; i < g_wordsNum && g_canSel[curId][i] != -1; i++) {
        int mudi = g_canSel[curId][i];
        if (g_visit[mudi] == 1) {
            continue;
        }
        g_visit[mudi] = 1;
        g_path[step] = mudi;
        ret = Step(step + 1, mudi, targetId);
        if (ret == 1) break;
        g_visit[i] = 0;
    }
    return ret;
}

void Dfs(int targetId)
{
    g_path[0] = 0;
    g_visit[0] = 1;
    Step(1, 0, targetId);
}

int FindTargetWordIdx(char *endword)
{
    int ans = -1;
    for (int i = 0; i < g_wordsNum; i++) {
        if (strcmp(endword, g_wordList[i]) == 0) {
            ans = i;
            break;
        }
    }
    return ans;
}

/*
 * 1: ?¬dendword¬O§_¦b¦r¨å¨½¡A¦pªG¤£¬O¡Aª½±µªð¦^¡C
 * 2¡G¦p¦ó¦s?¦UŸÄ??¬O§_¥i¥H??¡A§Ë¤@ŸÄ¯x?¥Î¤_«O¦s?¨t¡A‰V??«Ø¡A?¬d¦r²Å¥u¯à®t¤@ŸÄ¡A¦pªG¤£¬O¡A
 *    ??0.¡A¯x?²ÄŸÄ¤¸¯À¡A«O¦sbegin¡C
 * 3¡G¥t¥~¡A¦A¥Î¤@ŸÄ¤@ŸÄªÅšV«O¦sŸÏ0¨ìwordlistªºªÅšV
 * 4: dfs¡A¦pªGºâ¡C¨C¤@¨B¦b¥i?ªº¨½­±?¡A«O¦sg_path¡C
*/
char** findLadders(char* beginWord, char* endWord, char** wordList, int wordListSize, int* returnSize)
{
    PreHandle(beginWord, endWord, wordList, wordListSize);
PrintWords(wordList, wordListSize);
    g_targetID = FindTargetWordIdx(endWord);
    if (g_targetID == -1) {
        AfterHandle();
        *returnSize = 0;
        return NULL;
    }

    // dfs
    Dfs(g_targetID);

    char ** ret = ResultPrepare(returnSize);

    AfterHandle();
    return ret;
}

int main()
{
    int wordListSize = 6;
    int wordLen = 4;
    char **grid = NULL;
    char* t1[6] = {"hot","dot","dog","lot","log","cog"};
    char *beginWord = "hit";
    char *endWord = "cog";
    char ***result = NULL;
    int returnSize;
    int *returnColumnSizes = NULL;

    grid = malloc(wordListSize * sizeof(char *));
    for (int i = 0; i < wordListSize; i++) {
        grid[i] = malloc(wordLen * sizeof(char));
        strcpy(grid[i], t1[i]);
    }

    result = findLadders(beginWord, endWord, grid, wordListSize, &returnSize);
    PrintWords(result, returnSize);
    free(grid);
    free(result);
    return 0;
}