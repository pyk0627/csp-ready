class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs=[&](this auto&& dfs,int n,int left_sum)->void
        {
            int d=k-path.size();

            if(left_sum<0 || left_sum>(n*2+n-d+1)*d/2)
            {
                return;
            }

            if(d==0)
            {
                ans.emplace_back(path);
                return;
            }

            for(int j=n;j>=d;j--)
            {
                path.push_back(j);
                dfs(j-1,left_sum-j);
                path.pop_back();
            }
        };

        dfs(9,n);
        return ans;
    }
};
/*
这段代码是解决 **LeetCode 216. 组合总和 III** 的经典回溯算法实现。

**题目要求**：找出所有相加之和为 `n` 的 `k` 个数的组合。组合中只允许含有 1 - 9 的正整数，且每种组合中不存在重复的数字。

这段代码在你上一题代码的基础上，增加了一个**极其精妙的数学剪枝**。下面为你逐行详细拆解：

### 1. 初始化与函数签名
```cpp
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](this auto&& dfs, int i, int left_sum) -> void {
```
* **`i`**：当前可以枚举的最大数字。因为题目限制在 1-9 之间，所以初始调用时传入 `9`。
* **`left_sum`**：距离目标和 `n` 还差多少（即剩余需要的和）。初始调用时传入 `n`。

### 2. 核心剪枝（全代码最精妙的地方）
```cpp
            int d = k - path.size(); // 还要选 d 个数
            
            // ⭐ 强力剪枝
            if (left_sum < 0 || left_sum > (i * 2 - d + 1) * d / 2) { 
                return;
            }
```
这里包含了两个极其重要的优化：
1. **`left_sum < 0`**：如果当前的和已经超过了目标值 `n`，因为所有的数字都是正整数，再往下选只会越来越大，不可能凑出 `n`，直接剪枝。
2. **`left_sum > (i * 2 - d + 1) * d / 2`（上限剪枝）**：
   * **逻辑**：当前还需要选 `d` 个数，且当前能选的最大数字是 `i`。为了让和尽可能大，我们**最多**只能选从 `i` 开始往下递减的 `d` 个最大数字，即：`i, i-1, i-2, ..., i-d+1`。
   * **公式推导**：这是一个首项为 `i`，末项为 `i-d+1`，项数为 `d` 的等差数列。根据等差数列求和公式 $S = \frac{(首项 + 末项) \times 项数}{2}$，可得最大可能和为：$\frac{(i + i - d + 1) \times d}{2}$。
   * **结论**：如果剩余需要的和 `left_sum` **大于**这个最大可能和，说明就算你把能选的最大的数全选了，也凑不够 `n`，直接剪枝！

**💡 隐藏的彩蛋（当 `d == 0` 时）：**
当 `d == 0`（已经选够了 `k` 个数）时，公式里的项数为 `0`，计算出的最大可能和为 `0`。
* 如果此时 `left_sum > 0`，就会触发 `left_sum > 0` 的剪枝，直接 `return`。
* 如果此时 `left_sum < 0`，触发 `< 0` 剪枝，直接 `return`。
* **只有当 `left_sum == 0` 时，才不会触发剪枝**。这意味着作者极其巧妙地把“检查 `left_sum` 是否等于 0”的逻辑，完美融合在了这一个剪枝条件里，省去了写 `if (d == 0 && left_sum == 0)` 的冗余判断！

### 3. 递归终止条件
```cpp
            if (d == 0) { // 找到一个合法组合
                ans.emplace_back(path);
                return;
            }
```
* 因为能走到这里的 `d == 0`，必然意味着 `left_sum == 0`（由上面的剪枝保证），所以直接把当前的 `path` 加入结果集 `ans` 即可。

### 4. 循环枚举与基础剪枝
```cpp
            // 枚举的数不能太小，否则后面没有数可以选
            for (int j = i; j >= d; j--) {
                path.push_back(j);
                dfs(j - 1, left_sum - j);
                path.pop_back(); // 恢复现场
            }
```
* **倒序枚举**：`j` 从 `i` 递减到 `d`。
* **基础剪枝 (`j >= d`)**：当前还需要选 `d` 个数，而 1 到 `j` 只有 `j` 个数可用。如果 `j < d`，剩下的数字根本不够选，直接终止循环。这和上一题的逻辑完全一致。
* **状态转移**：进入下一层时，最大可用数字变成 `j - 1`（保证数字不重复），剩余需要的和减去当前选中的 `j`（`left_sum - j`）。

### 5. 启动递归
```cpp
        };

        dfs(9, n); // 从 i=9 开始倒着枚举
        return ans;
    }
};
```
* 题目规定数字在 1-9 之间，所以初始状态最大数字是 `9`，目标和是 `n`。

---

### 🌟 总结
这段代码是回溯算法的**教科书级优化示范**。
它不仅有常规的回溯框架和基础剪枝（`j >= d`），还引入了**等差数列求和**来进行极限剪枝（`left_sum > 最大可能和`），并极其优雅地利用 `d=0` 时的数学特性，省去了显式的 `left_sum == 0` 判断。

**执行效率极高**，在 LeetCode 上运行时间通常可以达到 0ms，击败 100% 的用户。
*/