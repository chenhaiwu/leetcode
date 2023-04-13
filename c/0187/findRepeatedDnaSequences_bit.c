#define MAX_ROW_NUM 1000
int g_charHash[26];

void SetCharHash()
{
    g_charHash['A' - 'A'] = 0;
    g_charHash['C' - 'A'] = 1;
    g_charHash['G' - 'A'] = 2;
    g_charHash['T' - 'A'] = 3;
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
    } else {
        return false;
    }
}

#define MASK_20BIT 0xFFFFF
char ** findRepeatedDnaSequences(char * s, int* returnSize)
{
    HashHead head = NULL;
    char **ret = (char **)malloc(sizeof(char *) * MAX_ROW_NUM);
    int retSize = 0;
    int len = strlen(s);
    int tmpValue = 0;
    SetCharHash();
    if (len < 10) {
        *returnSize = 0;
        return NULL;
    }
    for (int i = 0; i < 10; i++) {
        tmpValue = tmpValue << 0x2;
        tmpValue |= g_charHash[s[i] - 'A'];
    }
    //printf("%08x\n", tmpValue);
    add_user_exist(&head, tmpValue, 1);
    for (int i = 10; i < len; i++) {
        tmpValue = tmpValue << 0x2;
        tmpValue |= g_charHash[s[i] - 'A'];
        tmpValue &= MASK_20BIT;
        HashNode *node = find_user(head, tmpValue);
        if(node != NULL) {
            if (node->value == 1) {
                ret[retSize] = (char *)malloc(sizeof(char) * 11);
                memcpy(ret[retSize], s + i - 10 + 1, 10);
                ret[retSize][10] = '\0';
                retSize++;
            }
            node->value += 1;
        } else {
            node = (HashNode *)malloc(sizeof(HashNode));
            node->id = tmpValue;
            node->value = 1;
            HASH_ADD_INT(head, id, node);
        }
    }
    *returnSize = retSize;
    return ret;
}

void main()
{
    char *p = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    int len;
    int **ret = findRepeatedDnaSequences(p, &len);
    return;
}