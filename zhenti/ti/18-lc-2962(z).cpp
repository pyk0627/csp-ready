class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int maxnum=ranges::max(nums);
        int n=nums.size();
        int cnt=0;
        long long ans=0;
        int l=0;
        for(int r=0;r<n;r++)
        {
            if(nums[r]==maxnum)
            {   
                cnt++;
            }
            while(cnt==k)
            {
                if(nums[l]==maxnum)
                {
                    cnt--;
                }
                l++;
            }
            ans+=l;
        }
        return ans;
    }
};