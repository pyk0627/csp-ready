class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dummy = new ListNode(0,head);
        ListNode* cur=dummy;
        while(cur->next != nullptr && cur->next->next!=nullptr )
        {
            //cout<<cur->next->val<<endl;
            //cout<<cur->next->next->val<<endl;
            if(cur->next->val == cur->next->next->val)
            {
                while(cur->next != nullptr &&cur->next->next != nullptr &&  cur->next->val == cur->next->next->val)
                {
                    //cout<<"---:"<<cur->val<<endl;
                    cur->next->next=cur->next->next->next;
                }
                cur->next=cur->next->next;
            }else
            {
                cur=cur->next;
            }
        }
        return dummy->next;
    }
};