
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for(int i=0;i<nums.size()-2;i++)
        {
            if(i>0 && nums[i]==nums[i-1])
            {
                continue;
            }

            /*
            优化一：如果 nums[i] 与后面最小的两个数相加 
            nums[i]+nums[i+1]+nums[i+2]>0，
            那么后面不可能存在三数之和等于 0，
            break 外层循环。
            */
            if(nums[i]+nums[i+1]+nums[i+2]>0)
            {
                break;
            }
            /*
            优化二：如果 nums[i] 与后面最大的两个数相加 
            nums[i]+nums[n−2]+nums[n−1]<0，
            那么内层循环不可能存在三数之和等于 0，
            但继续枚举，nums[i] 可以变大，
            所以后面还有机会找到三数之和等于 0，
            continue 外层循环。
            */
            if(nums[i]+nums[nums.size()-1]+nums[nums.size()-2]<0)
            {
                continue;
            }
            int j=i+1;
            int k=nums.size()-1;
            while(j<k)
            {
                if(nums[j]+nums[k]<-nums[i])
                {
                    j++;
                }else if(nums[j]+nums[k]>-nums[i])
                {
                    k--;
                }else if(nums[j]+nums[k]==-nums[i])
                {
                    vector<int> t(3);
                    t[0] = nums[i];
                    t[1]= nums[j];
                    t[2]=nums[k];

                    res.push_back(t);

                    j++;
                    while(j<k &&nums[j]==nums[j-1])
                    {
                        j++;
                    }
                    k--;
                    while(j<k &&nums[k]==nums[k+1])
                    {
                        k--;
                    }
                }
            }
        }
        return res;
    }
};
