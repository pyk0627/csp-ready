class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int n=nums.size();
        int targets[]=
        {
            nums[0]+nums[1],
            nums[n-1]+nums[n-2],
            nums[0]+nums[n-1]
        };
        int ans=0;
        for(auto& target:targets)
        {
            //没必要用三维数组
            //在每个遍历里，用二维数组
            vector<vector<int>> memo(n,vector<int>(n,-1));    
            auto dfs=[&](this auto&& dfs,int i,int j)->int
            {
                if(i>=j)
                {
                    return 0;
                }
                //用res引用表示记忆数组，后面会比较好写
                int &res=memo[i][j];
                if(res!=-1)
                {
                    return res;
                }    
                res=0;
                if(nums[i]+nums[j]==target)
                {
                    res=max(res,dfs(i+1,j-1)+1);
                }
                if(nums[j]+nums[j-1]==target)
                {
                    res=max(res,dfs(i,j-2)+1);
                }
                if(nums[i]+nums[i+1]==target)
                {
                    res=max(res,dfs(i+2,j)+1);
                }
                //这里不用写memo[i][j]=res，因为
                //res就是memo[i][j]的引用
                return res;
            };
            ans=max(ans,dfs(0,n-1));
        }
        return ans;
    }
};
