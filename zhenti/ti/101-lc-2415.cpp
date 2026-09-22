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
    TreeNode* reverseOddLevels(TreeNode* root) {
        if(root==nullptr)
        {
            return nullptr;
        }
        int depth=0;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            vector<TreeNode*> temp;
            vector<int> tempnum;
            for(int n=q.size();n--;)
            {
                auto t=q.front();
                q.pop();
                temp.push_back(t);
                tempnum.push_back(t->val);
                if(t->left){q.push(t->left);}
                if(t->right){q.push(t->right);}
            }
            if(depth%2!=0)
            {
                reverse(tempnum.begin(),tempnum.end());
                for(int i=0;i<temp.size();i++)
                {
                    temp[i]->val=tempnum[i];
                }
            }
            depth++;
        }
        return root;
    }
};