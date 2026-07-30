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
    map<int,int> cnt;
    int dfs(TreeNode* root)
    {
        if(root==nullptr)
        {
            return 0;
        }
        int left=dfs(root->left);
        int right=dfs(root->right);
        int sum=root->val+left+right;
        cnt[sum]++;
        return sum;
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        dfs(root);
        vector<int> result;
        int freq=0;
        for(auto& [sum,f]:cnt)
        {
            if(f>freq)
            {
                freq=f;
                result.clear();
                result.push_back(sum);
            }else if(f==freq)
            {
                result.push_back(sum);
            }
        }
        return result;
    }
};