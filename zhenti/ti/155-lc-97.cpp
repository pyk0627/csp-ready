class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n=s1.size();//s1的长度
        int m=s2.size();//s2的长度
        if(n+m !=s3.size())//如果s1的长度加上s2的长度不等于s3的长度，则无法组成s3，直接返回false
        {
            return false;
        }
        vector<vector<int>> memo(n+1,vector<int>(m+1,-1));//记忆化搜索数组，初始化为－1
        auto dfs=[&](this auto&& dfs,int i,int j)->bool 
        //i代表还需要处理的s1的长度
        //j代表还需要处理的s2的长度
        { 
            if(i==0&&j==0)//如果两个都处理完了，则说明可以组成s3，返回true
            {
                return true;
            }
            if(memo[i][j]!=-1)//如果当前的情况之前处理过，则直接返回之前的结果
            {
                return memo[i][j];
            }
            int k=i+j
            //根据i和j的处理情况推导出s3需要处理的位置
            if(i>0&&s1[i-1]==s3[k-1]&&dfs(i-1,j))
            //如果当前的i还有未处理的，而且
            //s1的末尾等于s3的末尾，而且
            //除了末尾，剩下的也可以被完美处理
            //则返回true
            {
                return memo[i][j]=1;
            }
            if(j>0&&s2[j-1]==s3[k-1]&&dfs(i,j-1))
            {
                return memo[i][j]=1;
            }
            //如果当前s3的位置即不和s1的位置相同，也不和s2的位置相同则返回false
            return memo[i][j]=0;
        };
        //传入需要处理的长度
        return dfs(n,m);
    }
};