class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1,INT_MAX);
        dp[0]=0;//和为0的完全平方数需要0个数
        for(int i=1;i<=n;i++)
        {
            int val=1;//枚举背包的物品，物品的价值为1，体积为i^2
            for(int j=1;j<=2;j++)
            {
                val*=i;
            }
            if(val>n)
            {
                break;
            }
            for(int c=val;c<=n;c++)
            {
                dp[c]=min(dp[c],dp[c-val]+1);
            }
        }
        return dp[n];
    }
};