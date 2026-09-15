class Solution {
public:
    int minInsertions(string s) {
        int n=s.size();
        vector<vector<int>> memo(n,vector<int>(n,-1));
        auto dfs=[&](this auto&& dfs,int i,int j)->int
        {
            if(memo[i][j]!=-1){return memo[i][j];}
            if(i>j){return memo[i][j]=0;}
            if(i==j){return memo[i][j]=1;}

            if(s[i]==s[j])
            {
                return memo[i][j]=dfs(i+1,j-1)+2;
            }else
            {
                return memo[i][j]=min(dfs(i,j-1)+2,dfs(i+1,j)+2);
            }
        };
        return dfs(0,n-1)-n;
    }
};
