#include <iostream>
using namespace std;
int main()
{
    //超过10^9，用long long
    long long  n=0;
    long long k=0;
    long long m=0;
    cin>>n>>k>>m;
    //l代表一定可行的
    //r代表一定不可行的
    long long l=0;
    long long r=n-n*k/100+1;
    while(l+1<r)
    {
       long long mid=(l+r)/2;
       long long day=0;

       long long cur_n=n;
       long long sheng=0;
        while(1)
        {
            //向上取整
            long long bian=(cur_n*k+100-1)/100;
            sheng=cur_n-bian-mid;
            if(sheng>=0)
            {
                cur_n=sheng;
                day++;
                //提前退出
                if(day>=m)
                {
                    //这里的break只会打断一层的while
                    break;
                }
            }else
            {
                break;
            }
        }
        
        //如果当前是可行的，就把l包含进去
        if(day>=m)
        {
            l=mid;
        }else
        {
            r=mid;
        }
    }
    //最后输出最可行的
    cout<<l<<endl;
    return 0;
}
