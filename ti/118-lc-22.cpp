class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string path(n*2,0);

        auto dfs=[&](this auto&& dfs,int left,int right)->void
        {
            if(right==n)
            {
                ans.emplace_back(path);
                return;
            }

            if(left<n)
            {
                path[left+right]='(';
                dfs(left+1,right);
            }

            if(right<left)
            {
                path[left+right]=')';
                dfs(left,right+1);
            }
        };

        dfs(0,0);
        return ans;
    }
};