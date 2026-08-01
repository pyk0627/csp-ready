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
    int kthSmallest(TreeNode* root, int k) {
        dfs(root);
        return num[k-1];
    }
};