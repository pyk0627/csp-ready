class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int ans=0;
        map<int,int> count;
        int n=nums.size();
        int l=0;
        for(int r=0;r<n;r++)
        {
            count[nums[r]]++;
            while(count[nums[r]]>k)
            {
                count[nums[l]]--;
                l++;
            }
            ans=max(ans,r-l+1);
        }
        return ans;
    }
};