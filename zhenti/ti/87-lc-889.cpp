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
    vector<int> postorder;
    TreeNode* build(int prel,int prer,int posl,int posr)
    {
        if(prel>prer)
        {
            return nullptr;
        }
        TreeNode* root=nullptr;
        if(prel<preorder.size())
        {
            root = new TreeNode(preorder[prel]);
        }
        if(prel==prer)
        {
            return root;
        }
        int a=0;
        if(prel<preorder.size()-1)
        {
            a=preorder[prel+1];
        }
        int idx=0;
        for(int i=0;i<postorder.size();i++)
        {
            if(postorder[i]==a)
            {
                idx=i;
            }
        }
        int k=idx-posl+1;
        root->left=build(prel+1,prel+k,posl,posl+k-1);
        root->right=build(prel+k+1,prer,posl+k,posr-1);
        return root;        
    }
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        this->preorder=preorder;
        this->postorder=postorder;
        return build(0,preorder.size()-1,0,postorder.size()-1);
    }
};