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
    int findBottomLeftValue(TreeNode* root) {
        int ans=0;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            for(int n=q.size();n--;)
            {
                auto t=q.front();
                q.pop();
                ans=t->val;
                if(t->right!=nullptr)
                {
                    q.push(t->right);
                }
                if(t->left!=nullptr)
                {
                    q.push(t->left);
                }
            }
        }
        return ans;
    }
};