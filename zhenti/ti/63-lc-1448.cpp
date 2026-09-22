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
    int goodNodes(TreeNode* root,int num=-INT_MAX)
    {
        if(root==nullptr)
        {
            return 0;
        }
        if(root->val>=num)
        {
            num=root->val;
            return 1+goodNodes(root->left,num)+goodNodes(root->right,num);
        }else
        {
            return goodNodes(root->left,num)+goodNodes(root->right,num);            
        }
    }
};