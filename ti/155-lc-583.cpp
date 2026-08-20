class Solution {
public:
    int minDistance(string word1, string word2) {
        int n=word1.size();
        int m=word2.size();
        vector<int> dp(m+1);
        // vector<vector<int>> dp(n+1,vector<int>(m+1));
        for(int j=0;j<m;j++)//初始化第0行，word1为空串的时候
        {
            dp[j]=j;
        }
        // for(int i=0;i<n;i++)
        // {
        //     dp[i+1][0]=i+1;
        // }
        for(int i=0;i<n;i++)
        {
            int pre=dp[0];//取出上一行的dp[0]
            dp[0]=i+1;//将这一行的dp[0]，依据相应的i进行初始化
            for(int j=0;j<m;j++)
            {
                int temp=dp[j+1];//当前的旧值就在下一个新值的左上角
                if(word1[i]==word2[j])
                {
                    dp[j+1]=pre;
                }else
                {
                    dp[j+1]=min(dp[j+1],dp[j])+1;
                }
                pre=temp;
            }
        }
        return dp[m];
        // auto dfs=[&](this auto && dfs,int i,int j)->int
        // {
        //     if(i<0)
        //     {
        //         return j+1;
        //     }
        //     if(j<0)
        //     {
        //         return i+1;
        //     }
        //     if(word1[i]==word2[j])
        //     {
        //         return memo[i][j]=dfs(i-1,j-1);
        //     }else
        //     {
        //         return memo[i][j]=min(dfs(i,j-1),dfs(i-1,j))+1;
        //     }
        // };
        // return dfs(n-1,m-1);
    }
};