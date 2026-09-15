class Solution {
public:
    int minInsertions(string s) {
        int n=s.size();
        vector<vector<int>> dp(n,vector<int>(n));
        for(int i=n-1;i>=0;i--)
        {
            for(int j=0;j<n;j++)
            {
                if(i>j)
                {
                    continue;
                }else if(i==j)
                {
                    dp[i][j]=1;
                }else  if(s[i]==s[j])
                {
                    dp[i][j]=dp[i+1][j-1]+2;
                }else
                {
                    dp[i][j]=min(dp[i][j-1]+2,dp[i+1][j]+2);
                }
            }
        }
        return dp[0][n-1]-n;
        // vector<vector<int>> memo(n,vector<int>(n,-1));
        // auto dfs=[&](this auto&& dfs,int i,int j)->int
        // {
        //     if(memo[i][j]!=-1){return memo[i][j];}
        //     if(i>j){return memo[i][j]=0;}
        //     if(i==j){return memo[i][j]=1;}

        //     if(s[i]==s[j])
        //     {
        //         return memo[i][j]=dfs(i+1,j-1)+2;
        //     }else
        //     {
        //         return memo[i][j]=min(dfs(i,j-1)+2,dfs(i+1,j)+2);
        //     }
        // };
        // return dfs(0,n-1)-n;
    }
};
