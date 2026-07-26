class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int l1len=0;
        int l2len=0;
        ListNode* pre=nullptr;
        ListNode* cur=l1;
        while(cur!=nullptr)
        {
            l1len++;
            ListNode* nxt=cur->next;
            cur->next=pre;
            pre=cur;
            cur=nxt;
        }
        ListNode* ll1=pre;

        pre=nullptr;
        cur=l2;
        while(cur!=nullptr)
        {
            l2len++;
            ListNode* nxt=cur->next;
            cur->next=pre;
            pre=cur;
            cur=nxt;
        }

        ListNode* ll2=pre;

        if(l2len>l1len)
        {
            ListNode* temp=ll1;
            ll1=ll2;
            ll2=temp;
        }

        int carry=0;

        ListNode* resultHead=ll1;
        ListNode* p1=ll1;
        ListNode* p2=ll2;
        while(p1 != nullptr)
        {
            int num=p1->val+carry;
            if(p2!=nullptr)
            {
                num+=p2->val;
                p2=p2->next;
            }

            p1->val=num % 10;
            carry=num/10;
            p1=p1->next;
        }
        pre=nullptr;
        cur=resultHead;
        while(cur!=nullptr)
        {
            ListNode* nxt=cur->next;
            cur->next=pre;
            pre=cur;
            cur=nxt;
        }

        if(carry!=0)
        {
            ListNode* ans=new ListNode(carry);
            ans->next=pre;
            return ans;
        }
        return pre;
    }
};