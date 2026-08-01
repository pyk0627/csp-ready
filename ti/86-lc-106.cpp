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
    vector<int> postorder;
    vector<int> inorder;
    TreeNode* build(int inl,int inr,int pol,int por)
    {
        if(inl>inr)
        {
            return nullptr;
        }
        TreeNode* root=new TreeNode(postorder[por]);
        int idx=0;
        for(int i=0;i<inorder.size();i++)
        {
            if(inorder[i]==postorder[por])
            {
                idx=i;
            }
        }
        int k=idx-inl;
        root->left=build(inl,idx-1,pol,pol+k-1);
        root->right=build(idx+1,inr,pol+k,por-1);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        this->inorder=inorder;
        this->postorder=postorder;
        return build(0,inorder.size()-1,0,postorder.size()-1);      
    }
};