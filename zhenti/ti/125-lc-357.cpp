class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int ans=1;
        vector<uint8_t> vis(10,false);
        auto dfs=[&](this auto&& dfs,int depth)
        {
            if(depth==n)
            {
                return;
            }
            for(int i=0;i<10;i++)
            {
                if(vis[i]){continue;}
                if(i==0&&depth==0){continue;}

                vis[i]=true;
                ans++;
                dfs(depth+1);
                vis[i]=false;
                
            }
        };
        dfs(0);
        return ans;
    }
};