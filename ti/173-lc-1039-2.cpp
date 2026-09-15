class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n=values.size();
        vector<vector<int>> dp(n,vector<int>(n));
        for(int i=n-3;i>=0;i--)
        {
            for(int j=0;j<=n-1;j++)
            {
                if(j==i+1)
                {
                    dp[i][j]=0;
                }else
                {
                    int res=INT_MAX;
                    for(int k=i+1;k<=j-1;k++)
                    {
                        res=min(res,dp[i][k]+dp[k][j]+values[i]*values[k]*values[j]);
                    }
                    dp[i][j]=res;
                }
            }
        }
        return dp[0][n-1];
        // vector<vector<int>> memo(n,vector<int>(n,-1));
        // auto dfs=[&](this auto&& dfs,int i,int j)
        // {
        //     if(memo[i][j]!=-1)
        //     {
        //         return memo[i][j];
        //     }
        //     if(j==i+1)
        //     {
        //         return memo[i][j]=0;
        //     }

        //     int res=INT_MAX;
        //     for(int k=i+1;k<=j-1;k++)
        //     {
        //         res=min(res,dfs(i,k)+dfs(k,j)+values[i]*values[k]*values[j]);
        //     }

        //     return memo[i][j]=res;
        // };
        // return dfs(0,n-1);
    }
};
