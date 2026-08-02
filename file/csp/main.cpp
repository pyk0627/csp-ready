#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
    int ans=0;
    void dfs(TreeNode* root,int num)
    {
        cout<<root->val<<endl;
        if(root==nullptr)
        {
            return;
        }
        int f=1;
        if((root->left!=nullptr&&root->left->val>=root->val) ||
            (root->right!=nullptr&&root->right->val<=root->val))
        {
            f=0;
        }
        if(f)
        {
            num+=root->val;
        }
        if(num>ans)
        {
            ans=num;
        }
        cout<<"ans:"<<ans<<endl;
        if(root->left!=nullptr)
        {
            dfs(root->left,num);
        }
        if(root->right!=nullptr)
        {
            dfs(root->right,num);
        }
    }
public:
    int maxSumBST(TreeNode* root) {
        dfs(root,0);
        return ans;
    }
};
int main()
{
    TreeNode* root = new TreeNode(1); // 索引0

    // 索引1 root左子节点4
    root->left = new TreeNode(4);
    // 索引2 root右子节点3
    root->right = new TreeNode(3);

    // 索引3 root->left 左孩子2
    root->left->left = new TreeNode(2);
    // 索引4 root->left 右孩子4
    root->left->right = new TreeNode(4);

    // 索引5 root->right 左孩子2
    root->right->left = new TreeNode(2);
    // 索引6 root->right 右孩子5
    root->right->right = new TreeNode(5);

    // 索引7~12 全部null，无需创建任何节点

    // 索引13：root->left->right 的右孩子4
    root->left->right->right = new TreeNode(4);
    // 索引14：root->right->right 的左孩子6
    root->right->right->left = new TreeNode(6);
    Solution sol;
    cout<<sol.maxSumBST(root)<<endl;
    return 0;
}
