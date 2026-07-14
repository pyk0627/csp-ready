#include <iostream>
#include <string>
#include <map>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int n=s.size();
        if(n<t.size())
        {
            return "";
        }
        int l=0;
        map<char,int> cntt;
        for(int i=0;i<t.size();i++)
        {
            cntt[t[i]]++;
        }
        int cnt1=0;
        int ansl=0;
        int ansr=n;
        string ans;
        map<char,int> cnts;
        for(int r=0;r<n;r++)
        {
            cout<<"s[r]:"<<s[r]<<endl;
            cnts[s[r]]++;
            cout<<"cnts[s[r]]:"<<cnts[s[r]]<<endl;
            if(cntt[s[r]]>0 && cnts[s[r]]<=cntt[s[r]])
            {
                cnt1++;
            }
            while(cnt1>=t.size())
            {
                if(r-l+1<ansr-ansl+1)
                {
                    ansl=l;
                    ansr=r;
                }
                if(cntt[s[l]]>0)
                {
                    cnts[s[l]]--;
                    cnt1--;
                }
                l++;
            }
        }
        if(ansr==n)
        {
            return "";
        }
        ans = s.substr(ansl,ansr-ansl+1);
        return ans;
    }
};

int main() {
    Solution sol;
    string s = "bba";
    string t = "ab";
    string result = sol.minWindow(s, t);
    cout << result << endl;
    return 0;
}
