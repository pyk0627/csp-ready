class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int a=capacityA;
        int b=capacityB;
        int ans=0;
        int n=plants.size();
        int l=0;
        int r=n-1;
        capacityA-=plants[l];
        capacityB-=plants[r];
        l++;
        r--;
        while(l<r)
        {
            if(capacityA>=plants[l])
            {
                capacityA-=plants[l];
            }else
            {
                ans++;
                capacityA=a-plants[l];
            }

            if(capacityB>=plants[r])
            {
                capacityB-=plants[r];
            }else
            {
                ans++;
                capacityB=b-plants[r];
            }
            l++;
            r--;
        }
        if(l==r)
        {
            if(capacityA == capacityB)
            {
                if(capacityA>=plants[l])
                {
                    capacityA-=plants[l];
                }else
                {
                    ans++;
                    capacityA=a-plants[l];
                }
            }else
            {
                if(capacityA > capacityB)
                {
                    if(capacityA>=plants[l])
                    {
                        capacityA-=plants[l];
                    }else
                    {
                        ans++;
                        capacityA=a-plants[l];
                    }
                }else
                {
                    if(capacityB>=plants[r])
                    {
                        capacityB-=plants[r];
                    }else
                    {
                        ans++;
                        capacityB=b-plants[r];
                    }
                }
            }
        }
        return ans;
    }
};