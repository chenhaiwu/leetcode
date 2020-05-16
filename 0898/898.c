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
   方法1：使用每一个数的i - > j 的或的值作key，插入到hash中，如果不存在则值为1，存在则+1，
   for (i : 0->len) {
     key = 0;
     for (j: i, -> len) {
       key |= A[j];
       AddHash(key, value: 1)
     }
   }
   注意点：算法复杂度为n^2, hash没有办法使用一个INT数组，因为值10^9，太大
   1 <= A.length <= 50000
   0 <= A[i] <= 10^9
    实际结果，超时 72/83
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
    方法2：1中n^2再加上 hash超时了， 考虑减枝， 实际结果，超时 80/83
    这时思考，能否减枝，或者记忆化。
    减枝：如果所有的位组合都出现了，就不需要了，则需要在每次i循环中，j在增加的过程中记录一个32bit的hash值，如果全部为1，则减枝。
    注意，因为给的值最大为10^9次方，则是0x3FFFFFFF，可能是最大的或值，如果已经是最大或值，则没必要再往下循环j了
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
    方法3：1中n^2再加上 hash超时了， 实际结果，超时 80/83
    这时思考，能否再减枝，或者记忆化。  如果key已经在了，我们不需要++，所以就丢掉
    最后：结论是多过了一个case，但是超过了内存限制，说明说hash已经值太多了，没办法再使用hash来存了。只能考虑使用其它算法了
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