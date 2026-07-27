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
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* pa=list1;
        for(int i=0;i<a-1;i++)
        {
            pa=pa->next;
        }
        ListNode* pb=list1;
        for(int i=0;i<b+1;i++)
        {
            pb=pb->next;
        }
        pa->next=list2;
        ListNode* lst2end=list2;
        while(lst2end->next !=nullptr)
        {
            lst2end=lst2end->next;
        }
        lst2end->next=pb;
        return list1;
    }
};