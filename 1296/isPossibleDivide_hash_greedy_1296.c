#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

/* 
 * 
 */

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

int Cmp(const void *a, const void *b)
{
    int ta = *(int *)a;
    int tb = *(int *)b;
    return ta > tb;
}

typedef struct my_struct {
    int id;            /* we'll use this field as the key */
    int value;
    UT_hash_handle hh; /* makes this structure hashable */
} HashNode;
typedef HashNode* HashHead;

int count_user(HashHead head);
HashNode *find_user(HashHead head, int user_id) {
    HashNode *s;
    HASH_FIND_INT(head, &user_id, s);
    return s;
}
void add_user(HashHead *head, HashNode *users) {
    if(!find_user(*head, users->id))
        HASH_ADD_INT(*head, id, users);
}
void replace_user(HashHead *head, HashNode *newNode) {
    HashNode *oldNode = find_user(*head, newNode->id);
    if (oldNode)
        HASH_REPLACE_INT(*head, id, newNode, oldNode);
}
void delete_user(HashHead *head,HashNode *user) {
    if (user) {
        HASH_DEL(*head, user);
        free(user);
    }
}

int add_user_exist(HashHead *head, int id, int val) {
    HashNode *node = find_user(*head, id);
    if(node != NULL) {
        node->value += val;
        return node->value;
    } else {
        node = (HashNode *)malloc(sizeof(HashNode));
        node->id = id;
        node->value = val;
        HASH_ADD_INT(*head, id, node);
        return -1;
    }
}

bool isPossibleDivide_1(int* nums, int numsSize, int k)
{
    bool ans = true;
    if (numsSize % k != 0) {
        return false;
    }
    qsort(nums, numsSize, sizeof(int), Cmp);
    PrintArray(nums, numsSize);
    
    HashHead head = NULL;
    for (int i = 0; i < numsSize; i++) {
        add_user_exist(&head, nums[i], 1);
    }

    for (int i = 0; i < numsSize; i++) {
        HashNode *node = find_user(head, nums[i]);
        if (node->value <= 0) {
            continue;
        }
        for (int j = 0; j < k; j++) {
            HashNode *nodeJ = find_user(head, nums[i] + j);
            if (!nodeJ || nodeJ->value <= 0) {
                return false;
            }
            nodeJ->value--;
        }
    }

    return ans;
}

bool isPossibleDivide(int* nums, int numsSize, int k)
{
    bool ans = true;
    if (numsSize % k != 0) {
        return false;
    }

    int tongSize = numsSize / k;
    int *tongK = (int *)malloc(sizeof(int) * k);
    memset(tongK, 0x0, sizeof(int) * k);
    
    for (int i = 0; i < numsSize; i++) {
        tongK[nums[i] % k]++;
    }
    for (int i = 0; i < k; i++) {
        if (tongK[i] != tongSize) {
            return false;
        }
    }
    return ans;
}

int main()
{
    int a[] = {1,2,3,3,4,4,5,6};
    int w = 4;
    bool ret = isPossibleDivide(a, sizeof(a)/sizeof(int), w);
    printf("ret=%d\n", ret);
    return 0;
}