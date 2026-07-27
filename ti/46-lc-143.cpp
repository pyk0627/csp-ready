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
    void reorderList(ListNode* head) {
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast!=nullptr && fast->next !=nullptr)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode* mid=slow;

        ListNode* pre=nullptr;
        ListNode* cur=mid;
        while(cur!=nullptr)
        {
            ListNode* nxt=cur->next;
            cur->next=pre;
            pre=cur;
            cur=nxt;
        }

        ListNode* head2 = pre;
        ListNode* ans=head;
        while(head2->next !=nullptr)
        {
            ListNode* nxt1=head->next;
            ListNode* nxt2=head2->next;

            head->next=head2;
            head2->next=nxt1;

            head=nxt1;
            head2=nxt2;
        }
    }
};