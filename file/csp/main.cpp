#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findMin(vector<int>& nums) {
        int idxmax = ranges::max_element(nums)-nums.begin();
        if(idxmax==nums.size()-1 && nums[0]==nums[idxmax])
        {
            idxmax=0;
        }
        while(idxmax<nums.size()-1 && nums[idxmax+1]==nums[idxmax])
        {
            idxmax++;
        }
        if(idxmax==nums.size()-1)
        {
            return nums[0];
        }else
        {
            return nums[idxmax+1];
        }
    }
};
int main()
{
    Solution sol;
    vector<int> nums={2,2,2,0,1};
    cout<<sol.findMin(nums)<<endl;
    return 0;
}
