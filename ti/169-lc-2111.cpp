class Solution {
    int f(vector<int>& x)
    {
        vector<int> dp;
        for(auto& q:x)
        {
            auto it=ranges::upper_bound(dp,q);
            if(it==dp.end())
            {
                dp.push_back(q);
            }else
            {
                *it=q;
            }
        }
        return dp.size();
    }
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n=arr.size();
        vector<vector<int>> array(k);
        for(int i=0;i<k;i++)
        {
            int t=i;
            while(t<n)
            {
                array[i].push_back(arr[t]);
                t+=k;
            }
        }
        int ans=0;
        for(int i=0;i<k;i++)
        {
            ans+=array[i].size()-f(array[i]);
        }
        return ans;
    }
};
// 2111. 使数组 K 递增的最少操作次数