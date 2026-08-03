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
    bool isEvenOddTree(TreeNode* root) {
        if(root==nullptr)
        {
            return true;
        }
        int depth=0;
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
            if(depth%2==0)
            {
                int i=0;
                for(;i<temp.size()-1;i++)
                {
                    if(temp[i]%2==0||temp[i]>=temp[i+1])
                    {
                        return false;
                    }
                }
                if(temp[i]%2==0)
                {
                    return false;
                }
            }else
            {
                int i=0;
                for(;i<temp.size()-1;i++)
                {
                    if(temp[i]%2!=0||temp[i]<=temp[i+1])
                    {
                        return false;
                    }
                }
                if(temp[i]%2!=0)
                {
                    return false;
                }
            }
            depth++;
        }
        return true;
    }
};