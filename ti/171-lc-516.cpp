class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n=s.size();
        vector<int> dp(n);
        for(int i=n-1;i>=0;i--)
        {
            dp[i]=1;
            int pre=0;
            for(int j=i+1;j<n;j++)
            {
                int temp=dp[j];
                if(s[i]==s[j])
                {
                    dp[j]=pre+2;
                }else
                {
                    //这里的dp[j]是旧值，等价与dp[i+1][j]
                    //这里的dp[j-1]是新值,等价与dp[i][j-1],因为这是在j这个循环中，刚刚才更新的值
                    dp[j]=max(dp[j],dp[j-1]);
                }
                pre=temp;
            }
        }
        return dp[n-1];
        // vector<vector<int>> dp(n,vector<int>(n));
        // for(int i=n-1;i>=0;i--)
        // {
        //     dp[i][i]=1;
        //     for(int j=i+1;j<n;j++)
        //     {
        //         if(s[i]==s[j])
        //         {
        //             dp[i][j]=dp[i+1][j-1]+2;
        //         }else
        //         {
        //             //对于i，需要i+1，则i需要从大到小遍历
        //             dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
        //         }
        //     }
        // }
        // return dp[0][n-1];
        // auto dfs=[&](this auto&& dfs,int i,int j)
        // {
        //     if(memo[i][j]!=-1)
        //     {
        //         return memo[i][j];
        //     }
        //     if(i>j)
        //     {
        //         return memo[i][j]=0;
        //     }
        //     if(i==j)
        //     {
        //         return memo[i][j]=1;
        //     }
        //     if(s[i]==s[j])
        //     {
        //         return memo[i][j]=dfs(i+1,j-1)+2;
        //     }
        //     return memo[i][j]=max(dfs(i+1,j),dfs(i,j-1));
        // };
        // return dfs(0,n-1);
    }
};