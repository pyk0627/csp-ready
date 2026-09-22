class Solution {
public:
    int minLength(vector<int>& nums, int k) {
        int n=nums.size();
        int l=0;
        map<int,int> cnt;
        int s=0;
        int ans=INT_MAX;
        for(int r=0;r<n;r++)
        {
            cnt[nums[r]]++;
            if(cnt[nums[r]]==1)
            {
                s+=nums[r];
            }
            while(s>=k)
            {
                ans = min(ans,r-l+1);
                cnt[nums[l]]--;
                if(cnt[nums[l]]==0)
                {
                    s-=nums[l];
                }
                l++;
            }
        }
        if(ans==INT_MAX)
        {
            return -1;
        }else
        {
            return ans;
        }
    }
};