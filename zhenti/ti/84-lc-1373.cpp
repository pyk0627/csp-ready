struct info
{
    bool isBST;
    int sum;
    int mn;
    int mx;
};
class Solution {
    int ans=0;
    info dfs(TreeNode* root)
    {
        if(root==nullptr)
        {
            info a;
            a.isBST=true;
            a.sum=0;
            a.mn=INT_MAX;
            a.mx=INT_MIN;
            return a;
        }
        if(root->left==nullptr&&root->right==nullptr)
        {
            info a;
            a.isBST=true;
            a.sum=root->val;
            if(a.sum>ans)
            {
              ans=a.sum;
            }
            a.mn=root->val;
            a.mx=root->val;
            return a;
        }
        info left=dfs(root->left);
        info right=dfs(root->right);
        if(left.isBST==true&&right.isBST==true)
        {
            int f=1;
            if(root->left!=nullptr)
            {
                if(root->left->val>=root->val||left.mx>root->val)
                {
                    f=0;
                }
            }
            if(root->right!=nullptr)
            {
                if(root->right->val<=root->val||right.mn<root->val)
                {
                    f=0;
                }
            }
            if(f)
            {
                info a;
                a.isBST=true;
                a.sum=root->val+left.sum+right.sum;
                if(a.sum>ans)
                {
                    ans=a.sum;
                }
                a.mn=left.mn;
                a.mx=right.mx;
                return a;
            }
        }
        info a;
        a.isBST=false;
        a.sum=0;
        a.mn=INT_MAX;
        a.mx=INT_MIN;
        return a;
   }
public:
    int maxSumBST(TreeNode* root) {
        dfs(root);
        return ans;
    }
};