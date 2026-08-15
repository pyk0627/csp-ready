class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=accumulate(nums.begin(),nums.end(),0)-abs(target);
        if(sum<0||sum%2)
        {
            return 0;
        }
        int s=sum/2;//背包容量
        vector memo(nums.size()+1,vector<int>(s+1));
        memo[0][0]=1;
        for(int i=0;i<nums.size();i++)
        {
            for(int c=0;c<=s;c++)
            {
                if(c<nums[i])
                {
                    memo[i+1][c]=memo[i][c];
                }else
                {
                    memo[i+1][c]=memo[i][c]+memo[i][c-nums[i]];
                }
            }
        }
        return memo[nums.size()][s];
        // auto dfs=[&](this auto&& dfs,int i,int c)->int
        // {
        //     if(i<0)
        //     {
        //         return c==0;
        //     }
        //     if(memo[i][c]!=-1)
        //     {
        //         return memo[i][c];
        //     }
        //     if(c<nums[i])
        //     {
        //         return memo[i][c]=dfs(i-1,c);
        //     }
        //     return memo[i][c]=dfs(i-1,c)+dfs(i-1,c-nums[i]);
        // };
        // return dfs(nums.size()-1,s);
    }
};
/*
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=accumulate(nums.begin(),nums.end(),0)-abs(target);
        if(sum<0||sum%2)
        {
            return 0;
        }
        int s=sum/2;
        vector memo(nums.size()+1,vector<int>(s+1));
        memo[0][0]=1;
        for(int i=0;i<nums.size();i++)
        {
            for(int c=0;c<=s;c++)
            {
                if(c<nums[i])
                {
                    memo[i+1][c]=memo[i][c];
                }else
                {
                    memo[i+1][c]=memo[i][c]+memo[i][c-nums[i]];
                }
            }
        }
        return memo[nums.size()][s];
        // auto dfs=[&](this auto&& dfs,int i,int c)->int
        // {
        //     if(i<0)
        //     {
        //         return c==0;
        //     }
        //     if(memo[i][c]!=-1)
        //     {
        //         return memo[i][c];
        //     }
        //     if(c<nums[i])
        //     {
        //         return memo[i][c]=dfs(i-1,c);
        //     }
        //     return memo[i][c]=dfs(i-1,c)+dfs(i-1,c-nums[i]);
        // };
        // return dfs(nums.size()-1,s);
    }
};
这种方法里面：为什么这里                    memo[i+1][c]=memo[i][c]+memo[i][c-nums[i]];
是nums[i]而不是nums[i+1]这个memo[i+1]也让我挺疑惑的

你遇到的这个疑惑非常经典！这是动态规划（DP）中一个非常核心且常用的技巧：**“状态偏移一位”**。

为了让你彻底明白，我们先来解答你的两个疑问，然后再对比一下你注释掉的 DFS（记忆化搜索）和现在的 DP（递推）到底有什么区别。

---

### 疑问一：为什么状态数组是 `memo[i+1]`？让人很疑惑

**核心原因：为了能够优雅地表示“考虑前 0 个物品”的初始状态。**

在 0-1 背包问题中，我们的状态定义通常是：**“考虑前 $k$ 个物品时，凑出容量 $c$ 的方案数”**。
注意，这里的 $k$ 代表的是**物品的数量**，而不是数组的下标。

如果我们直接用 `memo[i][c]` 表示“考虑前 `i` 个物品”，那么“考虑前 0 个物品”的状态就应该是 `memo[0][c]`。
但是，在代码的循环中，我们需要遍历数组 `nums`，数组的下标是从 `0` 开始的。
如果 `i = 0`，它代表的是数组的第一个元素 `nums[0]`。这就产生了冲突：**`i=0` 到底是指“考虑前 0 个物品”，还是指“考虑第 1 个物品（下标为0）”？**

为了解决这个冲突，我们**把 DP 数组的第一维整体向后偏移一位**：
* 把 `memo` 的大小开成 `nums.size() + 1`。
* 规定：**`memo[k][c]` 表示“考虑数组中的前 `k` 个物品”**。

这样一来，逻辑就非常清晰了：
* **`k = 0`**：考虑前 0 个物品（什么都不选）。此时只有 `memo[0][0] = 1`（凑出容量0有1种方法），其余都是0。这就是代码中 `memo[0][0]=1` 的由来。
* **`k = 1`**：考虑前 1 个物品（即 `nums[0]`）。状态存在 `memo[1][...]` 中。
* **`k = 2`**：考虑前 2 个物品（即 `nums[0], nums[1]`）。状态存在 `memo[2][...]` 中。
* ...
* **`k = n`**：考虑前 `n` 个物品（即所有物品）。最终答案就是 `memo[n][s]`。

**回到你的循环：**
```cpp
for(int i=0; i<nums.size(); i++) // i 从 0 遍历到 n-1
```
当 `i = 0` 时，我们正在处理数组的第一个元素（也就是第 1 个物品）。处理完它之后，我们就变成了“考虑前 1 个物品”的状态，所以结果要写入 **`memo[0 + 1]`**，也就是 **`memo[1]`**。
以此类推，当循环变量为 `i` 时，我们正在处理第 `i+1` 个物品，所以状态要更新到 **`memo[i+1]`**。

---

### 疑问二：为什么是 `nums[i]` 而不是 `nums[i+1]`？

明白了上面的“偏移”原理，这个问题就迎刃而解了。

在你的外层循环中：
```cpp
for(int i=0; i<nums.size(); i++)
```
这里的变量 **`i` 就是数组的真实下标**。
* 当 `i=0` 时，当前物品就是 `nums[0]`。
* 当 `i=1` 时，当前物品就是 `nums[1]`。

所以，在状态转移方程中，我们需要的正是**当前正在处理的这个物品的体积**，当然要用 **`nums[i]`**。

如果你用 `nums[i+1]`：
1. **逻辑错误**：当 `i=0` 时，你处理的是第 1 个物品，但你却拿了第 2 个物品（`nums[1]`）的体积来算，完全错乱了。
2. **数组越界**：当 `i` 循环到最后一次，即 `i = nums.size() - 1` 时，如果你写 `nums[i+1]`，下标就变成了 `nums.size()`，这会导致**数组越界（Runtime Error）**，因为数组的最大合法下标是 `size() - 1`。

---

### 💡 终极对比：DFS（递归） vs DP（递推）

为了帮你彻底打通任督二脉，我们把注释掉的 DFS 和现在的 DP 放在一起对比，你会发现它们视角的差异：

| 对比维度 | DFS (记忆化搜索 / 自顶向下) | DP (递推 / 自底向上) |
| :--- | :--- | :--- |
| **状态定义** | `dfs(i, c)`：用下标 `0` 到 **`i`** 的物品凑容量 `c` | `memo[k][c]`：用前 **`k`** 个物品凑容量 `c` |
| **索引含义** | `i` 就是**数组的真实下标** | `k` 是**物品的数量** (`k = 真实下标 + 1`) |
| **初始/边界** | 递归到 `i < 0` (没有物品了)，看 `c` 是否为 0 | 初始化 `memo[0][0] = 1` (前0个物品凑0) |
| **遍历方向** | 从后往前推（从 `n-1` 递减到 `0`） | 从前往后推（从 `0` 递增到 `n-1`） |
| **当前物品** | `nums[i]` | `nums[i]` (此时 `i` 是外层循环变量) |
| **更新状态** | 更新 `memo[i][c]` | 更新 `memo[i+1][c]` (因为考虑了第 `i+1` 个物品) |
| **最终答案** | `dfs(n-1, s)` | `memo[n][s]` (即 `memo[nums.size()][s]`) |

### 总结
你写的这段 DP 代码逻辑是**完全正确**的！
* `memo[i+1]` 是因为 DP 数组的第一维代表 **“前几个物品”**，比数组真实下标大 1。
* `nums[i]` 是因为外层循环变量 `i` 就是**数组的真实下标**，代表当前正在考察的那个物品。

**附赠一个小优化（空间优化 / 滚动数组）：**
仔细观察你的状态转移方程：`memo[i+1][c]` 只依赖于上一行 `memo[i][c]` 和 `memo[i][c-nums[i]]`。
这意味着我们根本不需要一个二维数组，只需要一个**一维数组**，并且**内层循环倒序遍历**即可。这能让你的代码更简洁，内存占用更小：

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0) - abs(target);
        if (sum < 0 || sum % 2) return 0;
        
        int s = sum / 2;
        // 优化为一维数组，dp[c] 表示凑出容量 c 的方案数
        vector<int> dp(s + 1, 0);
        dp[0] = 1; // 初始状态：前0个物品凑出容量0有1种方法
        
        for (int num : nums) { // 遍历每个物品
            // 必须倒序遍历容量，防止同一个物品被重复使用
            for (int c = s; c >= num; c--) {
                dp[c] = dp[c] + dp[c - num];
            }
        }
        return dp[s];
    }
};
```
*/