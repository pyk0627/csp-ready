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
    ListNode* removeNodes(ListNode* head) {
        ListNode* head2 = reserve(head);
        int num=head2->val;
        ListNode* cur=head2;
        while(cur->next !=nullptr)
        {
            if(cur->next->val <num)
            {
                cur->next=cur->next->next;
            }else if(cur->next->val > num)
            {
                num=cur->next->val;
                cur=cur->next;
            }else
            {
                cur=cur->next;
            }
        }
        return reserve(head2);
    }
};