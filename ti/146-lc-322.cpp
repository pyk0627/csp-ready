class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n=coins.size();
        vector<int> memo(amount+1,INT_MAX/2);
        memo[0]=0;
        for(auto x:coins)
        {
            for(int c=x;c<=amount;c++)
            {
                memo[c]=min(memo[c],memo[c-x]+1);
            }
        }
        int ans=memo[amount];
        return ans<INT_MAX/2?ans:-1;
    }
};