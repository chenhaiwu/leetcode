#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    if (!l1) {
        return l2;
    }
    if (!l2) {
        return l1;
    }
    struct ListNode * head = NULL;
    struct ListNode * pNext = NULL;
    if (l1->val < l2->val) {
        head = l1;
        l1 = l1->next;
    } else {
        head = l2;
        l2 = l2->next;
    }
    pNext = head;
    while (l1 != NULL || l2 != NULL) {
        if (l1 == NULL) {
            pNext->next = l2;
            break;
        }
        if (l2 == NULL) {
            pNext->next = l1;
            break;
        }
        if (l1->val < l2->val) {
            pNext->next = l1;
            pNext = pNext->next;
            l1 = l1->next;
        } else {
            pNext->next = l2;
            pNext = pNext->next;
            l2 = l2->next;
        }
    }
    return head;
}