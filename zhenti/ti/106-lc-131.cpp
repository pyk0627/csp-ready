class Solution {
    string s;
    vector<vector<string>> ans;
    vector<string> temp;
    void dfs(int depth)
    {
        if(depth==s.size())
        {
            ans.push_back(temp);
            return;
        }
        for(int j=1;j<=s.size()-depth;j++)
        {
            string str=s.substr(depth,j);
            string str1=str;
            reverse(str1.begin(),str1.end());
            if(str==str1)
            {
                temp.push_back(str);
                dfs(depth+j);
                temp.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        this->s=s;
        dfs(0);
        return ans;
    }
};
/*
c++中怎么快速获得string任意位置的子串？

在 C++ 中，获取字符串任意位置的子串主要有三种方式。根据你是**做常规开发**还是**刷算法题**，推荐的用法会有所不同。

以下是按“从常用到极致性能”排序的三种方法：

### 1. 最常规的方法：`std::string::substr` (深拷贝)
这是 C++ 标准库提供的方法，使用最简单，但**会产生内存分配和拷贝**。

* **语法**：`s.substr(起始位置 pos, 截取长度 count)`
* **特点**：会生成一个全新的 `std::string` 对象。如果 `count` 不写，默认截取到字符串末尾。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "Hello, World!";
    
    // 截取 "World" (从索引 7 开始，截取 5 个字符)
    std::string sub1 = s.substr(7, 5); 
    
    // 截取 "World!" (从索引 7 开始，一直截取末尾)
    std::string sub2 = s.substr(7); 
    
    std::cout << sub1 << "\n"; // 输出: World
    return 0;
}
```
⚠️ **注意**：如果 `pos` 大于字符串的长度，会抛出 `std::out_of_range` 异常。

---

### 2. 现代 C++ 的高效方法：`std::string_view` (零拷贝 / C++17 引入)
如果你使用的是 C++17 或更高版本，且**只需要读取子串而不需要修改它**，强烈建议使用 `std::string_view`。

* **特点**：它底层只保存了一个**指针**和一个**长度**，**不会分配新内存，也不会拷贝字符**，速度极快（时间复杂度 $O(1)$）。
* **适用场景**：高频的字符串切片、字符串解析、哈希计算等。

```cpp
#include <iostream>
#include <string>
#include <string_view> // 必须包含此头文件

int main() {
    std::string s = "Hello, World!";
    std::string_view sv = s; // 将 string 转换为 string_view

    // 零拷贝截取 "World"
    std::string_view sub = sv.substr(7, 5); 
    
    std::cout << sub << "\n"; // 输出: World
    return 0;
}
```

---

### 3. 算法题的终极优化：根本不截取（双指针/索引法）
结合你上一问的**回溯算法题**，如果你在算法题中频繁使用 `s.substr()`，会导致大量的内存分配（`new/delete`），从而让代码运行变慢，甚至超时（TLE）。

**在算法题中，获取子串最高效的方式是：不获取子串，而是传递“左右边界索引”。**

#### ❌ 糟糕的写法（频繁拷贝）：
```cpp
// 每次判断回文都要 substr 拷贝一次，非常慢！
string sub = s.substr(i, j - i + 1);
if (isPalindrome(sub)) { ... }
```

#### ✅ 极致的写法（传递索引）：
直接让函数接收原字符串的引用以及 `left` 和 `right` 索引，在原字符串上直接比对，**零内存分配，零拷贝**。
```cpp
// 只传索引，时间复杂度 O(N)，空间复杂度 O(1)
bool isPalindrome(const string& s, int left, int right) {
    while (left < right) {
        if (s[left++] != s[right--]) {
            return false;
        }
    }
    return true;
}

// 调用时：
if (isPalindrome(s, i, j)) { ... }
```
*(注：只有当最终要把合法的子串存入答案数组 `ans.push_back(s.substr(i, j - i + 1))` 时，才去执行一次真正的 `substr` 拷贝。)*

---

### 💡 总结与建议

| 方法 | 性能 | 内存分配 | 适用场景 |
| :--- | :--- | :--- | :--- |
| **`s.substr(pos, len)`** | 较慢 | **有** (深拷贝) | 日常开发，需要把子串存起来或修改它。 |
| **`string_view::substr`** | 极快 | **无** (仅拷贝指针) | C++17 及以上，高频切片，只读操作（如正则匹配、日志解析）。 |
| **传递 `left, right` 索引** | **最快** | **无** | **刷算法题**，特别是在回溯、动态规划中频繁判断子串属性时。 |


c++中怎么快速反转字符串？

# C++ 中快速反转字符串

## 方法一：`std::reverse`（最推荐，一行搞定）

这是 C++ 标准库提供的算法，**原地反转**，不产生新字符串。

```cpp
#include <string>
#include <algorithm> // 必须包含

std::string s = "Hello";
std::reverse(s.begin(), s.end());
// s 变成 "olleH"
```

也可以只反转**一部分**：
```cpp
std::string s = "Hello, World!";
std::reverse(s.begin() + 7, s.begin() + 12);
// s 变成 "Hello, dlroW!"  （只反转了 "World"）
```

---

## 方法二：双指针手动交换（算法题常考）

面试中如果让你手写，用这个方法：

```cpp
void reverseString(string& s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        std::swap(s[left], s[right]);
        left++;
        right--;
    }
}
```

**特点**：原地操作，时间 $O(n)$，空间 $O(1)$。

---

## 方法三：生成新字符串（逆序迭代器）

如果你不想修改原字符串，而是想要一个**反转后的副本**：

```cpp
std::string s = "Hello";
std::string reversed(s.rbegin(), s.rend()); // 用逆序迭代器构造
// reversed = "olleH"，s 不变
```

---

## 对比总结

| 方法 | 是否原地 | 是否产生新内存 | 适用场景 |
| :--- | :---: | :---: | :--- |
| `std::reverse(s.begin(), s.end())` | ✅ 原地 | ❌ 不分配 | **日常开发首选** |
| 双指针 `swap` | ✅ 原地 | ❌ 不分配 | 面试手写、理解原理 |
| `string(s.rbegin(), s.rend())` | ❌ 新建 | ✅ 分配 | 需要保留原字符串时 |

---

## ⚠️ 算法题中的注意事项

在算法题（如判断回文）中，**通常不要真的去反转字符串**，因为：
- 反转是 $O(n)$ 时间 + 可能 $O(n)$ 空间。
- 直接用**双指针从两端向中间比较**即可，无需反转。

```cpp
// ❌ 不推荐：反转后比较（浪费空间）
string rev = s;
reverse(rev.begin(), rev.end());
return s == rev;

// ✅ 推荐：双指针直接判断
bool isPalindrome(const string& s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}
```

**一句话总结**：日常用 `std::reverse`，面试写双指针，判断回文别反转直接比。


c++怎么快速判断两个字符串是否相等？

# C++ 中快速判断两个字符串是否相等

## 方法一：`==` 运算符（最推荐，一行搞定）

`std::string` 重载了 `==` 运算符，内部实现非常高效。

```cpp
std::string a = "Hello";
std::string b = "Hello";

if (a == b) {
    std::cout << "相等\n";
} else {
    std::cout << "不相等\n";
}
```

### 内部原理（为什么它已经很快了）：
```cpp
// 伪代码：std::string::operator== 的实现
bool operator==(const string& lhs, const string& rhs) {
    // 1. 先比较长度，长度不同直接返回 false（O(1) 快速剪枝）
    if (lhs.size() != rhs.size()) return false;
    
    // 2. 长度相同，逐字符比较（O(n)）
    return std::char_traits<char>::compare(lhs.data(), rhs.data(), lhs.size()) == 0;
}
```

---

## 方法二：`compare()` 函数

如果你需要知道**字典序关系**（大于、小于、等于），用 `compare`：

```cpp
std::string a = "apple";
std::string b = "banana";

int result = a.compare(b);
// result < 0: a 字典序小于 b
// result == 0: a 等于 b
// result > 0: a 字典序大于 b

if (result == 0) {
    std::cout << "相等\n";
}
```

---

## 方法三：C 风格 `strcmp()`（不推荐，但有时会遇到）

```cpp
#include <cstring>

const char* a = "Hello";
const char* b = "Hello";

if (strcmp(a, b) == 0) {
    std::cout << "相等\n";
}
```

⚠️ **注意**：`strcmp` 只能用于 `const char*`，不能直接用于 `std::string`。如果用 `std::string`，需要调用 `.c_str()`。

---

## 方法四：`std::string_view`（C++17，零拷贝比较）

如果你有两个字符串的**视图**（不拥有数据），可以直接比较：

```cpp
#include <string_view>

std::string_view a = "Hello";
std::string_view b = "Hello";

if (a == b) {
    std::cout << "相等\n";
}
```

---

## 性能对比与总结

| 方法 | 时间复杂度 | 是否分配内存 | 适用场景 |
| :--- | :---: | :---: | :--- |
| `a == b` | $O(1)$ 或 $O(n)$ | ❌ 不分配 | **日常开发首选** |
| `a.compare(b)` | $O(1)$ 或 $O(n)$ | ❌ 不分配 | 需要知道字典序关系 |
| `strcmp(a, b)` | $O(n)$ | ❌ 不分配 | C 风格字符串 |
| `string_view` | $O(1)$ 或 $O(n)$ | ❌ 不分配 | C++17，零拷贝场景 |

---

## ⚠️ 算法题中的注意事项

### 1. 频繁比较大量字符串？考虑哈希
如果你在算法题中需要**反复比较**大量字符串是否相等（比如判断单词是否出现过），用 `std::unordered_set` 或 `std::unordered_map` 更快：

```cpp
#include <unordered_set>

std::unordered_set<std::string> seen;
seen.insert("Hello");
seen.insert("World");

if (seen.count("Hello")) {
    std::cout << "找到了\n"; // O(1) 平均时间
}
```

### 2. 只关心是否相等，不需要知道顺序？
直接 `==` 即可，不要自己写循环比较。

### 3. 避免不必要的拷贝
```cpp
// ❌ 不推荐：传值会拷贝字符串
bool isEqual(std::string a, std::string b) {
    return a == b;
}

// ✅ 推荐：传 const 引用，零拷贝
bool isEqual(const std::string& a, const std::string& b) {
    return a == b;
}
```

---

**一句话总结**：日常直接用 `a == b`，它已经很快了（先比长度，再比内容）。需要字典序用 `compare`，频繁查找用哈希表。



*/