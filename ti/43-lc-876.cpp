class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow=head;
        ListNode* fast=head;
        while(1)
        {
            // cout<<slow->val<<endl;
            // cout<<fast->val<<endl;
            //先判断fast是否为空指针，再判断fast->next是否为空指针
            //否则编译器会报错
            //因为可能会识别成，我对值为nullptr的指针访问它的next
            if(fast==nullptr ||fast->next==nullptr)
            {
                return slow;
            }
            slow=slow->next;
            fast=fast->next->next;
        }
    }
};
