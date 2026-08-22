class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n=str1.size();
        int m=str2.size();
        vector<string> dp(m+1);
        for(int j=0;j<=m;j++)//i等于0的时候
        {
            dp[j]=str2.substr(0,j);
        }
        for(int i=1;i<=n;i++)
        {
            string pre=dp[0];
            dp[0]=str1.substr(0,i);
            for(int j=1;j<=m;j++)
            {
            //     if(i==0)
            //     {
            //         dp[j]=str2.substr(0,j);//这里更新dp[j]的话
            //会影响下面的temp，所以在循环开始前初始化
            //     }
            //     if(j==0)
            //     {
            //         dp[j]=str1.substr(0,i);//这里也放到循环外单独处理
            //     }
                string temp=dp[j];
                if(i>0&&j>0&&str1[i-1]==str2[j-1])
                {
                    dp[j]=pre+str1[i-1];
                }else if(i>0&&j>0&&str1[i-1]!=str2[j-1])
                {
                    string s1=dp[j]+str1[i-1];
                    string s2=dp[j-1]+str2[j-1];
                    if(s1.size()<s2.size())
                    {
                        dp[j]=s1;
                    }else
                    {
                        dp[j]=s2;
                    }
                }
                pre=temp;
            }
        }
        return dp[m];
        // vector<vector<string>> memo(n+1,vector<string>(m+1,"0"));
        // auto dfs=[&](this auto&& dfs,int i,int j)->string
        // {
        //     if(memo[i+1][j+1]!="0")
        //     {
        //         return memo[i+1][j+1];
        //     }
        //     if(i<0)
        //     {
        //         return memo[i+1][j+1]=str2.substr(0,j+1);
        //     }
        //     if(j<0)
        //     {
        //         return memo[i+1][j+1]=str1.substr(0,i+1);
        //     }
        //     if(str1[i]==str2[j])
        //     {
        //         return memo[i+1][j+1]=dfs(i-1,j-1)+str1[i];
        //     }else
        //     {
        //         string s1=dfs(i-1,j)+str1[i];
        //         string s2=dfs(i,j-1)+str2[j];
        //         if(s1.size()<s2.size())
        //         {
        //             return memo[i+1][j+1]=s1;
        //         }else
        //         {
        //             return memo[i+1][j+1]=s2;
        //         }
        //     }
        // };
        // return dfs(n-1,m-1);
    }
};