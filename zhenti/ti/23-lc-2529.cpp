class Solution {
    int lb(vector<int>& nums,int k)
    {
        int l=-1;
        int r=nums.size();
        while(l+1 < r)
        {
            int mid = (r-l)/2+l;
            if(nums[mid]>=k)
            {
                r=mid;
            }else
            {
                l=mid;
            }
        }
        return r;
    }
public:
    int maximumCount(vector<int>& nums) {
        int n = nums.size();
        int r1 = lb(nums,1);
        int l1 = lb(nums,0)-1;
        return max(l1+1,n-r1);
    }
};