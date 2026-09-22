/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    vector<int> num;
    void dfs(TreeNode* root)
    {
        if(root==nullptr)
        {
            return;
        }
        dfs(root->left);
        num.push_back(root->val);
        dfs(root->right);
    }
public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        vector<vector<int>> res;
        dfs(root);
        int ans1=-1;
        int ans2=-1;
        for(int i=0;i<queries.size();i++)
        {
            ans1=-1;
            ans2=-1;
            auto it=lower_bound(num.begin(),num.end(),queries[i]+1);
            if(it!=num.begin())
            {
                ans1=*(it-1);
            }
            it=lower_bound(num.begin(),num.end(),queries[i]);
            if(it!=num.end())
            {
                ans2=*it;
            }
            res.push_back({ans1,ans2});
        }
        return res;
    }
};