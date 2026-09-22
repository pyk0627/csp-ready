class Solution {
public:
    int maxArea(vector<int>& height) {
        int ans=0;
        int l=0;
        int r=height.size()-1;
        while(l<r)
        {
            if(height[l]<height[r])
            {
                int s = (r-l)*height[l];
                if(s>ans)
                {
                    ans=s;
                }
                l++;
            }else
            {
                int s = (r-l)*height[r];
                if(s>ans)
                {
                    ans=s;
                }
                r--;
            }
        }
        return ans;
    }
};