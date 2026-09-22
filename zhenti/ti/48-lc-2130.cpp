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
    ListNode* reserve(ListNode* head)
    {
        ListNode* pre=nullptr;
        ListNode* cur=head;
        while(cur!=nullptr)
        {
            ListNode* nxt=cur->next;
            cur->next=pre;
            pre=cur;
            cur=nxt;
        }
        return pre;
    }
public:
    int pairSum(ListNode* head) {
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast!=nullptr && fast->next !=nullptr)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode* mid=slow;
        ListNode* head2=reserve(mid);
        int ans=0;
        while(head!=nullptr && head2 !=nullptr)
        {
            ans=max(ans,head->val+head2->val);
            head=head->next;
            head2=head2->next;
        }
        return ans;
    }
};