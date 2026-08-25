class Solution {
    int f(vector<int>& x)
    {
        vector<int> dp1;
        for(int i=0;i<x.size();i++)
        {
            int t=x[i];
            auto it=ranges::lower_bound(dp1,t);
            if(it==dp1.end())
            {
                dp1.push_back(t);
            }else
            {
                *it=t;
            }
        }
        return dp1.size();
    }
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n=nums.size();
        int ans=INT_MAX;
        for(int i=2;i<=n-1;i++)
        {
            vector<int> left(nums.begin(),nums.begin()+i);
            int dp1len=f(left);
            if(dp1len==1)
                continue;
            vector<int> right(nums.begin()+i-1,nums.end());
            reverse(right.begin(),right.end());
            int dp2len=f(right);
            int res=left.size()-dp1len+right.size()-dp2len;
            if(dp2len==1)
                continue;
            ans=min(ans,res);
        }
        return ans;
    }
};//1671. 得到山形数组的最少删除次数