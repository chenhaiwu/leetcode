#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct my_struct {
    int id;            /* we'll use this field as the key */
    int value;
    UT_hash_handle hh; /* makes this structure hashable */
}HashNode;
typedef HashNode* HashHead;

int count_user(HashHead head);
HashNode *find_user(HashHead head, int user_id) {
    HashNode *s;
    HASH_FIND_INT(head, &user_id, s);  /* s: output pointer */
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
        HASH_DEL(*head, user);  /* user: pointer to deletee */
        free(user);             /* optional; it's up to you! */
    }
}
void print_user_iterator(HashHead head) {
    HashNode *s, *tmp;
    printf("size is %d\n", count_user(head));
    HASH_ITER(hh, head, s, tmp) {
        printf("user id %d: value is %d\n", s->id, s->value);
        /* ... it is safe to delete and free s here */
    }
}
int count_user(HashHead head) {
    return HASH_COUNT(head);
}
int name_sort(HashNode *a, HashNode *b) {
	   return a->value, b->value;
}

int id_sort(HashNode *a, HashNode *b) {
	   return (a->id - b->id);
}

void sort_by_name(HashHead *head) {
	   HASH_SORT(*head, name_sort);
}

void sort_by_id(HashHead *head) {
	   HASH_SORT(*head, id_sort);
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

/*
   ����1��ʹ��ÿһ������i - > j �Ļ��ֵ��key�����뵽hash�У������������ֵΪ1��������+1��
   for (i : 0->len) {
     key = 0;
     for (j: i, -> len) {
       key |= A[j];
       AddHash(key, value: 1)
     }
   }
   ע��㣺�㷨���Ӷ�Ϊn^2, hashû�а취ʹ��һ��INT���飬��Ϊֵ10^9��̫��
   1 <= A.length <= 50000
   0 <= A[i] <= 10^9
    ʵ�ʽ������ʱ 72/83
*/
int subarrayBitwiseORs1(int* A, int ASize)
{
    int ret;
    HashHead head = NULL;
    for (int i = 0; i < ASize; i++) {
        int key = 0;
        for (int j = i; j < ASize; j++) {
            key |= A[j];
            add_user_exist(&head, key, 1);
        }
    }
    ret = count_user(head);
    return ret;
}

/*
    ����2��1��n^2�ټ��� hash��ʱ�ˣ� ���Ǽ�֦�� ʵ�ʽ������ʱ 80/83
    ��ʱ˼�����ܷ��֦�����߼��仯��
    ��֦��������е�λ��϶������ˣ��Ͳ���Ҫ�ˣ�����Ҫ��ÿ��iѭ���У�j�����ӵĹ����м�¼һ��32bit��hashֵ�����ȫ��Ϊ1�����֦��
    ע�⣬��Ϊ����ֵ���Ϊ10^9�η�������0x3FFFFFFF�����������Ļ�ֵ������Ѿ�������ֵ����û��Ҫ������ѭ��j��
*/
int subarrayBitwiseORs(int* A, int ASize)
{
    int ret;
    HashHead head = NULL;
    //int hash[32];
    //int bitCnt = 0;
    for (int i = 0; i < ASize; i++) {
        int key = 0;
        for (int j = i; j < ASize; j++) {
            key |= A[j];
            add_user_exist(&head, key, 1);
            if (key == 0xFFFFFFFF) {
                break;
            }
        }
    }
    ret = count_user(head);
    return ret;
}

/*
    ����3��1��n^2�ټ��� hash��ʱ�ˣ� ʵ�ʽ������ʱ 80/83
    ��ʱ˼�����ܷ��ټ�֦�����߼��仯��  ���key�Ѿ����ˣ����ǲ���Ҫ++�����ԾͶ���
    ��󣺽����Ƕ����һ��case�����ǳ������ڴ����ƣ�˵��˵hash�Ѿ�ֵ̫���ˣ�û�취��ʹ��hash�����ˡ�ֻ�ܿ���ʹ�������㷨��
*/
int subarrayBitwiseORs(int* A, int ASize)
{
    // int *sum = (int *)malloc(sizeof(int) * (ASize + 1));
    // sum[0] = 0;
    // for (int i = 1; i <= ASize; i++) {
    //     sum[i] |= sum[i - 1] | A[i - 1];
    // }
    int ret;
    HashHead head = NULL;
    HashHead curHead = NULL;
    int hCnt = 0;
    //int hash[32];
    //int bitCnt = 0;
    for (int i = 0; i < ASize; i++) {
        int key = A[i];
        add_user_exist(&head, key, 1);
        HashHead nextHead = NULL;
        add_user_exist(&nextHead, key, 1);
        HashNode *s, *tmp;
        HASH_ITER(hh, curHead, s, tmp) {
            //printf("user id %d: value is %d\n", s->id, s->value);
            int v = key | s->id;
            if (v > key) {
                add_user_exist(&nextHead, v, 1);
            }
            key = v;
            add_user_exist(&head, v, 1);            
        }
        curHead = nextHead;
        // for (int j = 0; j < i; j++) {
        //     key |= A[j];
        //     if(!find_user(head, key)) {
        //         HashNode *node = (HashNode *)malloc(sizeof(HashNode));
        //         node->id = key;
        //         node->value = 1;
        //         HASH_ADD_INT(head, id, node);
        //     }
        //     //add_user_exist(&head, key, 1);
        //     if (key == 0x3FFFFFFF) {
        //         break;
        //     }
        // }
    }
    ret = count_user(head);
    return ret;
}

void main()
{
    int ret;
    ret = subarrayBitwiseORs(4);
    printf("ret = %d\n", ret);
    return;
}