class Solution {
    vector<string> ans;
    string s;
    vector<int> temp;
    bool check()
    {
        int len=0;
        for(auto x:temp)
        {
            if(x<0 || x>255)
            {
                return false;
            }

            string str=to_string(x);
            len+=str.size();
        }
        if(len<s.size())
        {
            return false;
        }
        return true;
    }
    void dfs(int depth,int cnt)
    {
        if(depth==s.size()&&cnt==4)
        {
            if(check())
            {
                string str="";
                for(int i=0;i<4;i++)
                {
                    if(i>0)
                    {
                        str+='.';
                    }
                    str+=to_string(temp[i]);
                }
                ans.push_back(str);
            }
            return;
        }
        for(int i=1;i<=3;i++)
        {
            if(depth+i-1<s.size())
            {
                string str1=s.substr(depth,i);
                int num1=stoi(str1);
                temp.push_back(num1);
                dfs(depth+i,cnt+1);
                temp.pop_back();
            }
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        this->s=s;
        dfs(0,0);
        return ans;
    }
};