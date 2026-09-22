class Solution {
public:
    int trap(vector<int>& height) {
        int ans=0;
        int left = 0;
        int right = height.size()-1;
        int pre_max = 0;
        int suf_max = 0;
        while(left<=right)
        {
            pre_max = max(height[left],pre_max);
            suf_max = max(height[right],suf_max);
            if(pre_max<suf_max)
            {
                ans+=pre_max-height[left];
                left++;
            }else
            {
                ans+=suf_max-height[right];
                right--;
            }
        }
        return ans;
    }
};