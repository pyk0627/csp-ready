class Solution {
    vector<int> ans;
    vector<int> temp;
    int numArrows;
    vector<int> aliceArrows;
    int score=0;
    int t=0;
    void dfs(int depth)
    {
        if(depth==aliceArrows.size())
        {
            if(t>score)
            {
                ans=temp;
                score=t;
            }
            return;
        }

        // for(int i=0;i<=numArrows;i++)
        // {
        //     if(i>aliceArrows[depth]+1)
        //     {
        //         break;
        //     }
        //     temp.push_back(i);
        //     numArrows-=i;
        //     if(i>aliceArrows[depth])
        //     {
        //         t+=depth;
        //     }
        //     dfs(depth+1);
        //     if(i>aliceArrows[depth])
        //     {
        //         t-=depth;
        //     }
        //     temp.pop_back();
        //     numArrows+=i;
        // }

        temp.push_back(0);
        dfs(depth+1);
        temp.pop_back();

        if(numArrows>=aliceArrows[depth]+1)
        {
            temp.push_back(aliceArrows[depth]+1);
            numArrows-=(aliceArrows[depth]+1);
            t+=depth;
            dfs(depth+1);
            t-=depth;
            temp.pop_back();
            numArrows+=(aliceArrows[depth]+1);   
        }
    }
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        this->numArrows=numArrows;
        this->aliceArrows=aliceArrows;
        dfs(0);   
        int sum=accumulate(ans.begin(),ans.end(),0);
        ans[0]+=numArrows-sum;
        return ans;
    }
};
/*
c++中怎么快速复制一个vector容器？

#include <vector>

std::vector<int> a = {1, 2, 3, 4};

std::vector<int> b = a;   // 复制 a 到 b
std::vector<int> c(a);    // 也可以



怎么快速求和vector中的元素

#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};

    int sum = std::accumulate(v.begin(), v.end(), 0);

    std::cout << sum << std::endl; // 15
}

*/