class Solution {
    vector<string> arr;
    int ans=0;
    int len;
    string str="";
    int check()
    {
        map<char,int> cnt;
        for(auto x:str)
        {
            cnt[x]++;
            if(cnt[x]>1)
            {
                return 0;
            }
        }
        return str.size();
    }
    void dfs(int depth)
    {
        if(depth==len)
        {
            ans=max(ans,check());
            return;
        }
        dfs(depth+1);

        str+=arr[depth];
        if(check()==0)
        {
            str.erase(str.size()-arr[depth].size());
            return;
        }
        dfs(depth+1);
        str.erase(str.size()-arr[depth].size());
    }
public:
    int maxLength(vector<string>& arr) {
        this->arr=arr;
        len=arr.size();
        dfs(0);
        return ans;
    }
};