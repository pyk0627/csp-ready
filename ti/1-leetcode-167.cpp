class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res(2);
        int l = 0;
        int r = numbers.size()-1;
        while(l<r)
        {
            int temp = numbers[l]+numbers[r];
            if(temp > target)
            {
                r--;
            }else if(temp < target)
            {
                l++;
            }else if( temp == target)
            {
                res[0] = l+1;
                res[1] = r+1;
                break;
            }
        }
        return res;
    }
};