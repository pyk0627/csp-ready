class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n=obstacles.size();
        vector<int> ans;
        vector<int> dp;
        //dp数组的第k个位置，dp[k]存的是长度为k+1的非递减数组的最小值
        //dp数组中存的不是真实的实例，dp[k]存的是数组长度为k+1时，末尾的能有多小
        for(int i=0;i<n;i++)
        {
            int t=obstacles[i];//获取当前的障碍的高度
            auto it=ranges::upper_bound(dp,t);//在dp数组中找第一个大于障碍的位置
            int p=it-dp.begin();
            //it指向的是dp[p]
            //dp[p]是严格大于t的第一个
            //之前的dp[0]到dp[p-1]都是小于等于t的，小于等于t的有p个元素
            if(it==dp.end())//如果没找到，就放入dp数组中
            {
                dp.push_back(t);
            }else
            {
                *it=t;//如果找到了，就替换
            }
            ans.push_back(p+1);
        }
        return ans;
    }
};//1964. 找出到每个位置为止最长的有效障碍赛跑路线