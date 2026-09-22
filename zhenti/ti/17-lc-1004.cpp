class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int ans=0;
        int s=0;
        int n=nums.size();
        vector<int> sig(n);
        copy(nums.begin(),nums.end(),sig.begin());
        int l=0;
        for(int r=0;r<n;r++)
        {
            //cout<<"nums[r]:"<<nums[r]<<endl;
            if(nums[r]==1)
            {
                s++;
            }else if(nums[r]==0&&k>0)
            {
                s++;
                k--;
            }else if(nums[r]==0&&k==0)
            {
                //依旧是while而不是if
                //因为每个外层for循环都有对应的任务
                //要用while在这个循环之内
                //把任务做完
                while(sig[l]!=0)
                {
                    l++;
                }
                nums[l]=0;
                l++;
                //cout<<"l:"<<l<<endl;
                nums[r]=1;
                //cout<<"r:"<<r<<endl;
                s=r-l+1;
            }
            //cout<<"k:"<<k<<endl;
            //cout<<"s:"<<s<<endl;
            ans = max(ans,s);
            //cout<<"--------"<<endl;
        }
        return ans;
    }
};