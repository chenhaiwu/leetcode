
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

int add_user_exist(HashHead *head, int id, int val)
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

bool CheckHashRight(HashHead headSrc, int *nums, int numsSize)
{
    int srcCnt = count_user(headSrc);
    if (srcCnt == 1) {
        return true;
    }
    bool ret = false;
    HashHead headTmp = NULL;
    HashNode *s, *tmp;
    HASH_ITER(hh, headSrc, s, tmp)
    {
        add_user_exist(&headTmp, s->value, 1);
        if (count_user(headTmp) > 2) {
            return ret;
        }
        // printf("count headtmp=%d\n", count_user(headTmp));
        // print_user(headTmp);
    }

    int id1;
    int id2;
    int num1;
    int num2;
    int i = 0;
    HASH_ITER(hh, headTmp, s, tmp)
    {
        if (i == 0) {
            id1 = s->id;
            num1 = s->value;
            i++;
        } else {
            id2 = s->id;
            num2 = s->value;
            i++;
        }
    }
    int tmp3;
    if (num1 == 1) {
        if (id1 == 1 || id1 - id2 == 1) {
            return true;
        }
    }
    if (num2 == 1) {
        if (id2 == 1 || id2 - id1 == 1) {
            return true;
        }
    }
    return false;
}

int maxEqualFreq(int *nums, int numsSize)
{
    HashHead head1 = NULL;
    /* 所有元素入hash表, id为元素的nums[i]，value为元素个数 */
    for (int i = 0; i < numsSize; i++) {
        add_user_exist(&head1, nums[i], 1);
    }
    for (int i = 0; i < numsSize; i++) {
        if (count_user(head1) == numsSize - i) {
            return numsSize - i;
        }
        bool ret = CheckHashRight(head1, nums, numsSize);
        if (ret) {
            return numsSize - i;
        }
        ModifyHash(&head1, nums[numsSize - 1 - i], 1);
    }
    return 0;
}