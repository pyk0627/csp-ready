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
    TreeNode* ans=nullptr;
    void d(TreeNode* root,int val)
    {
        if(root==nullptr)
        {
            return;
        }
        if(root->val==val)
        {
            ans=root;
            return;
        }else if(root->val<val)
        {
            d(root->right,val);
        }else if(root->val>val)
        {
            d(root->left,val);
        }
    }
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        d(root,val);
        return ans;
    }
};