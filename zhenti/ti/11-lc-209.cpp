class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int ans=n+1;
        int s=0;
        int l=0;
        for(int r=0;r<n;r++)
        {
            s+=nums[r];
            //缩小窗口后依然合法就继续缩小 
            while(s-nums[l]>=target)
            {
                s-=nums[l];
                l++;
            }
            if(s>=target)
            {
                ans=min(ans,r-l+1);
            }
        }
        if(ans<=n)
        {
            return ans;
        }else
        {
            return 0;
        }

    }
};