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