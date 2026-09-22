class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs=[&](this auto&& dfs,int n,int left_sum)->void
        {
            int d=k-path.size();

            if(left_sum<0 || left_sum>(n*2+n-d+1)*d/2)
            {
                return;
            }

            if(d==0)
            {
                ans.emplace_back(path);
                return;
            }


            if(n>d)
            {
                dfs(n-1,left_sum);
            }

            path.push_back(n);
            dfs(n-1,left_sum-n);
            path.pop_back();
        };

        dfs(9,n);
        return ans;
    }
};