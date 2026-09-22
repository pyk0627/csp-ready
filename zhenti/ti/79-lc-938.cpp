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
    int ans=0;
    void dfs(TreeNode* root,int low,int high)
    {
        if(root==nullptr)
        {
            return;
        }
        if(low<=root->val&&root->val<=high)
        {
            ans+=root->val;
            dfs(root->left,low,high);
            dfs(root->right,low,high);
        }else if(root->val>high)
        {
            dfs(root->left,low,high);
        }else if(root->val<low)
        {
            dfs(root->right,low,high);
        }
    }
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        dfs(root,low,high);
        return ans;
    }
};