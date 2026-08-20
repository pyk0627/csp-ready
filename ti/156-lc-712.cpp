class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n=s1.size();
        int m=s2.size();

        // vector<vector<int>> memo(n,vector<int>(m,-1));
        vector<int> dp(m+1);
        for(int j=0;j<m;j++)
        {
            int res=0;
            for(int a=0;a<=j;a++)
            {
                res+=s2[a];
            }
            dp[j+1]=res;
        }
        for(int i=0;i<n;i++)
        {
            int pre=dp[0];
            int res=0;
            for(int a=0;a<=i;a++)
            {
                res+=s1[a];
            }
            dp[0]=res;
            for(int j=0;j<m;j++)
            {
                int temp=dp[j+1];
                if(s1[i]==s2[j])
                {
                    dp[j+1]=pre;
                }else
                {
                    dp[j+1]=min(dp[j]+s2[j],dp[j+1]+s1[i]);
                }
                pre=temp;
            }
        }
        return dp[m];
        // vector<vector<int>> dp(n+1,vector<int>(m+1));
        // for(int j=0;j<m;j++)
        // {
        //     int res=0;
        //     for(int a=0;a<=j;a++)
        //     {
        //         res+=s2[a];
        //     }
        //     dp[0][j+1]=res;
        // }
        // for(int i=0;i<n;i++)
        // {
        //     int res=0;
        //     for(int a=0;a<=i;a++)
        //     {
        //         res+=s1[a];
        //     }
        //     dp[i+1][0]=res;
        // }
        // for(int i=0;i<n;i++)
        // {
        //     for(int j=0;j<m;j++)
        //     {
        //         if(s1[i]==s2[j])
        //         {
        //             dp[i+1][j+1]=dp[i][j];
        //         }else
        //         {
        //             dp[i+1][j+1]=min(dp[i+1][j]+s2[j],dp[i][j+1]+s1[i]);
        //         }
        //     }
        // }
        // return dp[n][m];
        // auto dfs=[&](this auto&& dfs,int i,int j)->int
        // {
        //     int res=0;
        //     if(i<0)
        //     {

        //         for(int a=0;a<=j;a++)
        //         {
        //             res+=s2[a];
        //         }
        //         return res;
        //     }
        //     if(j<0)
        //     {
        //         for(int a=0;a<=i;a++)
        //         {
        //             res+=s1[a];
        //         }
        //         return res;
        //     }
        //     if(memo[i][j]!=-1)
        //     {
        //         return memo[i][j];
        //     }
        //     if(s1[i]==s2[j])
        //     {
        //         return memo[i][j]=dfs(i-1,j-1);
        //     }else
        //     {
        //         return memo[i][j]=min(dfs(i,j-1)+s2[j],dfs(i-1,j)+s1[i]);
        //     }
        // };
        // return dfs(n-1,m-1);
    }
};