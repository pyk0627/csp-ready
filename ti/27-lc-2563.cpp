class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(),nums.end());
        long long ans=0;
        for(int i=0;i<nums.size();i++)
        {
            //nums[i] + nums[j] > = lower
            int l = ranges::lower_bound(nums.begin()+i+1,nums.end(),lower-nums[i])-nums.begin();
            int r = ranges::upper_bound(nums.begin()+i+1,nums.end(),upper-nums[i])-nums.begin();
            ans+=r-l;
        }
        return ans;
    }
};
//lower_bound函数的使用：
/*
1.
    int l = ranges::lower_bound(nums.begin()+i+1,nums.end(),lower-nums[i])-nums.begin();
2.
    int l = ranges::lower_bound(nums,lower-nums[i])-nums.begin();
*/
//因为函数返回的是一个迭代器所以要减去begin来得到一个int值