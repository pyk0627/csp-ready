class Solution
{
public:
    int minInsertions(strin s)
    {
        int n=s.size();
        vector<int> dp(n);
        for(int i=n-1;i>=0;i--)
        {
            //注意：等于0
            int pre=0;
            for(int j=0;j<n;j++)
            {
                //因为下一轮要用，所以保存dp[j]
                //就是下一轮的dp[j-1]
                int temp=dp[j];
                //将二维转为一维的话，尽量删除continue
                if(i>j) {}
                else if(i==j)
                {
                    do[j]=1;
                }else if(s[i]==s[j])
                {
                    dp[j]=pre+2;
                }else 
                {
                    dp[j]=min(dp[j-1]+2,dp[j]+2);
                } 
                pre=temp;
            }
        }
        return dp[n-1]-n;
    }
}
