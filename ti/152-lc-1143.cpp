class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n=text1.size();
        int m=text2.size();
        auto dfs=[&](this auto&& dfs,int i,int j)->int
        {
            if(i<0||j<0)
            {
                return 0;
            }
            if(text1[i]==text2[j])
            {
                return dfs(i-1,j-1)+1;
            }else
            {
                return max(dfs(i-1,j),dfs(i,j-1));
            }
        };
        return dfs(n-1,m-1);
    }
};