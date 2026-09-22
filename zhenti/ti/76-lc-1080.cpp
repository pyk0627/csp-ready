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
    int dfs2(TreeNode* root)
    {
        if(root==nullptr)
        {
            return 0;
        }
        if(root->right==nullptr)
        {
            return root->val+dfs2(root->left);
        }
        if(root->left==nullptr)
        {
            return root->val+dfs2(root->right);
        }
        if(root->left==nullptr&&root->right==nullptr)
        {
            return root->val;
        }
        return root->val+max(dfs2(root->left),dfs2(root->right));
    }
    void dfs1(TreeNode* root,int sum=0,int limit=0)
    {
        if(root==nullptr)
        {
            return;
        }
        sum+=root->val;
        if(sum+dfs2(root->left)<limit)
        {
            root->left=nullptr;
        }
        if(sum+dfs2(root->right)<limit)
        {
            root->right=nullptr;
        }
        dfs1(root->left,sum,limit);
        dfs1(root->right,sum,limit);
    }
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        TreeNode* dummy=new TreeNode(0);
        dummy->left=root;
        dfs1(dummy,0,limit);
        return dummy->left;
    }
};