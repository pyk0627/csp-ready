class Solution {
    vector<int> nums;
    vector<vector<int>> ans;
    vector<int> temp;
    void dfs(int depth)
    {
        ans.push_back(temp);
        if(depth==nums.size())
        {

            return;
        }
        for(int j=depth;j<nums.size();j++)
        {
            temp.push_back(nums[j]);
            dfs(j+1);
            temp.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        this->nums=nums;
        dfs(0);
        return ans;
    }
};