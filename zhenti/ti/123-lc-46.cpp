class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<bool> on_path(nums.size(),false);
        vector<int> path;
        auto dfs=[&](this auto&& dfs,int i)->void
        {
            if(i==nums.size())
            {
                ans.emplace_back(path);
                return;
            }
            for(int j=0;j<nums.size();j++)
            {
                if(on_path[j]==false)
                {
                    path.push_back(nums[j]);
                    on_path[j]=true;
                    dfs(i+1);
                    path.pop_back();
                    on_path[j]=false;
                }
            }
        };
        dfs(0);
        return ans;
    }
};