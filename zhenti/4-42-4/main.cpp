#include <bits/stdc++.h>
using namespace std;

vector<int> nums;
vector<int> temp;

int f_xor(int i,int j)
{
    vector<int> t;
    do
    {
        t.push_back(nums[i]);
        i+=2;
    }while(i<j);
    return accumulate(t.begin(),
                      t.end(),
                      0,
                      bit_xor<int>());
}
int f(int i,int j)
{
    int res=0;
    int temp=i;
    for(int k=i;k<=j;k++)
    {
        if(f_xor(temp,k)==0)
        {
            res++;
            temp=k+1;
        }
    }
    return res;
}
int main()
{
    int n,q;
    cin>>n>>q;

    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        nums.push_back(a);
    }

    for(int i=0;i<q;i++)
    {
        int l,r;
        cin>>l>>r;
        cout<<f(l-1,r-1)<<endl;
    }

    return 0;
}
