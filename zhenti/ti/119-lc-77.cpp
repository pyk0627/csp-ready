class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs=[&](this auto&& dfs,int i)->void
        {
            int d=k-path.size();
            if(d==0)
            {
                ans.emplace_back(path);
                return;
            }

            if(i>d)
            {
                dfs(i-1);
            }

            path.push_back(i);
            dfs(i-1);
            path.pop_back();
        };

        dfs(n);
        return ans;
    }
};