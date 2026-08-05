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
/*
c++中，string类型的str可以进行+=一个string
类型的数据，可以-=一个string类型的数据吗

#include <iostream>
#include <string>

void removeSuffix(std::string& str, const std::string& suffix)
{
    if (str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0)
    {
        str.erase(str.size() - suffix.size());
    }
}

int main()
{
    std::string str = "hello world";
    std::string suffix = " world";

    removeSuffix(str, suffix);

    std::cout << str << std::endl; // hello
}


*/