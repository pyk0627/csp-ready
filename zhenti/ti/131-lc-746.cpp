class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        // vector<int> cache(cost.size()+5,0);
        // auto dfs=[&](this auto&& dfs,int i)
        // {
        //     if(i<=0)
        //     {
        //         return 0;
        //     }
        //     if(i==1)
        //     {
        //         return min(dfs(i-1)+cost[i-1],0);
        //     }
        //     if(cache[i]!=0)
        //     {
        //         return cache[i];
        //     }
        //     int res=min(dfs(i-1)+cost[i-1],dfs(i-2)+cost[i-2]);
        //     cache[i]=res;
        //     return res;
        // };
        // return dfs(cost.size());
        int ans;
        int f0=0;
        int f1=0;
        for(int i=0;i<=cost.size();i++)
        {
            if(i==0)
            {
                f0=0;
                f1=0;
            }else if(i==1)
            {
                int res=min(f1+cost[i-1],0);
                f0=f1;
                f1=res;
            }else
            {
                int res=min(f1+cost[i-1],f0+cost[i-2]);
                f0=f1;
                f1=res;
            }
        }
        return f1;
    }
};