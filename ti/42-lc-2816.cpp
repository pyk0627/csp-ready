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
    ListNode* doubleIt(ListNode* head) {
        ListNode* pre=reserve(head);
        ListNode* hh =pre;
        int carry=0;
        while(pre!=nullptr)
        {
            //cout<<pre->val<<endl;
            //cout<<carry<<endl;
            int num=(pre->val) * 2+carry;
            //cout<<num<<endl;
            carry = num / 10;
            num=num%10;
            //cout<<carry<<endl;
            //cout<<num<<endl;
            pre->val=num;
            pre=pre->next;
        }
        if(carry!=0)
        {
            ListNode* h=new ListNode(carry);
            h->next = reserve(hh);
            return h;
        }else
        {
            return reserve(hh);
        }
    }
};