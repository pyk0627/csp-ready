class Solution
{
public:
    bool isInterleave(string s1,string s2,string s3)
    {
        int n=s1.size();
        int m=s2.size();
        if(n+m!=s3.size())
        {
            return false;
        }
        vector<vector<int>> dp(n+1,vector<int>(m+1));
        dp[0][0]=1;//如果s1，s2的长度都为0，则说明可以组成s3
        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=m;j++)
            {
                if(i==0&&j==0)//i=0,j=0,时k=0，无法比较，所以跳过
                {
                    continue;
                }
                int k=i+j;
                if(i>0&&s1[i-1]==s3[k-1]&&dp[i-1][j])
                {
                    dp[i][j]=1;
                }else if(j>0&&s2[j-1]==s3[k-1]&&dp[i][j-1])
                {
                    dp[i][j]=1;
                }
            }
        }
        return dp[n][m];
    }
};