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
/*
如果 nums[left]+nums[right]<target，
由于数组是有序的，
nums[left] 与下标 i 在区间 [left+1,right] 中的任何 nums[i] 相加，
都是 <target 的，
因此直接找到了 right−left 个合法数对，加到答案中，
然后将 left 加一。
*/
//上面的，我写了一个外层for循环，和这个left加一是等效的，但没有这个简洁
/*
class Solution {
public:
    int countPairs(vector<int>& nums, int target) {
        ranges::sort(nums);
        int ans = 0, left = 0, right = nums.size() - 1;
        while (left < right) {
            if (nums[left] + nums[right] < target) {
                ans += right - left;
                left++;
            } else {
                right--;
            }
        }
        return ans;
    }
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/count-pairs-whose-sum-is-less-than-target/solutions/2396216/onlogn-pai-xu-shuang-zhi-zhen-by-endless-qk40/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/