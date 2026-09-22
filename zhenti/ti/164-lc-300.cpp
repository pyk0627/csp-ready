class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(),1);
        //每个单个的字符串就是一个递增序列，所以初始化为1
        for(int i=0;i<nums.size();i++)
        {
            int temp=1;
            for(int j=0;j<i;j++)
            {
                if(nums[j]<nums[i])
                {
                    temp=max(temp,dp[j]+1);
                }
            }
            dp[i]=temp;
        }
        return *max_element(dp.begin(),dp.end());
        // vector<int> memo(nums.size(),-1);
        // auto dfs=[&](this auto&& dfs,int i)->int
        // {
        //     if(memo[i]!=-1)
        //     {
        //         return memo[i];
        //     }
        //     int temp=1;
        //     for(int j=0;j<=i;j++)
        //     {
        //         if(nums[j]<nums[i])
        //         {
        //             temp=max(temp,dfs(j)+1);
        //         }
        //     }
        //     return memo[i]=temp;
        // };
        // int ans=0;
        // for(int a=0;a<nums.size();a++)
        // {
        //     ans=max(ans,dfs(a));
        // }
        // return ans;
    }
};