class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left=-1;
        int right=nums.size()-1;
        while(left+1<right)
        {
            int mid=(left+right)/2;
            if(nums[mid]>nums[nums.size()-1])
            {
                left=mid;
            }else
            {
                right=mid;
            }
        }
        if(target<nums[nums.size()-1])
        {
            left=right-1;
            right=nums.size()-1;
            while(left+1<right)
            {
                int mid=(left+right)/2;
                if(nums[mid]<target)
                {
                    left=mid;
                }else if(nums[mid]>target)
                {
                    right=mid;
                }else
                {
                    return mid;
                }
            }
            return -1;
        }else if(target>nums[nums.size()-1])
        {
            left=-1;
            while(left+1<right)
            {
                int mid=(left+right)/2;
                if(nums[mid]<target)
                {
                    left=mid;
                }else if(nums[mid]>target)
                {
                    right=mid;
                }else
                {
                    return mid;
                }
            }
            return -1;
        }else
        {
            return nums.size()-1;
        }
    }
};