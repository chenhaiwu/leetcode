// 给定一个单链表 L 的头节点 head ，单链表 L 表示为：
// L0 → L1 → … → Ln - 1 → Ln
// 请将其重新排列后变为：
// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
// 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。


// 示例 1
// 输入head = [1,2,3,4]
// 输出：[1,4,2,3]

// 示例 2
// 输入head = [1,2,3,4,5]
// 输出：[1,5,2,4,3]

// 提示：
// 链表的长度范围为 [1, 5 * 104]
// 1 <= node.val <= 1000

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


// 方法一：方法一：线性表
// 因为链表不支持下标访问，所以我们无法随机访问链表中任意位置的元素。
// 因此比较容易想到的一个方法是，我们利用线性表存储该链表，然后利用线性表可以下标访问的特点，直接按顺序访问指定元素，重建该链表即可
// 注意：放到vector里面的是链表指针，然后修改指针next的指向。
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// class Solution {
// public:
//     void reorderList(ListNode* head) {
//         if (head == nullptr)
//             return;
        
//         vector<ListNode *>veclist;
//         ListNode* p = head;
//         while (p != nullptr) {
//             veclist.emplace_back(p);
//             p = p->next;
//         }

//         // swap i, j; i = 0 & n - 1;
//         int i = 0, j = veclist.size() - 1;
//         while (i < j) {
//             veclist[i]->next = veclist[j];
//             i++;
//             if (i == j) break;
//             veclist[j]->next = veclist[i];
//             j--;
//         }
//         veclist[i]->next = nullptr;
//     }
// };


// 方法二：线性表
// 注意这里，其实是把链表的后半部，拿出来反序，然后前后半部，按每个链表各取一个结点重组。
// 1：利用快慢指针：先查找链表的中间结点指针位置
// 2: 从中间位置的后面一个开始，当作第二个链表的头，把第二个链表反序
// 3：重组链表1，链表2
/**
 * Definition for singly-linked list.
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr)
            return;
        ListNode* middle = middleNode(head);
        ListNode* pHead2 = middle->next;
        middle->next = nullptr;
        pHead2 = reverseList(pHead2);
        mergeList(head, pHead2);
    }

    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;

        ListNode* pPre = nullptr;
        ListNode* pCur = head;

        while (pCur != nullptr) {
            ListNode* pTmp = pCur->next;
            pCur->next = pPre;
            pPre = pCur;
            pCur = pTmp;
        }


        return pPre;
    }

    void mergeList(ListNode* head1, ListNode* head2) {
        ListNode* l1 = head1;
        ListNode* l2 = head2;
        ListNode* pTmp1 = nullptr;
        ListNode* pTmp2 = nullptr;

        while (l1 != nullptr && l2 != nullptr) {
            pTmp1 = l1->next;
            pTmp2 = l2->next;

            l1->next = l2;
            l2->next = pTmp1;
            l1 = pTmp1;
            l2 = pTmp2;
        }
    }
};

int main()
{
    Solution obj;
    ListNode n1(1);
    ListNode n2(2, &n1);
    ListNode n3(3, &n2);
    ListNode n4(4, &n3);
    ListNode n5(5, &n4);

    obj.reorderList(&n5);
    system("pause");
    return 0;
}




// 链表常用操作方法【查找中点、反转、合并】
// 找到原链表的中点(参考「876. 链表的中间结点」）。

// 我们可以使用快慢指针来 地找到链表的中间节点。
// 我们可以使用迭代法实现链表的反转。
// 将原链表的右半端反转 (参考「206. 反转链表」）。

// 将原链表的两端合并。
// 因为两链表长度相差不超过1, 因此直接合并即可。