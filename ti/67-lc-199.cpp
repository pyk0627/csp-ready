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
    vector<int> ans;
    void d(TreeNode* root,int depth)
    {
        if(root==nullptr)
        {
            return;
        }
        if(depth==ans.size())
        {
            ans.push_back(root->val);
        }
        d(root->right,depth+1);
        d(root->left,depth+1);
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        d(root,0);
        return ans;
    }
};