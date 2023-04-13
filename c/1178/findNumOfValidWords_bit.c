#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/*
    O(MN)的算法超时，即使已经使用上了BIT位操作还是超时
*/

int* findNumOfValidWords1(char ** words, int wordsSize, char ** puzzles, int puzzlesSize, int* returnSize)
{
    int *wordsHash = (int *)malloc(sizeof(int) * wordsSize);
    for (int i = 0; i < wordsSize; i++) {
        wordsHash[i] = 0;
        int len  = strlen(words[i]);
        for (int j = 0; j < len; j++) {
            wordsHash[i] |= (0x1 << (words[i][j] - 'a'));
        }
        printf("%08x ", wordsHash[i]);
    }
    printf("\n");
    int *puzHash = (int *)malloc(sizeof(int) * puzzlesSize);
    for (int i = 0; i < puzzlesSize; i++) {
        puzHash[i] = 0;
        int len  = strlen(puzzles[i]);
        for (int j = 0; j < len; j++) {
            puzHash[i] |= (0x1 << (puzzles[i][j] - 'a'));
        }
        printf("%08x ", puzHash[i]);
    }
    printf("\n");

    int *ret = (int *)malloc(sizeof(int) * puzzlesSize);
    *returnSize = puzzlesSize;
    for (int i = 0; i < puzzlesSize; i++) {
        int cnt = 0;
        for (int j = 0; j < wordsSize; j++) {
            if ((wordsHash[j] & (0x1 << (puzzles[i][0] - 'a'))) == 0) continue;
            if ((puzHash[i] | wordsHash[j]) != puzHash[i]) continue;
            cnt++;
        }
        ret[i] = cnt;
    }
    return ret;
}

typedef struct my_struct {
    int id;            /* we'll use this field as the key */
    int value;
    UT_hash_handle hh; /* makes this structure hashable */
}HashNode;
typedef HashNode* HashHead;

HashNode *find_user(HashHead head, int user_id) {
    HashNode *s;
    HASH_FIND_INT(head, &user_id, s);  /* s: output pointer */
    return s;
}
int count_user(HashHead head) {
    return HASH_COUNT(head);
}
void print_user(HashHead head) {
    HashNode *s;
    printf("size is %d\n", count_user(head));
    for (s = head; s != NULL; s = s->hh.next) {
        printf("user id %d, value %d\n", s->id, s->value);
    }
}

int add_user_exist(HashHead *head, int id, int val) {
    HashNode *node = find_user(*head, id);
    if(node != NULL) {
        node->value = node->value + val;
        return node->value;
    } else {
        node = (HashNode *)malloc(sizeof(HashNode));
        node->id = id;
        node->value = val;
        HASH_ADD_INT(*head, id, node);
        return -1;
    }
}

int bitSet(int mask, int bit) {
    return mask | (1 << bit);
}

int bitClr(int mask, int bit) {
    return mask & (~(1 << bit));
}

bool bitTest(int mask, int bit) {
    if((mask & (1 << bit)) >> bit == 1) {
        return true;
    }else{
        return false;
    }
}

int* findNumOfValidWords(char ** words, int wordsSize, char ** puzzles, int puzzlesSize, int* returnSize)
{
    HashHead head = NULL;
    int *wordsHash = (int *)malloc(sizeof(int) * wordsSize);
    for (int i = 0; i < wordsSize; i++) {
        wordsHash[i] = 0;
        int len  = strlen(words[i]);
        for (int j = 0; j < len; j++) {
            wordsHash[i] = bitSet(wordsHash[i], words[i][j] - 'a');
        }
        add_user_exist(&head, wordsHash[i], 1);
    }
    int *puzHash = (int *)malloc(sizeof(int) * puzzlesSize);
    for (int i = 0; i < puzzlesSize; i++) {
        puzHash[i] = 0;
        int len  = strlen(puzzles[i]);
        for (int j = 0; j < len; j++) {
            puzHash[i] = bitSet(puzHash[i], puzzles[i][j] - 'a');
        }
    }

    int *ret = (int *)malloc(sizeof(int) * puzzlesSize);
    *returnSize = puzzlesSize;
    int wordsusercnt = count_user(head);
    for (int i = 0; i < puzzlesSize; i++) {
        int cnt = 0;
        HashNode *s;
        int firstpos = puzzles[i][0] - 'a';
        // 优化2，注意只对puzzele的哈希值遍历，因为其最大长度为128，而且一定要保证首字母不丢，即如果首字符的位置1不丢，且这个新的值在word hash里有了。
        for (int j = puzHash[i]; j != 0; j = ((j - 1) & puzHash[i])) {
            s = find_user(head, j);
            if (bitTest(j, firstpos) && s != NULL) {
                cnt += s->value;
            }
        }
        // 优化1，把word去重，不管用，还是超时
        // for (s = head; s != NULL; s = s->hh.next) {
        //     printf("user id %d, value %d\n", s->id, s->value);
        //     if ((s->id & (0x1 << (puzzles[i][0] - 'a'))) == 0) continue;
        //     if ((puzHash[i] | s->id) != puzHash[i]) continue;
        //     cnt = cnt + s->value;
        // }
        // 最开始的遍历，使用o(mn)的复杂度，超时
        // for (int j = 0; j < wordsSize; j++) {
        //     if ((wordsHash[j] & (0x1 << (puzzles[i][0] - 'a'))) == 0) continue;
        //     if ((puzHash[i] | wordsHash[j]) != puzHash[i]) continue;
        //     cnt++;
        // }
        ret[i] = cnt;
    }
    return ret;
}

void main()
{
    char *words[7] = {"aaaa","asas","able","ability","actt","actor","access"};
    char *puzzles[7] = {"aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz", "paswxyz"};
    char **pwords = (char **)malloc(sizeof(char *) * 7);
    char **ppuzzles = (char **)malloc(sizeof(char *) * 7);
    for (int i = 0; i < 7; i++) {
        pwords[i] = (char *)malloc(sizeof(char) * 10);
        memset(pwords[i], 0x0, 10);
        strcpy(pwords[i], words[i]);
        ppuzzles[i] = (char *)malloc(sizeof(char) * 20);
        memset(ppuzzles[i], 0x0, 20);
        strcpy(ppuzzles[i], puzzles[i]);
    }
    int retSize = 0;
    int *ret = findNumOfValidWords(pwords, 7, ppuzzles, 7, &retSize);
    for (int i = 0; i < retSize; i++) {
        printf("%d ", ret[i]);
    }
    printf("\n");
    printf("ret = %d\n", retSize);
    return;
}