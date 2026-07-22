class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size();
        int n=matrix[0].size();

        int left=-1;
        int right=m-1;
        while(left+1<right)
        {
            int mid=(left+right)/2;
            if(matrix[mid][n-1]>=target)
            {
                right=mid;
            }else
            {
                left=mid;
            }
        }

        int l=-1;
        int r=n;
        while(l+1<r)
        {
            int mid=(l+r)/2;
            if(matrix[right][mid]>=target)
            {
                r=mid;
            }else
            {
                l=mid;
            }
        }

        if(r<n && matrix[right][r]==target)
        {
            return true;
        }else
        {
            return false;
        }
    }
};