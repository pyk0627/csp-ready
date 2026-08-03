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
    int targetSum;
    vector<vector<int>> ans;
    vector<int> temp;
    void dfs(TreeNode* root,int sum)
    {
        if(root!=nullptr&&root->left==nullptr&&root->right==nullptr&&sum+root->val==targetSum)
        {
            temp.push_back(root->val);
            ans.push_back(temp);
            temp.pop_back();
            return;
        }
        if(root!=nullptr)
        {
            sum+=root->val;
            temp.push_back(root->val);
            if(root->left){dfs(root->left,sum);}
            if(root->right){dfs(root->right,sum);}
            temp.pop_back();
        }
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        this->targetSum=targetSum;
        dfs(root,0);
        return ans;
    }
};