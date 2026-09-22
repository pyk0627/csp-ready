class Solution {
public:
    int climbStairs(int n) {
        // vector<int> cache(n+5);
        // auto dfs=[&](this auto&& dfs,int i)
        // {
        //     if(i<0)
        //     {
        //         return 0;
        //     }
        //     if(i==0)
        //     {
        //         return 1;
        //     }
        //     if(cache[i]!=0)
        //     {
        //         return cache[i];
        //     }
        //     int res=dfs(i-1)+dfs(i-2);
        //     cache[i]=res;
        //     return res;
        // };
        // return dfs(n);
        int f0=0;
        int f1=1;
        for(int i=2;i<n+2;i++)
        {
            int f2=f1+f0;
            f0=f1;
            f1=f2;
        }
        return f1;
    }
};