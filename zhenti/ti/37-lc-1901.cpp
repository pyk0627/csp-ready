class Solution {
    int idxmax(vector<int>& a)
    {
        return ranges::max_element(a)-a.begin();
    }
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int left=-1;
        int right=mat.size()-1;
        while(left+1<right)
        {
            int mid=(right-left)/2+left;
            int idx=idxmax(mat[mid]);
            (mat[mid][idx]>mat[mid+1][idx]?right:left)=mid;
        }
        return {right,idxmax(mat[right])};
    }
};