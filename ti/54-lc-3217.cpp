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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> st(nums.begin(),nums.end());
        ListNode* dummy = new ListNode(0,head);
        ListNode* cur=dummy;
        while(cur->next != nullptr)
        {
        //     int f=0;
        //     for(int i=0;i<nums.size();i++)
        //     {
        //         if(nums[i]==cur->next->val)
        //         {
        //             f=1;
        //             break;
        //         }
        //     }
            if(st.contains(cur->next->val))
            {
                cur->next=cur->next->next;
                
            }else
            {
                cur=cur->next;   
            }
        }
        return dummy->next;
    }
};