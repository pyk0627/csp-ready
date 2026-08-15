class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n=coins.size();
        vector memo(n+1,vector<int>(amount+1,INT_MAX/2));
        memo[0][0]=0;//是0是1还要看题意
        for(int i=0;i<n;i++)//是<n，不是<=n,由递归复刻而来
        {
            for(int c=0;c<=amount;c++)
            {
                if(c<coins[i])
                {
                    memo[i+1][c]=memo[i][c];
                }else
                {
                    memo[i+1][c]=min(memo[i][c],memo[i+1][c-coins[i]]+1);
                }
            }
        }
        int ans=memo[n][amount];
        return ans<INT_MAX/2?ans:-1;
    }
};