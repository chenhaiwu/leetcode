#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/*  �㷨1��������ѧ + ÿ�β�ѯʱ��ʹ��hash����ͳ�����ֳ��ִ��������Ƚ����ֳ��ֵķ�������������hash ID��
    �������ݳ���ΪN����ѯ����ΪM����
    �ռ临�Ӷȣ�O(N + M)��ʱ�临�Ӷȣ���������£�O(20000 * M)
    �����25/27
    �㷨2������ʹ��������hash��ÿ�ζ�Ҫȥ��������Ԫ�أ��޸ĳ�ʹ��hash�����������ж��ٸ�Ԫ�أ��ͱ������ٴ�
    �ռ临�Ӷȣ�O(N + M)��ʱ�临�Ӷȣ���������£�O(N*M) = O(N * M)
    �����22/27����������Щcase�����ˣ�����hash�и��������
    �㷨3��ֻ��˼��һ�£���ÿ��left->right��hashֵ����ס������һֱ�顣
    �ռ临�Ӷȣ�O(N + M)��ʱ�临�Ӷȣ���������£�O(N*M) = O(N * M)
    �����22/27����������Щcase�����ˣ�����hash�и��������
*/

/* //�㷨1
#define MAX_NUM 20001
int g_hash[MAX_NUM];

typedef struct {
    int *arr;
    int len;
} MajorityChecker;


MajorityChecker* majorityCheckerCreate(int* arr, int arrSize) {
    MajorityChecker* obj = (MajorityChecker*)malloc(sizeof(MajorityChecker));
    obj->arr = (int *)malloc(sizeof(int) * arrSize);
    for (int i = 0; i < arrSize; i++) {
        obj->arr[i] = arr[i];
    }
    obj->len = arrSize;
    return obj;    
}

int majorityCheckerQuery(MajorityChecker* obj, int left, int right, int threshold) {
    int ret = -1;
    int hashLen = right - left + 1;
    memset(g_hash, 0x0, sizeof(g_hash));
    for (int i = left; i <= right; i++) {
        g_hash[obj->arr[i]]++;
    }
    for (int i = 0; i < MAX_NUM; i++) {
        if (g_hash[i] >= threshold) {
            ret = i;
            break;
        }
    }
    return ret;
}

void majorityCheckerFree(MajorityChecker* obj) {
    if (obj != NULL) {
        if (obj->arr != NULL) {
            free(obj->arr);
            obj->arr = NULL;
            obj->len = 0;
        }
        free(obj);
        obj = NULL;
    }
    return;
}
*/

typedef struct my_struct {
    int id;
    int value;
    UT_hash_handle hh;
} HashNode;
typedef HashNode *HashHead;

HashNode *find_user(HashHead head, int user_id)
{
    HashNode *s;
    HASH_FIND_INT(head, &user_id, s);
    return s;
}

int count_user(HashHead head)
{
    return HASH_COUNT(head);
}

void print_user(HashHead head)
{
    HashNode *s;
    for (s = head; s != NULL; s = s->hh.next) {
        printf("user id %d, value %d\n", s->id, s->value);
    }
}

int ModifyHash(HashHead *head, int id, int val)
{
    HashNode *node = find_user(*head, id);
    if (node == NULL) {
        return -1;
    } else {
        if (node->value > 1) {
            node->value -= val;
        } else {
            HASH_DEL(*head, node);
        }
        return 1;
    }
}

int AddHashExist(HashHead *head, int id, int val)
{
    HashNode *node = find_user(*head, id);
    if (node != NULL) {
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

typedef struct {
    int *arr;
    int len;
} MajorityChecker;


MajorityChecker* majorityCheckerCreate(int* arr, int arrSize) {
    MajorityChecker* obj = (MajorityChecker*)malloc(sizeof(MajorityChecker));
    obj->arr = (int *)malloc(sizeof(int) * arrSize);
    for (int i = 0; i < arrSize; i++) {
        obj->arr[i] = arr[i];
    }
    obj->len = arrSize;
    return obj;    
}

int majorityCheckerQuery(MajorityChecker* obj, int left, int right, int threshold) {
    int ret = -1;
    int hashLen = right - left + 1;
    HashHead headHead = NULL;
    for (int i = left; i <= right; i++) {
        AddHashExist(&headHead, obj->arr[i], 1);
    }

    HashNode *s;
    for (s = headHead; s != NULL; s = s->hh.next) {
        if (s->value >= threshold) {            
            ret = s->id;
            break;
        }
    }
    return ret;
}

void majorityCheckerFree(MajorityChecker* obj) {
    if (obj != NULL) {
        if (obj->arr != NULL) {
            free(obj->arr);
            obj->arr = NULL;
            obj->len = 0;
        }
        free(obj);
        obj = NULL;
    }
    return;
}

void main()
{
    int ret = 0;
    printf("ret = %d\n", ret);
}