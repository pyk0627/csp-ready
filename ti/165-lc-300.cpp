class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> g;//贪心
        for(auto x:nums)//枚举nums的元素
        {
            auto it=ranges::lower_bound(g,x);
            //ranges::lower_bound比std::lower_bound使用其他更方便
            //ranges::lower_bound只需要传入数组名字
            //std::lower_bound需要传入g.begin(),g.end()
            //找g数组中第一个大于等于x的位置
            if(it==g.end())
            //如果没找到，就把当前的x放到g数组末尾
            {
                g.push_back(x);
            }else
            {
            //如果找到了，就把g数组中的元素替换为与之相等或者更小的x
                *it=x;
            }
        }
        return g.size();
    }
};