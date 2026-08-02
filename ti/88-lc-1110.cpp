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
    unordered_set<int> todel;
    vector<TreeNode*> ans;
    TreeNode* dfs(TreeNode* root)
    {
        if(root==nullptr)
        {
            return nullptr;
        }
        root->left=dfs(root->left);
        root->right=dfs(root->right);
        if(todel.find(root->val)!=todel.end())
        {
            if(root->left!=nullptr)
            {
                ans.push_back(root->left);
            }
            if(root->right!=nullptr)
            {
                ans.push_back(root->right);
            }
            return nullptr;
        }else
        {
            return root;
        }
    }
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        todel.insert(to_delete.begin(),to_delete.end());
        TreeNode* f=dfs(root);
        if(f!=nullptr)
        {
            ans.push_back(f);
        }
        return ans;
    }
};