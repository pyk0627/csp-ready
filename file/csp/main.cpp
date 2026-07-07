#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int res=0;
        int len=nums.size();
        sort(nums.begin(),nums.end());
        for(int i=0;i<len-2;i++)
        {
            int j=i+1;
            int k=len-1;
            while(j<k)
            {
                cout<<"nums[i]:"<<nums[i]<<endl;
                cout<<"nums[j]:"<<nums[j]<<endl;
                cout<<"nums[k]:"<<nums[k]<<endl;
                cout<<"--------"<<endl;
                if(nums[i]+nums[j]>nums[k])
                {
                    cout<<nums[i]<<","<<nums[j]<<","<<nums[k]<<endl;
                    res+=k-j;
                    k--;
                }else
                {
                    if(nums[i]+nums[j]>nums[k-1])
                    {
                        res+=k-1-j;
                    }
                    j++;

                }
            }
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums;
    string line;

    cout << "请输入整数数组，以空格分隔，按回车结束: ";
    getline(cin, line);
    istringstream iss(line);
    int num;
    while (iss >> num) {
        nums.push_back(num);
    }

    int result = sol.triangleNumber(nums);
    cout << "有效三角形的个数为: " << result << endl;

    return 0;
}
