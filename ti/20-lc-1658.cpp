class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum=accumulate(nums.begin(),nums.end(),0);
        int x1=sum-x;
        if(x1<0)
        {
            return -1;
        }
        int l=0;
        int n=nums.size();
        int s=0;
        int ans=INT_MAX;
        for(int r=0;r<n;r++)
        {
            s+=nums[r];
            while(s>x1)
            {
                s-=nums[l];
                l++;
            }
            if(s==x1)
            {
                ans=min(ans,n-(r-l+1));
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