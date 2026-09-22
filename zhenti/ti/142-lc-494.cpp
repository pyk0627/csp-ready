class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int s=accumulate(nums.begin(),nums.end(),0)-abs(target);
        if(s<0||s%2)
        {
            return 0;
        }
        s/=2;
        vector<int> f(s+1);
        f[0]=1;
        for(auto x:nums)
        {
            for(int c=s;c>=x;c--)
            {
                f[c]+=f[c-x];
            }
        }
        return f[s];
    }
};