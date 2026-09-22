class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long n=nums.size();
        long long l=0;
        vector<long long> qian(n);
        long long ans=0;
        for(long long i=0;i<n;i++)
        {
            if(i==0)
            {
                qian[i]=nums[i];
            }else
            {
                qian[i]=(long long)nums[i]+qian[i-1];//（这里出错过）是nums【i】+qian【i-1】而不是qian[i]
            }
            //cout<<"qian[i]:"<<qian[i]<<endl;
        }
        for(long long r=0;r<n;r++)
        {
            long long fen;
            if(l==0)
            {
                fen=qian[r]*(long long)(r+1);
            }else
            {
                fen=(qian[r]-qian[l-1])*(long long)(r-l+1);//这里是qian[r]-qian[l-1]而不是qian[r]-qian[l]
            }
           // cout<<"l:"<<l<<endl;
           // cout<<"r:"<<r<<endl;
           // cout<<"fen:"<<fen<<endl;
            if(fen<k)
            {
                ans+=(long long)r-l+1;
            }else
            {
                while(fen>=k)
                {
                    l++;
                    fen=(qian[r]-qian[l-1])*(long long)(r-l+1);
                }
               // cout<<"--------"<<endl;
              //  cout<<"l:"<<l<<endl;
               // cout<<"r:"<<r<<endl;
               // cout<<"fen:"<<fen<<endl;
               // cout<<"--------"<<endl;
                ans+=r-l+1;//这个一开始我没写else，写在了更外一层，导致结果偏大
            }
            //cout<<"ans:"<<ans<<endl;
        }
        return ans;
    }
};