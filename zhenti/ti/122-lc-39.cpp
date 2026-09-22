class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> path;

        // vector<int> hou(candidates.size());
        // for(int i=candidates.size()-1;i>=0;i--)
        // {
        //     if(i==candidates.size()-1)
        //     {
        //         hou[i]=candidates[i];
        //     }else
        //     {
        //         hou[i]=candidates[i]+hou[i+1];
        //     }
        // }
        auto dfs=[&](this auto&& dfs,int i,int left_sum)->void
        {
            // if(hou[i]<left_sum)
            // {
            //     return;
            // }
            if(left_sum<0)
            {
                return;
            }
            if(left_sum==0)
            {
                ans.emplace_back(path);
                return;
            }

            for(int j=i;j<candidates.size();j++)
            {
                path.push_back(candidates[j]);
                dfs(j,left_sum-candidates[j]);
                path.pop_back();
            }
        };

        dfs(0,target);
        return ans;
    }
};