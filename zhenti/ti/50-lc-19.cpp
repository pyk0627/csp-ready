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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0,head);
        ListNode* right=dummy;
        for(int i=0;i<n;i++)
        {
            right=right->next;
        }
        ListNode* left=dummy;
        while(right->next !=nullptr)
        {
            right=right->next;
            left=left->next;
        }
        left->next=left->next->next;
        if(dummy->next==nullptr)
        {
            return nullptr;
        }else
        {
            return dummy->next;
        }
    }
};