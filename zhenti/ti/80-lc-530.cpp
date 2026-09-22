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
    int ans=INT_MAX;
    TreeNode* pre=nullptr;
    void dfs(TreeNode* root)
    {
        if(root==nullptr)
        {
            return;
        }
        dfs(root->left);
        if(pre!=nullptr)
        {
            ans=min(ans,abs(root->val-pre->val));
        }
        pre=root;
        dfs(root->right);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        dfs(root);
        return ans;       
    }
};