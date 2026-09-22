class Solution {
public:
    int hIndex(vector<int>& citations) {
        int l=0;
        int r=citations.size()+1;
        /*
        为什么 r = citations.size() + 1 要加一？
        核心原因：搜索区间要包含 h 指数的最大可能值 n
        h 指数的取值范围是 [0, n]，其中 n = citations.size()。

        因为 h 指数最大只能是 n
        （你不可能有超过 n 篇论文，所以不可能有 n+1 篇论文都被引用 ≥ n+1 次）。
        */
        while(l+1<r)
        {
            int mid=(r-l)/2+l;
            int t=0;
            for(auto& x : citations)
            {
                if(x>=mid)
                {
                    t++;
                }
            }
            if(t>=mid)
            {
                l=mid;
            }else
            {
                r=mid;
            }
            /*
            用的是开区间二分（红蓝染色法），其不变量为：

            l 始终指向"可行"的值（即 h 指数 ≥ l 一定成立）
            r 始终指向"不可行"的值（即 h 指数 < r 一定成立）
            真正的答案藏在开区间 (l, r) 中
            所以初始化时：

            l = 0：h 指数 ≥ 0 恒成立 ✅ 可行
            r = n + 1：h 指数 < n+1 恒成立 ❌ 不可行（h 最大就是 n）
            */
            /*
            循环结束时
            while (l + 1 < r) 退出时 l + 1 == r，即 l 和 r 紧邻：

            l 是最后一个蓝色（最大可行值）→ 答案
            r 是第一个红色（最小不可行值）
            */
        }
        return l;
    }
};