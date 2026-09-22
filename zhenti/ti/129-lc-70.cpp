class Solution {
public:
    int climbStairs(int n) {
        vector<int> cache(n+5);
        auto dfs=[&](this auto&& dfs,int i)
        {
            if(i<0)
            {
                return 0;
            }
            if(i==0)
            {
                return 1;
            }
            if(cache[i]!=0)
            {
                return cache[i];
            }
            int res=dfs(i-1)+dfs(i-2);
            cache[i]=res;
            return res;
        };
        return dfs(n);
    }
};
/*

代码
测试结果
测试用例
测试用例
70. 爬楼梯
简单
相关标签
premium lock icon
相关企业
提示
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

 

示例 1：

输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：

输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶

这里的递推关系应该怎么写？class Solution {
public:
    int climbStairs(int n) {
        auto dfs=[&](this auto&& dfs,int i)
        {
            int res=0;
            if(i<=0)
            {
                return 0;
            }
            if(i==1)
            {
                return 1;
            }
            if(dfs(i-1))
            {
                res+=dfs(i-1);
            }
            if(dfs(i-2))
            {
                res+=dfs(i-2);
            }
            return res;
        };
        return dfs(n);
    }
};

递推关系本质是：

```cpp
f(n) = f(n - 1) + f(n - 2)
```

含义是：

- 要到达第 `n` 阶，最后一步可以是从第 `n - 1` 阶爬 1 阶上来；
- 或者从第 `n - 2` 阶爬 2 阶上来；
- 所以方法数等于两者相加。

---

## 1. 你的代码主要问题

你现在的写法：

```cpp
auto dfs=[&](this auto&& dfs,int i)
{
    int res=0;
    if(i<=0)
    {
        return 0;
    }
    if(i==1)
    {
        return 1;
    }
    if(dfs(i-1))
    {
        res+=dfs(i-1);
    }
    if(dfs(i-2))
    {
        res+=dfs(i-2);
    }
    return res;
};
```

问题有几个。

---

### 问题 1：边界条件错了

你写的是：

```cpp
if(i <= 0) return 0;
```

但是如果 `i == 0`，表示刚好爬完，不应该是 0 种方法，而应该是 1 种方法。

例如 `n = 2`：

```text
dfs(2)
= dfs(1) + dfs(0)
```

如果 `dfs(0) = 0`，那么结果就只有 `dfs(1) = 1`，少掉了直接一次爬 2 阶的方法。

所以应该写成：

```cpp
if (i == 0) return 1;
if (i < 0) return 0;
```

---

### 问题 2：不需要判断 `if(dfs(i - 1))`

你写：

```cpp
if(dfs(i-1))
{
    res += dfs(i-1);
}
```

这会导致两个问题：

1. `dfs(i - 1)` 被调用了两次；
2. 如果某个子问题结果真的是 0，你就不加，但这里本来也不需要靠返回值判断是否合法。

直接写：

```cpp
return dfs(i - 1) + dfs(i - 2);
```

即可。

---

## 2. 正确的递归递推关系

如果定义：

```cpp
dfs(i)
```

表示：

> 还剩 `i` 阶要爬，有多少种方法？

那么递推关系是：

```cpp
dfs(i) = dfs(i - 1) + dfs(i - 2)
```

边界条件是：

```cpp
dfs(0) = 1   // 刚好爬完，算一种方法
dfs(1) = 1   // 还剩一阶，只能爬一阶
```

完整递归可以写成：

```cpp
class Solution {
public:
    int climbStairs(int n) {
        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i == 0) return 1;
            if (i < 0) return 0;
            return dfs(i - 1) + dfs(i - 2);
        };

        return dfs(n);
    }
};
```

这个逻辑是对的，但是会超时，因为重复计算太多。

例如：

```text
dfs(5)
├── dfs(4)
│   ├── dfs(3)
│   │   ├── dfs(2)
│   │   └── dfs(1)
│   └── dfs(2)
└── dfs(3)
```

很多子问题被反复计算。

---

## 3. 加记忆化的递归写法

可以用一个数组保存已经算过的结果。

```cpp
class Solution {
public:
    int climbStairs(int n) {
        vector<int> memo(n + 1, -1);

        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i == 0) return 1;
            if (i < 0) return 0;

            if (memo[i] != -1) {
                return memo[i];
            }

            memo[i] = dfs(i - 1) + dfs(i - 2);
            return memo[i];
        };

        return dfs(n);
    }
};
```

这个递推关系还是：

```cpp
dfs(i) = dfs(i - 1) + dfs(i - 2)
```

只是把算过的 `dfs(i)` 存起来。

---

## 4. 动态规划写法

如果不用递归，可以直接递推。

定义：

```cpp
dp[i]
```

表示：

> 爬到第 `i` 阶有多少种方法。

那么：

```cpp
dp[i] = dp[i - 1] + dp[i - 2]
```

边界：

```cpp
dp[0] = 1
dp[1] = 1
```

代码：

```cpp
class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n + 1);

        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};
```

例如：

```text
dp[0] = 1
dp[1] = 1
dp[2] = dp[1] + dp[0] = 2
dp[3] = dp[2] + dp[1] = 3
dp[4] = dp[3] + dp[2] = 5
```

---

## 5. 最优的空间优化写法

因为每次只用到前两个状态，所以不需要整个数组。

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 1) {
            return 1;
        }

        int prev2 = 1; // dp[0]
        int prev1 = 1; // dp[1]

        for (int i = 2; i <= n; i++) {
            int cur = prev1 + prev2;
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};
```

这就是斐波那契数列的形式：

```text
1, 1, 2, 3, 5, 8, 13, ...
```

对应 `n = 0, 1, 2, 3, 4, 5, 6...`

---

## 6. 总结

递推关系写成：

```cpp
f(n) = f(n - 1) + f(n - 2)
```

边界写成：

```cpp
f(0) = 1
f(1) = 1
```

或者如果你习惯从 `1` 开始：

```cpp
f(1) = 1
f(2) = 2
f(n) = f(n - 1) + f(n - 2)
```

两种写法都可以。

你原来的代码最关键要改成：

```cpp
if (i == 0) return 1;
if (i < 0) return 0;

return dfs(i - 1) + dfs(i - 2);
```

而不是：

```cpp
if (i <= 0) return 0;
```
*/