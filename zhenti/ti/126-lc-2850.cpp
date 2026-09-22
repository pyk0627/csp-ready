class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        vector<vector<int>> yu;
        vector<vector<int>> kong;
        for(int i=0;i<9;i++)
        {
            int x=i/3;
            int y=i%3;
            if(grid[x][y]==0)
            {
                vector<int> t(2);
                t[0]=x;
                t[1]=y;
                kong.emplace_back(t);
            }
            int cnt=grid[x][y]-1;
            for(int j=0;j<cnt;j++)
            {
                vector<int> t(2);
                t[0]=x;
                t[1]=y;
                yu.emplace_back(t);
            }
        }
        vector<bool> vis(yu.size(),false);
        int ans=INT_MAX;
        int temp=0;
        auto dfs=[&](this auto&& dfs,int i)->void
        {
            if(i==yu.size())
            {
                ans=min(temp,ans);
                return;
            }
            for(int j=0;j<yu.size();j++)
            {
                if(!vis[j])
                {
                    vis[j]=true;
                    temp+=abs(yu[j][0]-kong[i][0])+abs(yu[j][1]-kong[i][1]);
                    dfs(i+1);
                    vis[j]=false;
                    temp-=abs(yu[j][0]-kong[i][0])+abs(yu[j][1]-kong[i][1]);
                }
            }
        };
        dfs(0);
        return ans;
    }
};