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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(0,head);
        ListNode* p0=&dummy;
        for(int i=0;i<left-1;i++)
        {
            p0=p0->next;
        }
        ListNode* pre=nullptr;
        ListNode* cur=p0->next;
        for(int i=0;i<right-left+1;i++)
        {
            ListNode* nxt=cur->next;
            cur->next=pre;
            pre=cur;
            cur=nxt;
        }
        p0->next->next=cur;
        p0->next=pre;
        return dummy.next;
    }
};
/*
因为 `dummy` 是对象，所以写：


dummy.next

如果 `dummy` 是指针，比如：

ListNode* dummy = new ListNode(0, head);

那就要写：

dummy->next


你这段代码里 `dummy` 不是指针，所以用的是：

dummy.next

*/