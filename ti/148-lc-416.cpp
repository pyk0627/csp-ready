class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int target=reduce(nums.begin(),nums.end());
        if(target%2)
        {
            return false;
        }
        target/=2;
        vector<bool> memo(target+1);
        memo[0]=true;
        for(auto num:nums)
        {
            for(int c=target;c>=num;c--)
            {
                memo[c]=memo[c]||memo[c-num];
                if(memo[target]==true)
                {
                    return true;
                }
            }
        }
        return memo[target];
        // auto dfs=[&](this auto&& dfs,int depth,int sum)->bool
        // {
        //     if(sum==target)
        //     {
        //         return true;
        //     }
        //     if(depth==nums.size())
        //     {
        //         return false;
        //     }

        //     return dfs(depth+1,sum)||dfs(depth+1,sum+nums[depth]);
        // };
        // return dfs(0,0);
    }
};
/*
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int target=reduce(nums.begin(),nums.end());
        if(target%2)
        {
            return false;
        }
        target/=2;
        vector<bool> memo(target+1);
        for(auto num:nums)
        {
            for(int c=target;c>=num;c--)
            {
                if()
                memo[c]=memo[c-1]||memo[c-num];
            }
        }
        // auto dfs=[&](this auto&& dfs,int depth,int sum)->bool
        // {
        //     if(sum==target)
        //     {
        //         return true;
        //     }
        //     if(depth==nums.size())
        //     {
        //         return false;
        //     }

        //     return dfs(depth+1,sum)||dfs(depth+1,sum+nums[depth]);
        // };
        // return dfs(0,0);
    }
};
这个递归怎么改成动态规划？

你的代码框架已经抓住了动态规划的核心（特别是**倒序遍历** `c=target; c>=num; c--` 这一步写得非常对，它保证了每个数字只被使用一次），只需要修正几个细节并理解状态转移的本质即可。

### 1. 你的代码需要修正的 3 个地方
1. **初始状态（Base Case）缺失**：需要设置 `memo[0] = true`。
2. **状态转移方程笔误**：你写的是 `memo[c] = memo[c-1] || ...`，应该是 `memo[c] = memo[c] || memo[c-num]`。
3. **缺少返回值**：最后需要返回 `memo[target]`。

### 2. 递归是如何变成一维 DP 的？
你注释掉的递归代码是**自顶向下**（从当前 `sum` 往目标 `target` 凑）；而标准的 0-1 背包 DP 是**自底向上**（从起点 `0` 往当前和 `c` 凑）。

我们可以这样映射：
*   **状态定义**：`dp[c]` 表示能否用已经遍历过的数字凑出和为 `c`。
*   **初始状态**：递归里终点是 `sum == target` 返回 `true`；而在 DP 中，起点是“什么都不选，和为 0 总是能凑出来的”，所以 **`dp[0] = true`**。
*   **状态转移**：
    *   递归中：`dfs(sum) = dfs(sum) || dfs(sum - num)`（要么不选当前数，要么选当前数）。
    *   DP 中：`dp[c] = dp[c] || dp[c - num]`。即：如果不选当前数字 `num`，看之前能不能凑出 `c`；如果选当前数字 `num`，看之前能不能凑出 `c - num`。
*   **为什么要倒序遍历？**
    如果正序遍历（`c=num; c<=target`），在计算 `dp[c]` 时，`dp[c-num]` 可能已经被当前的 `num` 更新过了，这会导致**同一个数字被重复使用**（变成了完全背包问题）。**倒序遍历**可以保证 `dp[c-num]` 拿到的是上一轮（即不包含当前数字）的旧状态，完美契合本题每个数字只能用一次的 0-1 背包模型。

---

### 3. 完整且修正后的代码

```cpp
#include <vector>
#include <numeric> // std::reduce 需要包含此头文件

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // C++17 的 std::reduce，等同于求和
        int sum = reduce(nums.begin(), nums.end());
        
        // 如果总和是奇数，绝对不可能平分为两个整数
        if (sum % 2 != 0) {
            return false;
        }
        int target = sum / 2;
        
        // dp[c] 表示能否凑出和为 c，初始全为 false
        vector<bool> dp(target + 1, false);
        
        // 【核心 Base Case】和为 0 总是可以凑出的（即什么都不选）
        dp[0] = true; 
        
        for (int num : nums) {
            // 【核心】必须倒序遍历，防止同一个数字被重复放入背包
            for (int c = target; c >= num; c--) {
                // 状态转移：不选当前数字(dp[c]) 或 选当前数字(dp[c - num])
                dp[c] = dp[c] || dp[c - num];
                
                // 【剪枝优化】如果已经能凑出 target，直接返回 true，无需继续计算
                if (dp[target]) {
                    return true;
                }
            }
        }
        
        return dp[target];
    }
};
```

### 总结
你原先写的递归其实带有一个隐式的备忘录（记忆化搜索）的雏形，把它“拍平”到数组上，就变成了上面这个一维数组的 DP 写法。这种**一维数组 + 倒序遍历**的写法是解决 **0-1 背包问题**（每个物品只能选一次）的最经典、空间复杂度最优（$O(\text{target})$）的模板，建议直接熟记。

DP 中：dp[c] = dp[c] || dp[c - num]。即：如果不选当前数字 num，看之前能不能凑出 c；如果选当前数字 num，看之前能不能凑出 c - num。
为什么右边这个dp[c]是之前的？

这是一个非常核心且关键的问题！理解这一点，就彻底搞懂了 **0-1 背包问题** 为什么要用“倒序遍历”来优化空间。

简单来说：**因为在倒序遍历中，当你读取等号右边的 `dp[c]` 时，这个位置还没有被当前这一轮的循环“污染”过，所以它里面装的还是上一轮（上一个数字）留下来的旧值。**

为了让你彻底弄懂，我们引入**二维数组**的概念，并对比**倒序**和**正序**的区别。

### 1. 本质：二维 DP 的降维
如果我们不优化空间，使用标准的二维数组，状态转移方程是这样的：
`dp[i][c] = dp[i-1][c] || dp[i-1][c - num]`
*   `i` 代表当前考虑第 `i` 个数字。
*   `dp[i-1][...]` 代表**上一轮**（不包含当前数字）的状态。

为了节省内存，我们把第一维（`i`）去掉了，变成了一维数组 `dp[c]`。
*   等号左边的 `dp[c]` 代表 **`dp[i][c]`（当前新状态）**。
*   等号右边的 `dp[c]` 和 `dp[c-num]` 必须代表 **`dp[i-1][...]`（上一轮旧状态）**。

**怎么保证右边读到的是旧状态呢？这就取决于你的遍历顺序。**

---

### 2. 实例推演：为什么必须是倒序？

假设 `nums = [2]`, `target = 4`。初始状态 `dp = [T, F, F, F, F]`（只有 `dp[0]` 是 True）。

#### ❌ 如果用正序遍历（`c` 从 `num` 到 `target`）
当处理数字 `num = 2` 时：
*   `c = 2`: `dp[2] = dp[2] || dp[0]` ➡️ `F || T` ➡️ **`dp[2] 变成 True`**。
*   `c = 3`: `dp[3] = dp[3] || dp[1]` ➡️ `F || F` ➡️ `dp[3] 还是 False`。
*   `c = 4`: `dp[4] = dp[4] || dp[2]` ➡️ **注意！这里的 `dp[2]` 刚刚已经被改成了 True！**
    *   结果：`dp[4]` 变成了 True。
*   **错误后果**：你只用了一个数字 `2`，却凑出了和为 `4`（相当于 `2 + 2 = 4`）。当前的数字被**重复使用了**！这就变成了“完全背包”问题。

#### ✅ 如果用倒序遍历（`c` 从 `target` 到 `num`）—— 你的代码写法
当处理数字 `num = 2` 时：
*   `c = 4`: `dp[4] = dp[4](旧值 F) || dp[2](旧值 F)` ➡️ `False`。
*   `c = 3`: `dp[3] = dp[3](旧值 F) || dp[1](旧值 F)` ➡️ `False`。
*   `c = 2`: `dp[2] = dp[2](旧值 F) || dp[0](旧值 T)` ➡️ **`dp[2] 变成 True`**。
*   **完美结果**：当我们要计算 `dp[4]` 时，由于循环是从大到小，`dp[2]` 还没走到，所以它拿到的绝对是上一轮干干净净的“旧值”。这就保证了每个数字只被放进背包**一次**。

---

### 总结
*   **等号右边的 `dp[c]` 代表“不选当前数字”**：因为你还没走到 `c` 这个索引去修改它，所以它保留着上一轮的旧结果（即不包含当前 `num` 时的状态）。
*   **等号右边的 `dp[c - num]` 代表“选当前数字”**：因为 `c - num` 比 `c` 小，倒序遍历同样还没走到那里，所以它也是上一轮的旧结果。
*   **等号左边的 `dp[c]` 代表“更新后的状态”**：计算完成后，把新结果覆盖写入这个位置，供下一个外层循环（下一个数字）作为“旧值”使用。
*/