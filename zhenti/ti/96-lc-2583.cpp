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
    vector<long long> ans;
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            long long sum=0;
            for(int n=q.size();n--;)
            {
                auto t=q.front();
                q.pop();
                sum+=t->val;
                if(t->left){q.push(t->left);}
                if(t->right){q.push(t->right);}
            }
            ans.push_back(sum);
        }
        sort(ans.begin(),ans.end());
        int len=ans.size();
        if(k>len)
        {
            return -1;
        }else
        {
            return ans[len-k];
        }
    }
};