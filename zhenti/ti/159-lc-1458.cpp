class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        int m=nums2.size();
        vector<vector<int>> memo(n+1,vector<int>(m+1,INT_MIN));
        const int NEG=-1e6;
        auto dfs=[&](this auto&& dfs,int i,int j)->int
        {
            if(i==0||j==0)
                return NEG;
            if(memo[i][j]!=INT_MIN)
                return memo[i][j];
            int p=nums1[i-1]*nums2[j-1];
            return memo[i][j]=max({dfs(i-1,j),
                                    dfs(i,j-1),
                                    dfs(i-1,j-1)+p,
                                    p});
        };
        return dfs(n,m);
    }
};