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
    }
};
