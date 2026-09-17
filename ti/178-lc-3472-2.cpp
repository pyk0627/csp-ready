class Solution
{
public:
    int longestPalindromicSubsequence(string s,int k)
    {
        int n=s.size();
        vector dp(n,vector(n,vector<int>(k+1)));
        for(int i=0;i<n;i++)
        {
            for(int c=0;c<=k;c++)
            {
                dp[i][i][c]=1;
            }
        }
        for(int i=n-1;i>=0;i--)
        {
            //之前j是从0开始遍历的
            //就是错的
            //尽量不要进行无效遍历
            //以免增添不必要的麻烦
            for(int j=i+1;j<=n-1;j++)
            {
                //之前让cnt从1开始遍历
                //就是错的
                //尽量让数组中的每一个都被填上正确的值
                for(int cnt=0;cnt<=k;cnt++)
                {
                    int res=0;
                        res=max(dp[i][j-1][cnt],
                                    dp[i+1][j][cnt]);
                    int d=abs(s[i]-s[j]);
                    int op=min(d,26-d);

                    if(op<=cnt)
                    {
                        res=max(res,dp[i+1][j-1][cnt-op]+2);
                        
                    }

                    dp[i][j][cnt]=res;
                }
            }
        }
        return dp[0][n-1][k];
    }
};


