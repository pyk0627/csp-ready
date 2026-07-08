class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int ans=0;
        int cnt=0;
        int n=s.size();
        int l=0;
        for(int r=1;r<n;r++)
        {
            if(s[r]==s[r-1])
            {
                cnt++;
            }
            //cout<<"s[r-1]:"<<s[r-1]<<endl;
            //cout<<"s[r]:"<<s[r]<<endl;
            //cout<<"cnt:"<<cnt<<endl;

            //cout<<"s[l]:"<<s[l]<<endl;

            //不断缩小窗口直到满足条件为止
            //用while而不是if
            while(cnt>1)
            {
                l++;
                if(s[l]==s[l-1])
                {
                    cnt--;
                }
            }
            if(cnt<=1)
            {
                //cout<<"ans:"<<ans<<endl;
                //cout<<"r-l+1="<<r-l+1<<endl;
                ans=max(ans,r-l+1);
            }
            //cout<<"--------"<<endl;
        }
        if(n==1)
        {
            ans=1;
        }
        return ans;
    }
};