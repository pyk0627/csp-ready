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
    vector<int> preorder;
    vector<int> inorder;
    TreeNode* build(int prel,int prer,int inl,int inr)
    {
        if(prel>prer)
        {
            return nullptr;
        }
        int root=preorder[prel];
        TreeNode* r=new TreeNode(root);
        int idx=0;
        for(int i=0;i<inorder.size();i++)
        {
            if(inorder[i]==root)
            {
                idx=i;
            }
        }
        int k=idx-inl;
        r->left=build(prel+1,prel+k,inl,idx-1);
        r->right=build(prel+k+1,prer,idx+1,inr);
        return r;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        this->preorder=preorder;
        this->inorder=inorder;
        return build(0,preorder.size()-1,0,inorder.size()-1);
    }
};