class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l=0;
        int maxh=0;
        auto it = max_element(piles.begin(),piles.end());
        if(it != piles.end())
        {
            maxh = *it;
        }
        int r = maxh;
        int mid;
        while(l+1 < r)
        {
            mid = (r-l)/2+l;
            long long t=0;
            for(auto x : piles)
            {
                //cout<<x<<endl;
                if(x<=mid)
                {
                    t++;
                }else
                {
                    t+=(x+mid-1)/mid;
                }
            }
            if(t>=h+1)
            {
                l=mid;
            }else
            {
                r=mid;
            }
        }
        return r;
    }
};
/*
1. 为什么是 t >= h + 1？
首先理清逻辑：

珂珂必须在 h 小时内吃完所有香蕉，所以合法的时间条件是 t <= h。
如果 t > h，说明吃的速度太慢了，需要加快速度。
因为时间 t 和 h 都是整数，所以 t > h 在整数域里完全等价于 t >= h + 1。
在二分查找中，我们需要根据中间值 mid 来决定下一步去左半边找还是右半边找：

如果 t >= h + 1（即 t > h）：说明当前速度 mid 太小了（不合法）。
我们要找一个更快的速度，所以必须向右查找。
在代码中，把左边界 l 移到 mid，即 l = mid。
如果 t <= h（即 else 分支）：说明当前速度 mid 足够快（合法）。
但题目要求的是“最小速度”，所以我们要尝试看有没有更小的速度也能满足条件，
因此向左查找。在代码中，把右边界 r 移到 mid，即 r = mid。
*/

/*
2. 为什么返回 r？
这取决于这段代码使用的二分查找边界定义。
观察循环条件 while(l + 1 < r)，这意味着循环结束时，一定有 l + 1 == r，
即 l 和 r 是相邻的两个整数。

在这个二分查找的过程中，l 和 r 维持了这样一个不变量（区间定义）：

[0, l] 范围内的速度，都是 “太慢了”（不合法，t > h） 的速度。
[r, maxh+1] 范围内的速度，都是 “足够快”（合法，t <= h） 的速度。
我们来看初始状态：

l = 0：速度为0肯定吃不完（吃不完意味着 t 会很大，肯定 > h），
所以 l=0 是合法的“慢速度”边界。
r = maxh + 1：maxh 是最大的一堆香蕉的数量。如果速度是 maxh，
每小时都能吃完任意一堆，总时间就是 piles.length。题目已知 piles.length <= h，
所以 maxh 绝对是一个合法的“快速度”。r 设为 maxh + 1 是为了作为一个安全的右边界。
在循环中：

每次 mid 太慢时，l = mid，保证了 l 及左边的都是慢速度。
每次 mid 足够快时，r = mid，保证了 r 及右边的都是快速度。
当循环结束时 (l + 1 == r)：

l 停在最后一个“太慢”的速度上。
r 停在第一个“足够快”的速度上。
题目要求的是能在 h 小时内吃完的最小速度，也就是第一个“足够快”的速度，所以正好是 r。
*/

/*
计算 t 的部分：
    if(x<=mid)
    { 
        t++; 
    } 
    else{ 
        t+=ceil((double)x/mid); 
    }

其实可以直接合并。
在数学中，对于正整数 a 和 b，ceil(a / b) 等于 (a + b - 1) / b。
所以你可以直接写成：
    long long t = 0;
    for (int x : piles)
    {
        t += (x + mid - 1) / mid;
    }
*/