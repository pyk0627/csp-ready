class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n=text1.size();
        int m=text2.size();

        // vector<int> dp(m+1);
        // for(int i=0;i<n;i++)
        // {
        //     int pre=dp[0];//用pre记录左上的状态
        //     for(int j=0;j<m;j++)
        //     {
        //         int temp=dp[j+1];//记录当前的状态作为下一个左上的状态
        //         dp[j+1]=text1[i]==text2[j]?pre+1:max(dp[j+1],dp[j]);
        //         pre=temp;//更新左上的状态
        //     }
        // }
        // return dp[m];
        vector<vector<int>> dp(n+1,vector<int>(m+1));
        dp[0][0]=0;
        //因为之前的递归是从底向上递归，利用了字串的结果，所以改成递推的时候
        //循环要从0到n-1
        for(int i=0;i<=n-1;i++)
        {
            for(int j=0;j<=m-1;j++)
            {
                //三目运算符dp[i+1][j+1]=text1[i]==text2[j]?dp[i][j]+1:max(dp[i][j+1],dp[i+1][j]);
                if(text1[i]==text2[j])
                {
                    dp[i+1][j+1]=dp[i][j]+1;
                }else
                {
                    dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
                }
            }
        }
        return dp[n][m];
        // vector<vector<int>> memo(n,vector<int>(m,-1));
        // auto dfs=[&](this auto&& dfs,int i,int j)->int
        // {
        //     if(i<0||j<0)
        //     {
        //         return 0;
        //     }
        //     if(memo[i][j]!=-1)
        //     {
        //         return memo[i][j];
        //     }
        //     if(text1[i]==text2[j])
        //     {
        //         return memo[i][j]=dfs(i-1,j-1)+1;
        //     }else
        //     {
        //         return memo[i][j]=max(dfs(i-1,j),dfs(i,j-1));
        //     }
        // };
        // return dfs(n-1,m-1);
    }
};