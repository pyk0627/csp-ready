const unsigned long long MOD = 1000000007;
class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        unsigned long long ans=0;
        vector<unsigned long long> hao(high+1,0);
        hao[0]=1;
        for(int i=1;i<=high;i++)
        {
            if(i<zero&&i<one)
            {
                hao[i]=0;
            }else if(i>=zero&&i<one)
            {
                hao[i]=hao[i-zero]%MOD;
            }else if(i<zero&&i>=one)
            {
                hao[i]=hao[i-one]%MOD;
            }else
            {
                hao[i]=(hao[i-zero]+hao[i-one])%(MOD);
            }
        }
        for(int i=low;i<=high;i++)
        {
            ans+=hao[i]%MOD;
        }
        return (int)(ans%MOD);
    }
};
/*
不能等最后结果很大了再取余，必须每次加法、累加之后立刻取余。
*/