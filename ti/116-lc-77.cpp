class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs=[&](this auto&& dfs,int i)->void
        {
            int d=k-path.size();
            if(d==0)
            {
                ans.emplace_back(path);
                return;
            }

            for(int j=i;j>=d;j--)
            {
                path.push_back(j);
                dfs(j-1);
                path.pop_back();
            }
        };

        dfs(n);
        return ans;
    }
};
/*
这段代码是解决 **“组合”问题**（例如 LeetCode 77. 组合）的经典**回溯算法（DFS）** 实现。它的目标是从 `1` 到 `n` 这 `n` 个数字中，找出所有由 `k` 个数字组成的组合。

这段代码有两个非常值得注意的地方：一是使用了**降序枚举 + 剪枝优化**来提高效率，二是使用了 **C++23 的新特性**来实现 Lambda 表达式的递归。

下面为你逐行详细解释：

### 1. 初始化变量
```cpp
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> path;
```
* **`ans`**：二维数组，用来存放所有最终符合条件的组合结果。
* **`path`**：一维数组，用来记录当前正在构建的组合（即递归路径上已经做出的选择）。

### 2. 定义递归函数 (Lambda 表达式)
```cpp
        // 枚举选哪个：在 1 到 i 中选一个数，加到 path 末尾
        auto dfs = [&](this auto&& dfs, int i) -> void {
```
* **`[&]`**：表示按引用捕获外部变量。这样 Lambda 内部就可以直接修改外部的 `ans`、`path`，并且能读取到 `k`。
* **`this auto&& dfs`**：⭐ **这是 C++23 引入的“显式对象参数”（Deducing `this`）特性**。
  * 在以前的 C++ 版本中，Lambda 表达式很难直接递归调用自己（通常需要借助 `std::function` 或者 Y 组合子）。
  * C++23 允许 Lambda 把自身的引用作为一个参数传进来，这里将其命名为 `dfs`。这样在函数内部就可以直接写 `dfs(...)` 来实现递归，既优雅又高效。
* **`int i`**：当前层可以枚举的最大数字边界（意味着只能在 `1` 到 `i` 的范围内选数）。
* **`-> void`**：声明这个 Lambda 表达式没有返回值。

### 3. 递归终止条件
```cpp
            int d = k - path.size(); // 还要选 d 个数
            if (d == 0) { // 选好了
                ans.emplace_back(path);
                return;
            }
```
* **`d`**：计算距离凑齐 `k` 个数还差几个（剩余深度 / 剩余需求）。
* **`if (d == 0)`**：如果已经选够了 `k` 个数，说明 `path` 里就是一个完整的组合。
* **`ans.emplace_back(path)`**：将当前的 `path` 拷贝一份放入结果集 `ans` 中（`emplace_back` 在 C++ 中通常比 `push_back` 构造更高效）。
* **`return`**：结束当前递归分支，往回退（回溯）。

### 4. 核心循环：枚举与剪枝
```cpp
            // 枚举的数不能太小，否则后面没有数可以选
            for (int j = i; j >= d; j--) {
```
* 这是整个代码最精妙的地方，包含了**倒序枚举**和**剪枝（Pruning）** 两个优化：
* **倒序枚举 (`j = i` 递减)**：我们人为规定组合内的数字必须是**降序**排列的（比如先选 4 再选 2，就不会再去选 2 再选 4）。这天然避免了重复组合的产生，不需要额外的去重逻辑。
* **剪枝优化 (`j >= d`)**：如果当前还需要选 `d` 个数，而剩下的可用数字（从 `j` 到 `1`）只有 `j` 个，那么必须满足 `j >= d` 才能凑齐。如果 `j < d`，剩下的数字根本不够选，直接终止循环。这能砍掉大量无效的搜索树分支，大幅提升运行速度。

### 5. 回溯三部曲：做选择、递归、撤销选择
```cpp
                path.push_back(j);
                dfs(j - 1);
                path.pop_back(); // 恢复现场
            }
```
* **`path.push_back(j)`**：**做出选择**。把当前枚举的数字 `j` 加入路径。
* **`dfs(j - 1)`**：**进入下一层递归**。因为规定了降序且数字不能重复使用，所以下一层能选的最大数字只能是 `j - 1`。
* **`path.pop_back()`**：**撤销选择（回溯）**。当从深层递归退回来后，必须把刚才加的 `j` 弹出去，恢复现场，以便在 `for` 循环的下一次迭代中尝试其他数字。

### 6. 启动递归并返回结果
```cpp
        };

        dfs(n); // 从 n 开始倒着枚举
        return ans;
    }
};
```
* **`dfs(n)`**：启动整个搜索过程。一开始我们可以选的最大数字是 `n`，所以传入 `n`。
* **`return ans`**：当所有可能的分支都搜索完毕后，返回收集了所有组合的二维数组。

---

### 💡 总结
这是一段非常标准且高质量的**回溯算法**代码。
1. **时间复杂度**：$O(\binom{n}{k} \times k)$，即组合的数量乘以每个组合的长度。
2. **空间复杂度**：$O(k)$，主要是递归调用栈的深度和 `path` 数组占用的空间（不考虑返回结果 `ans` 所占的空间）。
3. **技术亮点**：使用了 **C++23 特性**解决了 Lambda 递归的痛点，同时通过 `j >= d` 实现了**极限剪枝**，是面试或竞赛中非常拿得出手的写法。



                path.push_back(j);
                dfs(j - 1);
                path.pop_back(); // 恢复现场
            }
为什么这里又用了push_back而不是emplace_back?


这是一个非常敏锐且专业的问题！

简单来说：**对于 `int` 这样的基础数据类型，`push_back` 和 `emplace_back` 在性能和底层实现上没有任何区别。** 这里使用 `push_back` 更多是出于**传统编程习惯**和**代码可读性**的考虑。

为了让你彻底明白，我们需要从底层原理来对比这两个函数：

### 1. 两者的本质区别

*   **`push_back(value)`**：
    *   **语义**：把一个**已经存在**的对象，拷贝（或移动）到容器的末尾。
    *   **过程**：如果传入的是对象，它会先在外部构造好，然后再调用拷贝构造函数或移动构造函数放入容器中。
*   **`emplace_back(args...)`**：
    *   **语义**：在容器的末尾**原地构造**一个新对象。
    *   **过程**：它接受参数包，直接把这些参数转发给目标类型的构造函数，直接在容器分配的内存上“凭空”生成这个对象，省去了外部构造和拷贝/移动的开销。

### 2. 为什么 `path.push_back(j)` 不需要用 `emplace_back`？

在你的代码中，`path` 是 `vector<int>`，而 `j` 是一个 `int`（基础类型）。

*   **如果用 `path.push_back(j)`**：直接把 `int` 类型的变量 `j` 的值，按位复制到 `vector` 的尾部内存中。
*   **如果用 `path.emplace_back(j)`**：把参数 `j` 传给 `int` 的构造函数，在 `vector` 的尾部内存中“构造”一个 `int`。

对于 `int`、`float`、`char` 这种**基础标量类型**，它们没有复杂的构造函数，“复制一个值”和“原地构造一个值”在编译器看来是完全等价的操作。现代编译器（如 GCC, Clang）在开启优化后，这两行代码生成的**底层汇编指令是一模一样的**。

因此，对于基础类型，`emplace_back` 并没有性能优势，使用历史更悠久、语义更直白的 `push_back` 会让代码看起来更自然。

### 3. `emplace_back` 真正的威力在哪里？

`emplace_back` 的真正优势体现在**复杂对象（自定义类、结构体）** 上。

假设你有一个 `vector<pair<int, string>>`，你想插入一个 `{1, "hello"}`：
*   **传统 `push_back`**：你需要先在外面创建一个 `pair` 对象，然后再把它拷贝进 vector。
    ```cpp
    vec.push_back(make_pair(1, "hello")); // 产生临时对象并拷贝
    // 或者
    vec.push_back({1, "hello"}); 
    ```
*   **现代 `emplace_back`**：你可以直接把构造 `pair` 所需的参数传进去，它会在 vector 内部直接调用 `pair` 的构造函数，**零拷贝**。
    ```cpp
    vec.emplace_back(1, "hello"); // 完美转发参数，原地构造，性能最高
    ```

### 4. 顺带一提：`ans.emplace_back(path)` 写得对吗？

你注意到了上一行代码：
```cpp
ans.emplace_back(path);
```
`ans` 是 `vector<vector<int>>`，`path` 是一个 `vector<int>` 对象。

其实，在这里 `ans.emplace_back(path)` 和 `ans.push_back(path)` 的性能是**完全一样的**，因为它们传入的都是一个已经存在的 `vector` 对象，最终都会触发 `vector` 的**拷贝构造函数**，把 `path` 里的所有元素复制一份。

**如果想在这里真正发挥 `emplace_back` 或 `push_back` 的威力，应该配合 `std::move` 使用：**
```cpp
// 触发移动语义，直接把 path 的内部数组指针转移给 ans，无需复制元素，极快！
ans.emplace_back(std::move(path)); 
// 或者
ans.push_back(std::move(path));
```
*注：不过在你的代码逻辑中，由于 `path` 在后续还要被 `pop_back` 恢复现场继续使用，所以**不能**使用 `std::move`，必须老老实实地进行深拷贝。原作者在这里用 `emplace_back` 可能只是出于“现代 C++ 添加元素无脑用 emplace_back”的肌肉记忆。*

### 总结
*   **基础类型 (`int` 等)**：`push_back` 和 `emplace_back` 性能一样，用 `push_back` 更直观。
*   **复杂对象**：`emplace_back` 传入构造参数，原地构造，性能优于 `push_back`。
*   **已有对象**：无论是 `push_back` 还是 `emplace_back`，都是拷贝/移动，配合 `std::move` 才能达到最高效率。
*/