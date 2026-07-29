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
    bool d(TreeNode* root,int num)
    { 
        if(root==nullptr)
        {
            return true;
        }
        if(root->val == num)
        {
            return d(root->left,num)&&d(root->right,num);
        }else
        {
            return false;
        }
    }
public:
    bool isUnivalTree(TreeNode* root) {
        if(root!=nullptr)
        {
            return d(root,root->val);
        }else
        {
            return true;
        }
    }
};