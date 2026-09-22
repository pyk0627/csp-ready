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
    TreeNode* replaceValueInTree(TreeNode* root) {
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
            int sum=0;
            for(int n=q.size();n--;)
            {
                auto t=q.front();
                q.pop();
                if(depth<=1)
                {
                    t->val=0;
                }
                if(depth>=1)
                {
                    if(t->left){sum+=t->left->val;}
                    if(t->right){sum+=t->right->val;}
                }
                temp.push_back(t);
                if(t->left){q.push(t->left);}
                if(t->right){q.push(t->right);}
            }
            if(depth>=1)
            {
                for(int i=0;i<temp.size();i++)
                {
                    int num=sum;
                    if(temp[i]->left)
                    {
                        num-=temp[i]->left->val;
                    }
                    if(temp[i]->right)
                    {
                        num-=temp[i]->right->val;
                    }
                    if(temp[i]->left)
                    {
                        temp[i]->left->val=num;
                    }
                    if(temp[i]->right)
                    {
                        temp[i]->right->val=num;
                    }
                }
            }
            depth++;
        }
        return root;
    }
};