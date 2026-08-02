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
    vector<vector<int>> ans;
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root==nullptr)
        {
            return {};
        }
        queue<TreeNode*> q;
        q.push(root);
        bool f=false;
        while(!q.empty())
        {
            vector<int> temp;
            for(int n=q.size();n--;)
            {
                auto node=q.front();
                q.pop();
                temp.push_back(node->val);
                if(node->left!=nullptr)
                {
                    q.push(node->left);
                }
                if(node->right!=nullptr)
                {
                    q.push(node->right);
                }
            }
            if(f)
            {
                reverse(temp.begin(),temp.end());
            }
            ans.push_back(move(temp));
            f=!f;
        }
        return ans;
    }
};