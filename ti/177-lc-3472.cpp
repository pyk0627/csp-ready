//在遇到关于子串的话
//就是考虑当前的字符选或者不选
//就是在考虑子串
class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n=s.size();
        //创建3维数组
        vector memo(n,vector(n,vector<int>(k+1,-1)));
        auto dfs=[&](this auto&& dfs,
                                int i,int j,int cnt)->int
        {
            if(i==j){return 1;}
            else if(i>j){return 0;}
            
            int &res=memo[i][j][cnt];
            if(res!=-1){return res;}

            //先比较，
            //不要当前的j或者不要当前的i，
            //这两种情况中的子串哪个最大
            res=max(dfs(i,j-1,cnt),dfs(i+1,j,cnt));

            //求出将两端改成相同的字母需要的操作数
            int d=abs(s[i]-s[j]);
            //26是因为一共有26个字母
            int op=min(d,26-d);

            //如果可以操作的话
            if(op<=cnt)
            {
                res=max(res,dfs(i+1,j-1,cnt-op)+2);
            }

            return memo[i][j][cnt]=res;
        };
        return dfs(0,n-1,k);
    }
};
