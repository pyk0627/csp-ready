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
    vector<int> rightSideView(TreeNode* root) {
        if(root==nullptr)
        {
            return {};
        }
        vector<int> ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            vector<int> temp;
            for(int n=q.size();n--;)
            {
                auto t=q.front();
                q.pop();
                temp.push_back(t->val);
                if(t->left){q.push(t->left);}
                if(t->right){q.push(t->right);}
            }
            ans.push_back(temp[temp.size()-1]);
        }
        return ans;
    }
};