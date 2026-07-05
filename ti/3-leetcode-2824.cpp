class Solution
{
public:
    int countPairs(vector<int>& nums, int target)
    {
        int res=0;
        sort(nums.begin(),nums.end());
        for(int k=0; k<nums.size()-1; k++)
            {
                int i=k;
                int j=nums.size()-1;
                while(i<j)
                    {
                        if(nums[i]+nums[j]<target)
                            {
                                res+=j-i;
                                break;
                            }
                        else
                            {
                                j--;
                            }
                    }
            }
        return res;
    }
};
