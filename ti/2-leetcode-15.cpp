
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
