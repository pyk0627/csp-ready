class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> cache(nums.size(),-1);
        auto dfs=[&](this auto&& dfs,int i)->int
        {
            if(i<0)
            {
                return 0;
            }
            if(cache[i]!=-1)
            {
                return cache[i];
            }
            int res=max(dfs(i-1),dfs(i-2)+nums[i]);
            cache[i]=res;
            return res;
        };
        return dfs(nums.size()-1);
    }
};