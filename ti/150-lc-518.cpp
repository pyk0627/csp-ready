class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<unsigned> dp(amount+1);
        dp[0]=1;
        for(auto x:coins)
        {
            for(int i=x;i<=amount;i++)
            {
                if(i-x>=0)
                {
                    dp[i]+=dp[i-x];
                }
            }
        }
        return dp[amount];
    }
};
/*
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // 和答案无关的转移可能会溢出，从而报错
        // 为了避免报错，使用 unsigned
        vector<unsigned> f(amount + 1);
        f[0] = 1;
        for (int x : coins) {
            for (int c = x; c <= amount; c++) {
                f[c] += f[c - x];
            }
        }
        return f[amount];
    }
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/coin-change-ii/solutions/2706227/shi-pin-wan-quan-bei-bao-cong-ji-yi-hua-o3ew0/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

这个用的是什么类型

这里使用的是 **`unsigned`** 类型（即 **无符号整型 `unsigned int`**）。

这是一种非常巧妙且高级的写法，利用了 C++ 语言标准中对“溢出”的不同规定来绕过 UBSan 报错，同时保证最终结果的正确性。

以下是详细的原理解析：

### 1. 为什么用 `unsigned` 就不会报错了？
*   **有符号整数（`int`）溢出**：在 C++ 标准中属于**未定义行为（Undefined Behavior, UB）**。一旦发生，UBSan（UndefinedBehaviorSanitizer）等内存/安全检查工具就会立刻拦截并报错。
*   **无符号整数（`unsigned`）溢出**：在 C++ 标准中是**明确定义的行为（Well-defined Behavior）**。当它超出最大范围时，会自动对 $2^{32}$ 取模（即发生“回绕”或“截断”，丢弃超出的高位）。因为这是合法行为，**UBSan 不会报错**。

### 2. 中间过程溢出了，为什么最终答案还是对的？
这是最核心的数学原理。
*   这道题的状态转移方程全都是纯加法：`f[c] = f[c] + f[c - x]`。
*   在模 $2^{32}$ 的意义下做加法，最终得到的结果等于 **真实答案对 $2^{32}$ 取模**。
*   题目保证了**最终答案一定能用 32 位有符号整数（`int`）表示**（即真实答案 $< 2^{31}-1$）。
*   既然真实答案小于 $2^{31}$，那么它对 $2^{32}$ 取模后的结果，**就是它本身**（没有发生改变）。
*   最后执行 `return f[amount];` 时，编译器会将 `unsigned int` 隐式转换回 `int`。因为此时它的二进制位模式正好对应那个小于 $2^{31}$ 的正数，所以转换后的 `int` 值是完全正确的。

### 3. 这种写法的优势
*   **比 `long long` 更省内存/更快**：`long long` 是 64 位的，而 `unsigned` 依然是 32 位的。在数组很大时，`unsigned` 占用的内存少一半，缓存命中率更高，运算也略微快一点。
*   **比“饱和加法”更简洁**：不需要像之前提到的那样写 `if (sum > INT_MAX)` 进行截断判断，代码极其干净，完全保留了 DP 最原始的简洁美感。

**总结**：灵茶山艾府的这种写法利用了 **“无符号整数溢出合法”** 以及 **“模加法同余”** 的特性，完美解决了中间状态溢出导致 UBSan 报错的问题，是这道题非常优雅的工程解法。
*/