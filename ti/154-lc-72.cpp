class Solution {
public:
    int minDistance(string word1, string word2) {
        int n=word1.size();
        int m=word2.size();

        vector<vector<int>> dp(n+1,vector<int>(m+1));
        for(int j=0;j<=m;j++)
        {
            dp[0][j]=j;
        }
        for(int i=0;i<=n;i++)
        {
            dp[i][0]=i;
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(word1[i]==word2[j])
                {
                    dp[i+1][j+1]=dp[i][j];
                }else
                {
                    dp[i+1][j+1]=min({dp[i+1][j],dp[i][j+1],dp[i][j]})+1;
                }
            }
        }
        return dp[n][m];
        // vector<vector<int>> memo(n+1,vector<int>(m+1,-1));
        // auto dfs=[&](this auto&& dfs,int i,int j)->int
        // {
        //     if(i<0)
        //     {
        //         return j+1;
        //     }
        //     if(j<0)
        //     {
        //         return i+1;
        //     }
        //     if(memo[i][j]!=-1)
        //     {
        //         return memo[i][j];
        //     }
        //     if(word1[i]==word2[j])
        //     {
        //         return memo[i][j]=dfs(i-1,j-1);
        //     }else
        //     {
        //         return memo[i][j]=min({dfs(i,j-1),dfs(i-1,j),dfs(i-1,j-1)})+1;
        //     }
        // };
        // return dfs(n-1,m-1);
    }
};