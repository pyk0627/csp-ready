class Solution
{
public:
    bool isInterleave(string s1,string s2,string s3)
    {
        int n=s1.size();
        int m=s2.size();
        if(n+m!=s3.size())
            return false;
        vector<int> dp(m+1);
        dp[0]=1;//如果s1，s2的长度都为0，则说明可以组成s3
        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=m;j++)
            {
                if(i==0&&j==0)//i=0,j=0,时k=0，无法比较，所以跳过
                    continue;
                int k=i+j;
                if(i>0&&s1[i-1]==s3[k-1]&&dp[j])
                {
                    dp[j]=1;
                }else if(j>0&&s2[j-1]==s3[k-1]&&dp[j-1])
                {
                    dp[j]=1;
                }else
                {
                    dp[j]=0;
                    //当我在处理第j行时，dp[j]保留的是第j-1行的数据，如果以上两种情况都不符合
                    //不置0的话则保留的是上一行的数据，这样是错误的
                    //如果是之前的二维数组，因为每个地方只用一次，所以一开始全部初始化为0，这是没问题的
                    //但因为这是一维的，所以每一行处理的过程中都要及时更新
                }
            }
        }
        return dp[m];
    }
};