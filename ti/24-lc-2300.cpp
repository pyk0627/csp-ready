class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(),potions.end());
        int n=spells.size();
        vector<int> ans(n);
        for(int i=0;i<n;i++)
        {
            int x = spells[i];
            int l=-1;
            int r=potions.size();
            while(l+1<r)
            {
                int mid = (r-l)/2+l;
                if((long long)x*potions[mid] >= success)
                {
                    r=mid;
                }else
                {
                    l=mid;
                }
            }
            ans[i]=(int)potions.size()-r;
        }
        return ans;
    }
};