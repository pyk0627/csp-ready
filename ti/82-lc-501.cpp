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
    unordered_map<int,int> cnt;
    void dfs(TreeNode* root)
    {
        if(root==nullptr)
        {
            return;
        }
        dfs(root->left);
        cnt[root->val]++;
        dfs(root->right);
    }
public:
    vector<int> findMode(TreeNode* root) {
        dfs(root);
        vector<int> res;
        int maxcnt=0;
        for(auto& x:cnt)
        {
            if(x.second>maxcnt)
            {
                maxcnt=x.second;
            }
        }
        for(auto& x:cnt)
        {
            if(x.second==maxcnt)
            {
                res.push_back(x.first);
            }
        }
        return res;
    }
};