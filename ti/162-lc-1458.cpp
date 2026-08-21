class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        int m=nums2.size();
        vector<int> dp(m+1);
        for(int i=0;i<=n;i++)
        {
            int pre=dp[0];//这个好像可以背一下
            for(int j=0;j<=m;j++)
            {
                int temp=dp[j];//记录当前的作为下一个的pre
                if(i==0||j==0)
                {
                    dp[j]=-1e6;
                    continue;
                }
                int p=nums1[i-1]*nums2[j-1];
                dp[j]=max({dp[j],dp[j-1],
                            pre+p,p});
                pre=temp;
            }
        }
        return dp[m];
    }
};