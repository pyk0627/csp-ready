class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ans=0;
        map<char,int> count;
        int n=s.size();
        int l=0;
        for(int r=0;r<n;r++)
        {
            count[s[r]]++;
            while(count[s[r]]>1 && r>=l)
            {
                count[s[l]]--;
                l++;
            }
            ans=max(ans,r-l+1);
        }
        return ans;
    }
};