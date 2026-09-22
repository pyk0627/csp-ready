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
    int maxdepth=0;
    vector<TreeNode*> node;
    void dfs(TreeNode* root,int depth)
    {
        if(root==nullptr)
        {
            return;
        }
        if(depth>maxdepth)
        {
            node.clear();
            node.push_back(root);
            maxdepth=depth;
        }else if(depth == maxdepth)
        {
            node.push_back(root);
        }
        dfs(root->left,depth+1);
        dfs(root->right,depth+1);
    }
    TreeNode* f(TreeNode* root,TreeNode* p,TreeNode* q)
    {
        if(root==nullptr||root==p||root==q)
        {
            return root;
        }
        TreeNode* left=f(root->left,p,q);
        TreeNode* right=f(root->right,p,q);
        if(left&&right)
        {
            return root;
        }
        if(left)
        {
            return left;
        }
        return right;
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        dfs(root,0);
        while(node.size()>2)
        {
            node.push_back(f(root,node[0],node[1]));
            node.erase(node.begin());
            node.erase(node.begin());
        }
        if(node.size()==2)
        {
            return f(root,node[0],node[1]);
        }
        return node[0];
    }
};