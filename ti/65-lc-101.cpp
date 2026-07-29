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
    bool f(TreeNode* l,TreeNode* r)
    {
        if(l==nullptr||r==nullptr)
        {
            return l==r;
        }
        return l->val==r->val&&
               f(l->left,r->right)&&
               f(l->right,r->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        return f(root->left,root->right);
    }
};