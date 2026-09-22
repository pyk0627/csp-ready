class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n=text1.size();
        int m=text2.size();
        vector<vector<int>> memo(n,vector<int>(m,-1));
        auto dfs=[&](this auto&& dfs,int i,int j)->int
        {
            if(i<0||j<0)
            {
                return 0;
            }
            if(memo[i][j]!=-1)
            {
                return memo[i][j];
            }
            if(text1[i]==text2[j])
            {
                return memo[i][j]=dfs(i-1,j-1)+1;
            }else
            {
                return memo[i][j]=max(dfs(i-1,j),dfs(i,j-1));
            }
        };
        return dfs(n-1,m-1);
    }
};