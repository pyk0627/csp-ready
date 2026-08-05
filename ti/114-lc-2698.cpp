class Solution {
    int i;
    string str;
    int sum=0;
    int f=0;
    void dfs(int depth)
    {
        if(depth==str.size())
        {
            if(sum==i)
            {
                f=1;
            }
        }
        for(int i=depth;i<str.size();i++)
        {
            string t=str.substr(depth,i-depth+1);
            sum+=stoi(t);
            dfs(i+1);
            sum-=stoi(t);
        }
    }
public:
    int punishmentNumber(int n) {
        int ans=0;
        for(i=1;i<=n;i++)
        {
            f=0;
            int num=i*i;
            str=to_string(num);
            dfs(0);
            if(f)
            {
                ans+=num;
            }
        }
        return ans;
    }
};