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
public:
    bool isValidBST(TreeNode* root,long long left=LONG_MIN,long long right=LONG_MAX) {
        if(root==nullptr)
        {
            return true;
        } 
        return (root->val<right&&root->val>left) &&isValidBST(root->left,left,root->val)&&isValidBST(root->right,root->val,right);  
    }
};