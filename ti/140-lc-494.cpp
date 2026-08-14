class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=accumulate(nums.begin(),nums.end(),0)-abs(target);
        if(sum<0||sum%2)
        {
            return 0;
        }
        int s=sum/2;
        vector memo(nums.size(),vector<int>(s+1,-1));
        auto dfs=[&](this auto&& dfs,int i,int c)->int
        {
            if(i<0)
            {
                return c==0;
            }
            if(memo[i][c]!=-1)
            {
                return memo[i][c];
            }
            if(c<nums[i])
            {
                return memo[i][c]=dfs(i-1,c);
            }
            return memo[i][c]=dfs(i-1,c)+dfs(i-1,c-nums[i]);
        };
        return dfs(nums.size()-1,s);
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
        vector memo(nums.size(),vector<int>(s+1,-1));
        auto dfs=[&](this auto&& dfs,int i,int c)->int
        {
            if(i<0)
            {
                return c==0;
            }
            if(memo[i][c]!=-1)
            {
                return memo[i][c];
            }
            if(c<nums[i])
            {
                return memo[i][c]=dfs(i-1,c);
            }
            return memo[i][c]=max(dfs(i-1,c),dfs(i-1,c-nums[i]));
        };
        return dfs(nums.size()-1,s);
    }
};哪里有问题

这段代码主要存在**两个问题**：一个是**致命的算法逻辑错误**，另一个是**可能导致编译错误的 C++ 语法兼容性问题**。

下面为你详细拆解：

### 1. 致命逻辑错误：使用了 `max` 而不是 `+`

**错误代码：**
```cpp
return memo[i][c]=max(dfs(i-1,c),dfs(i-1,c-nums[i]));
```

**原因分析：**
这道题是一个**计数问题**（求有多少种不同的表达式数目），而不是**最优化问题**（求最大价值/最小代价）。
* 在经典的 0-1 背包“求最大价值”问题中，状态转移方程确实是 `max(不选, 选)`。
* 但在“求方案总数”问题中，状态转移方程必须是**相加**：`总方案数 = 不选当前物品的方案数 + 选当前物品的方案数`。

**直观的例子：**
假设 `nums = [1, 1, 1, 1, 1]`, `target = 3`。我们需要凑出容量为 `1` 的背包（选1个1）。
* 显然有 **5 种** 选法（选第1个、选第2个...）。
* 如果你用 `max`，程序会发现“选”的方案数是 1，“不选”的方案数也是 1（或者0），`max(1, 1)` 结果永远是 **1**。这就导致你漏算了剩下的 4 种情况，最终答案会输出 1，而正确答案是 5。

**修改方法：**
将 `max` 改为 `+`：
```cpp
return memo[i][c] = dfs(i - 1, c) + dfs(i - 1, c - nums[i]);
```

---

### 2. 语法兼容性问题：`this auto&& dfs` 是 C++23 特性

**错误代码：**
```cpp
auto dfs=[&](this auto&& dfs,int i,int c)->int
```

**原因分析：**
`this auto&&` （显式对象参数 / Deducing this）是 **C++23** 标准才引入的新特性。
目前 LeetCode 的 C++ 编译器环境主要默认使用 **C++17** 或 **C++20**。如果你直接提交这段代码，大概率会报**编译错误 (Compile Error)**，提示编译器不认识这种语法。

**修改方法（兼容 C++17/20 的标准写法）：**
在 C++17/20 中，Lambda 表达式递归的标准做法是**将 Lambda 自身作为第一个参数传进去**：
```cpp
// 1. 定义时，第一个参数是 auto&& self
auto dfs = [&](auto&& self, int i, int c) -> int {
    // ...
    // 2. 递归调用时，调用 self
    return memo[i][c] = self(i - 1, c) + self(i - 1, c - nums[i]);
};
// 3. 第一次触发时，把 dfs 自己传进去
return dfs(dfs, nums.size() - 1, s);
```

---

### 🌟 最终修改后的正确代码

结合以上两点，修改后的完美代码如下（你可以直接复制去 LeetCode 提交）：

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0) - abs(target);
        if (sum < 0 || sum % 2) {
            return 0;
        }
        
        int s = sum / 2;
        // 使用 CTAD 自动推导类型，C++17 支持
        vector memo(nums.size(), vector<int>(s + 1, -1)); 
        
        // 兼容 C++17/20 的递归 Lambda 写法
        auto dfs = [&](auto&& self, int i, int c) -> int {
            if (i < 0) {
                return c == 0;
            }
            if (memo[i][c] != -1) {
                return memo[i][c];
            }
            if (c < nums[i]) {
                return memo[i][c] = self(i - 1, c); // 只能不选
            }
            // 【核心修改】：求方案数，必须用 + 号
            return memo[i][c] = self(i - 1, c) + self(i - 1, c - nums[i]); 
        };

        // 第一次调用时，把 dfs 自身作为第一个参数传入
        return dfs(dfs, nums.size() - 1, s);
    }
};
```

**总结：**
刷题时遇到“求方案数/组合数”的 DP 或记忆化搜索，**永远记住状态转移是加法 (`+`)**；只有遇到“求最大/最小价值”时，才用 `max` 或 `min`。
*/