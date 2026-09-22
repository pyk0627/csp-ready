class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        // vector<int> cache(costs.size()+5);
        // auto dfs=[&](this auto&& dfs,int i)->int
        // {
        //     if(cache[i]!=0)
        //     {
        //         return cache[i];
        //     }
        //     if(i==0)
        //     {
        //         return cache[i]=costs[i]+1;
        //     }
        //     if(i==1)
        //     {
        //         return cache[i]=min(dfs(i-1)+costs[i]+1,costs[i]+4);
        //     }
        //     if(i==2)
        //     {
        //         int re1=min(dfs(i-1)+costs[i]+1,dfs(i-2)+costs[i]+4);
        //         int re2=min(re1,costs[i]+9);
        //         return cache[i]=re2;
        //     }
        //     int res1=min(dfs(i-1)+costs[i]+1,dfs(i-2)+costs[i]+4);
        //     int res2=min(res1,dfs(i-3)+costs[i]+9);
        //     return cache[i]=res2;
        // };
        // return dfs(costs.size()-1);
        int f2=0;
        int f1=0;
        int f0=0;
        int res1=0;
        int res2=0;
        for(int i=0;i<costs.size();i++)
        {
            if(i==0)
            {
                res2=costs[i]+1;
            }else if(i==1)
            {
                res2=min(f2+costs[i]+1,costs[i]+4);
            }else if(i==2)
            {
                res1=min(f2+costs[i]+1,f1+costs[i]+4);
                res2=min(res1,costs[i]+9);
            }else
            {
                res1=min(f2+costs[i]+1,f1+costs[i]+4);
                res2=min(res1,f0+costs[i]+9);
            }
            f0=f1;
            f1=f2;
            f2=res2;
        }
        return f2;
    }
};