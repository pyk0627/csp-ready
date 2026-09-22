class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string path(n*2,')');

        auto check=[&](string str)->bool
        {
            int left=0;
            int right=0;
            for(auto x:str)
            {
                if(x=='(')
                {
                    left++;
                }
                if(x==')')
                {
                    right++;
                }
                if(left<right)
                {
                    return false;
                }
            }
            return true;
        };
        auto dfs=[&](this auto&& dfs,int left,int i)->void
        {
            if(left==0)
            {
                if(check(path))
                {
                    ans.emplace_back(path);
                }
                return;
            }

            for(int j=i;j<n*2;j++)
            {
                path[j]='(';
                dfs(left-1,j+1);
                path[j]=')';
            }
        };
        dfs(n,0);
        return ans;
    }
};