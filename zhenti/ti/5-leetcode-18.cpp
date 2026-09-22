#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n=nums.size();//用int类型存储长度，避免溢出
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for(int i=0;i<n-3;i++)
        {
            if(i>0&&nums[i]==nums[i-1])
            {
                continue;
            }
            /*
            设 s=nums[a]+nums[a+1]+nums[a+2]+nums[a+3]。
            如果 s>target，由于数组已经排序，后面无论怎么选，
            选出的四个数的和不会比 s 还小，
            所以后面不会找到等于 target 的四数之和了。
            所以只要 s>target，就可以直接 break 外层循环了。

            作者：灵茶山艾府
            链接：https://leetcode.cn/problems/4sum/solutions/2344514/ji-zhi-you-hua-ji-yu-san-shu-zhi-he-de-z-1f0b/
            来源：力扣（LeetCode）
            著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
            */
            if(nums[i]+nums[i+1]+nums[i+2]+nums[i+3]>target)
            {
                break;
            }
            /*
            设 s=nums[a]+nums[n−3]+nums[n−2]+nums[n−1]。
            如果 s<target，由于数组已经排序，
            nums[a] 加上后面任意三个数都不会超过 s，
            所以无法在后面找到另外三个数与 nums[a] 相加等于 target。
            但是后面还有更大的 nums[a]，
            可能出现四数之和等于 target 的情况，
            所以还需要继续枚举，continue 外层循环。

            作者：灵茶山艾府
            链接：https://leetcode.cn/problems/4sum/solutions/2344514/ji-zhi-you-hua-ji-yu-san-shu-zhi-he-de-z-1f0b/
            来源：力扣（LeetCode）
            著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
            */
            if(nums[i]+nums[n-3]+nums[n-2]+nums[n-1]<target)
            {
                continue;
            }
            for(int j=i+1;j<n-2;j++)
            {

                if(j>i+1&&nums[j]==nums[j-1])//这里是j>i+1,而不是j>0
                {
                    continue;
                }
                /*
                设 s=nums[a]+nums[b]+nums[b+1]+nums[b+2]。
                如果 s>target，由于数组已经排序，后面无论怎么选，
                选出的四个数的和不会比 s 还小，
                所以后面不会找到等于 target 的四数之和了。
                所以只要 s>target，就可以直接 break。

                作者：灵茶山艾府
                链接：https://leetcode.cn/problems/4sum/solutions/2344514/ji-zhi-you-hua-ji-yu-san-shu-zhi-he-de-z-1f0b/
                来源：力扣（LeetCode）
                著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
                */
                if(nums[i]+nums[j]+nums[j+1]+nums[j+2]>target)
                {
                    break;
                }
                if(nums[i]+nums[j]+nums[n-2]+nums[n-1]<target)
                {
                    continue;
                }
                int k=j+1;
                int l=nums.size()-1;
                // cout<<"k:"<<k<<endl;
                // cout<<"l:"<<l<<endl;
                while(k<l)
                {
                    // cout<<"nums[i]:"<<nums[i]<<endl;
                    // cout<<"nums[j]:"<<nums[j]<<endl;
                    // cout<<"nums[k]:"<<nums[k]<<endl;
                    // cout<<"nums[l]:"<<nums[l]<<endl;
                    long long t = (long long)nums[i]+nums[j]+nums[k]+nums[l];//将第一个数字转为long long 避免溢出
                    // cout<<"t:"<<t<<endl;
                    if(t<target)
                    {
                        k++;
                    }else if(t>target)
                    {
                        l--;
                    }else if(t==target)
                    {
                        vector<int> r(4);
                        r[0]=nums[i];
                        r[1]=nums[j];
                        r[2]=nums[k];
                        r[3]=nums[l];
                        res.push_back(r);

                        k++;
                        while(k<l&&nums[k]==nums[k-1])
                        {
                            k++;
                        }

                        l--;
                        while(k<l&&nums[l]==nums[l+1])
                        {
                            l--;
                        }
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    int n;
    cout << "请输入数组长度: ";
    cin >> n;

    vector<int> nums(n);
    cout << "请输入 " << n << " 个整数: ";
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    int target;
    cout << "请输入目标值: ";
    cin >> target;

    // 打印读取的数据，确认输入正确
    cout << "\n读取完成！数组为: ";
    for (int x : nums) cout << x << " ";
    cout << "\n目标值: " << target << endl;

    // 调用 fourSum（当前返回空）
    Solution sol;
    vector<vector<int>> result = sol.fourSum(nums, target);

    cout << "fourSum 返回结果（未实现）: ";
    // 打印空结果（便于观察）
    cout << "[]" << endl;

    return 0;
}
