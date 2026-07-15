class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        auto it=min_element(time.begin(),time.end());
        long long l=*it-1;
        //这里确定最小值是 
        //time数组中的最小值减一
        //这个时候任何车都不可能跑一次
        //所以是最小值中的最大值 
        long long r=*it*(long long)totalTrips;
        //这里确定最大值是
        //让花费时间最少的那个车跑完全部的路程所用的时间  
        while(l+1<r)
        {
            long long mid=(r-l)/2+l;
            long long t=0;
            for(auto x : time)
            {
                t+=mid/x;
                if(t>=totalTrips)
                {
                    break;
                }
            }
            if(t>=totalTrips)
            {
                r=mid;
            }else
            {
                l=mid;
            }
        }
        return r;
    }
};
//如果超出时间限制可能是因为int类型溢出，把int改为long long可能就会好了 