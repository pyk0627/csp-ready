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
    int deepestLeavesSum(TreeNode* root) {
        if(root==nullptr)
        {
            return 0;
        }
        int sum=0;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            int temp=0;
            for(int n=q.size();n--;)
            {
                auto t=q.front();
                q.pop();
                temp+=t->val;
                if(t->left){q.push(t->left);}
                if(t->right){q.push(t->right);}
            }
            sum=temp;
        }
        return sum;
    }
};