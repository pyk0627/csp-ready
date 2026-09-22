class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = INT_MAX;
        int f=0;
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size()-2;i++)
        {
            /*
            如果 i>0 且 nums[i]=nums[i−1]，
            那么 nums[i] 和后面数字相加的结果，必然在之前算过
            ，所以无需跑下面的双指针，直接 continue 外层循环。

            作者：灵茶山艾府
            链接：https://leetcode.cn/problems/3sum-closest/solutions/2337801/ji-zhi-you-hua-ji-yu-san-shu-zhi-he-de-z-qgqi/
            来源：力扣（LeetCode）
            著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
            */
            if(i>0&&nums[i]==nums[i-1])
            {
                continue;
            }
            /*
            设 s=nums[i]+nums[i+1]+nums[i+2]。
            如果 s>target，由于数组已经排序，
            后面无论怎么选，选出的三数之和不会比 s 还小，
            所以不会找到比 s 更优的答案了。
            所以只要 s>target，就可以直接 break 外层循环了。
            在 break 前判断 s 是否离 target 更近，如果更近，那么更新答案为 s。

            作者：灵茶山艾府
            链接：https://leetcode.cn/problems/3sum-closest/solutions/2337801/ji-zhi-you-hua-ji-yu-san-shu-zhi-he-de-z-qgqi/
            来源：力扣（LeetCode）
            著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
            */
            int s = nums[i]+nums[i+1]+nums[i+2];
            if(s>target)
            {
                if(abs(s-target)<res)
                {
                    f=s;
                }
                break;
            }
            /*
            设 s=nums[i]+nums[n−2]+nums[n−1]。
            如果 s<target，由于数组已经排序，
            nums[i] 加上后面任意两个数都不超过 s，
            所以下面的双指针就不需要跑了，
            无法找到比 s 更优的答案。
            但是后面还有更大的 nums[i]，
            可能找到一个离 target 更近的三数之和，
            所以还需要继续枚举，continue 外层循环。
            在 continue 前判断 s 是否离 target 更近，
            如果更近，那么更新答案为 s。

            作者：灵茶山艾府
            链接：https://leetcode.cn/problems/3sum-closest/solutions/2337801/ji-zhi-you-hua-ji-yu-san-shu-zhi-he-de-z-qgqi/
            来源：力扣（LeetCode）
            著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
            */
            s=nums[i]+nums[nums.size()-2]+nums[nums.size()-1];
            if(s<target)
            {
                if(abs(s-target)<res)
                {
                    res=abs(s-target);
                    f=s;
                }
                continue;
            }
            int j=i+1;
            int k=nums.size()-1;
            while(j<k)
            {
                // cout<<"nums[i]:"<<nums[i]<<endl;
                // cout<<"nums[j]:"<<nums[j]<<endl;
                // cout<<"nums[k]:"<<nums[k]<<endl;
                int t=nums[i]+nums[j]+nums[k];
                int t1 = abs(t-target);
                // cout<<"t:"<<t<<endl;
                // cout<<"t1:"<<t1<<endl;
                // cout<<"res:"<<res<<endl;

                if(t1<res)
                {
                    res=t1;
                    f=t;
                }
                if(t>target)
                {
                    k--;
                }else
                {
                    j++;
                }

            }
        }
        return f;
    }
};