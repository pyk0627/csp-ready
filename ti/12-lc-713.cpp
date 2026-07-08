class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        long long s=1;
        int n=nums.size();
        int ans=0;
        int l=0;
        for(int r=0;r<n;r++)
        {
            s*=nums[r];
            while(s>=k)
            {
                s/=nums[l];
                l++;
            }
            if(s<k)
            {
                ans+=r-l+1;
            }
        }
        return ans;
    }
};