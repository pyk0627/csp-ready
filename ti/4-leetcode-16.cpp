#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

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
            那么 nums[i] 和后面数字相加的结果，必然在之前算过，
            所以无需跑下面的双指针，直接 continue 外层循环。

            作者：灵茶山艾府
            链接：https://leetcode.cn/problems/3sum-closest/solutions/2337801/ji-zhi-you-hua-ji-yu-san-shu-zhi-he-de-z-qgqi/
            来源：力扣（LeetCode）
            著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
            */
            if(i>0&&nums[i]==nums[i-1])
            {
                continue;
            }
            int j=i+1;
            int k=nums.size()-1;
            while(j<k)
            {
                cout<<"nums[i]:"<<nums[i]<<endl;
                cout<<"nums[j]:"<<nums[j]<<endl;
                cout<<"nums[k]:"<<nums[k]<<endl;
                int t=nums[i]+nums[j]+nums[k];
                int t1 = abs(t-target);
                cout<<"t:"<<t<<endl;
                cout<<"t1:"<<t1<<endl;
                cout<<"res:"<<res<<endl;

                //筛选更优的结果
                if(t1<res)
                {
                    res=t1;
                    f=t;
                }

                //不断逼近目标
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

int main() {
    int n;
    cout << "请输入数组长度: ";
    cin >> n;

    vector<int> nums(n);
    cout << "请输入 " << n << " 个整数（空格分隔）: ";
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    int target;
    cout << "请输入目标值: ";
    cin >> target;

    Solution sol;
    int result = sol.threeSumClosest(nums, target);
    cout << "最接近的三数之和为: " << result << endl;

    return 0;
}
