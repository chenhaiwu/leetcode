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
void print_user(HashHead head) {
    HashNode *s;
    printf("size is %d\n", count_user(head));
    for (s = head; s != NULL; s = s->hh.next) {
        printf("user id %d, value %d\n", s->id, s->value);
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

// if exit then update the value, else create a new node and return -1;
int add_user_exist(HashHead *head, int id, int val) {
    HashNode *node = find_user(*head, id);
    if(node != NULL) {
        return node->value;
    } else {
        node = (HashNode *)malloc(sizeof(HashNode));
        node->id = id;
        node->value = val;
        HASH_ADD_INT(*head, id, node);
        return -1;
    }
}

#define STR_MAX_LEN 1024
char *fractionToDecimal(int numerator, int denominator)
{
    HashHead head = NULL;
    char *buf = (char *)malloc(STR_MAX_LEN);
    int pos;
    long num = numerator;
    long demo = denominator;
    num = labs(num);
    demo = labs(demo);
    if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0)) {
        sprintf(buf, "-%ld", num / demo);
    } else {
        sprintf(buf, "%ld", num / demo);
    }
    num = num % demo;
    pos = strlen(buf);
    if (num != 0) {
        buf[pos++] = '.';
        int start_idx = -1;
        while (num != 0) {
            start_idx = add_user_exist(&head, num, pos);
            //printf("id=%d, num=%d, pos=%d\n", start_idx, num, pos);
            //print_user(head);
            if (start_idx != -1) {
                break;
            }
            buf[pos++] = (num * 10) / demo + '0';
            //printf("%c\n", buf[pos-1]);
            num = (num * 10) % demo;
        }
        if (start_idx != -1) {
            for (int i = pos++; i > start_idx; i--) {
                buf[i] = buf[i - 1];
            }
            buf[start_idx] = '(';
            buf[pos++] = ')';
        }
    }
    buf[pos] = '\0';
    return buf;
}