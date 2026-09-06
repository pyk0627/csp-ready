class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        vector<pair<int,int>> nums;
        for(int i=0;i<scores.size();i++)
        {
            nums.push_back({ages[i],scores[i]});
        }           
        sort(nums.begin(),nums.end());

        //dp[i]表示以第i个球员结尾时的最大总分
        vector<int> dp(scores.size(),0);
        int ans=0;
        for(int i=0;i<nums.size();i++)
        {

            //初始化每个dp[i]，只能选自己
            dp[i]=nums[i].second;
            for(int j=0;j<i;j++)
            {

                //枚举之前的以第j个成员结尾的情况
                //如果第j个成员的成绩是小于当前成员的
                //则可以把当前成员加到它的结尾
                //这就是以当前成员结尾的情况
                if(nums[j].second<=nums[i].second)
                {
                    dp[i]=max(dp[i],dp[j]+nums[i].second);
                }
            }
            ans=max(ans,dp[i]);
        } 
        return ans;
    }
};