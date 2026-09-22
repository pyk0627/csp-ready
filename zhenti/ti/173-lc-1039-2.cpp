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
                        res=min(res,dp[i][k]+
                                dp[k][j]+values[i]*
                                values[k]*values[j]);
                    }
                    dp[i][j]=res;
                }
            }
        }
        return dp[0][n-1];
    }
};
