class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int ans=0;
        sort(arr2.begin(),arr2.end());
        for(int x : arr1)
        {
            //满足距离问题可以转化为满足在一个区间内的问题
            auto it = ranges::lower_bound(arr2,x-d);
            if(it == arr2.end() || *it > x+d)
            {
                ans++;
            }
        }
        return ans;
    }
};