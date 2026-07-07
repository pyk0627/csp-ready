class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int ans=0;
        int n =nums.size();
        sort(nums.begin(),nums.end());
        //枚举最大边
        for(int k=n-1;k>=2;k--)
        {
            if(nums[0]+nums[1]>nums[k])
            {
                ans+=(k+1)*k*(k-1)/6;
                break;
            }
            if(nums[k-2]+nums[k-1]<nums[k])
            {
                continue;
            }
            int i=0;
            int j=k-1;
            while(i<j)
            {
                if(nums[i]+nums[j]>nums[k])
                {
                    ans+=j-i;
                    // 由于 nums 已经从小到大排序
                    // nums[i]+nums[j] > c 同时意味着：
                    // nums[i+1]+nums[j] > c
                    // nums[i+2]+nums[j] > c
                    // ...
                    // nums[j-1]+nums[j] > c
                    // 从 i 到 j-1 一共 j-i 个

                    //作者：灵茶山艾府
                    //链接：https://leetcode.cn/problems/valid-triangle-number/solutions/2432875/zhuan-huan-cheng-abcyong-xiang-xiang-shu-1ex3/
                    //来源：力扣（LeetCode）
                    //著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
                    j--;
                }else
                {
                    i++;
                }
            }
        }
        return ans;
    }
};