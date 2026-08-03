class Solution {
    vector<int> nums;
    vector<vector<int>> ans;
    vector<int> temp;
    void dfs(int depth)
    {
        if(depth==nums.size())
        {
            ans.push_back(temp);
            return;
        }
        dfs(depth+1);

        temp.push_back(nums[depth]);
        dfs(depth+1);
        temp.pop_back();
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        this->nums=nums;
        dfs(0);
        return ans;
    }
};