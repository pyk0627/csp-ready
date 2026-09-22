class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned long long> ans(target+1);
        ans[0]=1;
        for(int i=1;i<=target;i++)
        {
            for(auto& x:nums)
            {
                if(i-x>=0)
                {
                    ans[i]+=ans[i-x];
                }          
            }
        }
        return ans[target];
    }
};