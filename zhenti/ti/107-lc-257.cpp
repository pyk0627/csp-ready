/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    vector<string> ans;
    string temp;
    void dfs(TreeNode* root)
    {
        if(root->left==nullptr && root->right==nullptr)
        {
            string str=to_string(root->val);
            temp+=str;
            ans.push_back(temp);
            temp.erase(temp.size()-str.size());
            return;
        }
        if(root==nullptr)
        {
            return;
        }
        if(root->left)
        {
            string str=to_string(root->val);
            temp+=str;
            temp+="->";
            dfs(root->left);
            temp.erase(temp.size()-str.size()-2);
        }
        if(root->right)
        {
            string str=to_string(root->val);
            temp+=str;
            temp+="->";
            dfs(root->right);
            temp.erase(temp.size()-str.size()-2);
        }
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
/*
c++中怎么把int类型的值转为char类型？怎么在string类型的字符串后面添加char类型的字符？

# C++ 中 int 转 char 及 string 添加 char

## 一、int 转 char

这里要区分**两种完全不同的需求**：

### 情况 1：int 是 ASCII 码，想转成对应字符

比如 `65` → `'A'`，`97` → `'a'`

```cpp
int n = 65;
char c = static_cast<char>(n);  // c = 'A'

// 或者简写
char c = (char)n;
```

### 情况 2：int 是一个数字（0~9），想转成对应的数字字符

比如 `5` → `'5'`，`0` → `'0'`

```cpp
int n = 5;
char c = '0' + n;   // c = '5'

// 等价写法
char c = n + '0';
```

> **原理**：字符 `'0'` 的 ASCII 码是 48，`'1'` 是 49，...，`'9'` 是 57。所以 `'0' + 5 = 53`，正好是字符 `'5'`。

### 情况 3：int 是一个多位数，想转成字符串

比如 `123` → `"123"`（这不是转成单个 char，而是转成 string）

```cpp
int n = 123;
std::string s = std::to_string(n);  // s = "123"
```

---

## 二、string 后面添加 char

有 **三种常用写法**，效果完全一样：

```cpp
std::string s = "Hello";
char c = '!';

// 方法 1：push_back（最常用，推荐）
s.push_back(c);       // s = "Hello!"

// 方法 2：+= 运算符
s += c;               // s = "Hello!"

// 方法 3：append
s.append(1, c);       // s = "Hello!"（追加 1 个字符 c）
```

### 三者的微小区别

| 方法 | 返回值 | 适用场景 |
| :--- | :--- | :--- |
| `s.push_back(c)` | `void` | **最推荐**，语义清晰 |
| `s += c` | `string&`（返回自身） | 可以链式调用：`s += 'a' += 'b'` |
| `s.append(1, c)` | `string&` | 需要追加多个相同字符时用：`s.append(5, 'x')` |

---

## 三、结合算法题的实战示例

结合你之前学的**回溯/分割回文串**，一个常见操作是"把数字转成字符拼接到字符串里"：

```cpp
// 把数字 0~9 拼接到字符串末尾
std::string s = "num: ";
int digit = 7;

s.push_back('0' + digit);  // s = "num: 7"

// 把 ASCII 码转成字符拼接
int ascii = 65;
s.push_back(static_cast<char>(ascii));  // s = "num: 7A"
```

---

## 一句话总结

| 需求 | 写法 |
| :--- | :--- |
| int（ASCII码）→ char | `char c = (char)n;` |
| int（0~9）→ 数字字符 | `char c = '0' + n;` |
| int → 字符串 | `std::string s = std::to_string(n);` |
| string 末尾加 char | `s.push_back(c);` |


c++中，string类型的字符串怎么删除指定长度的末尾子串

# C++ 中 string 删除末尾指定长度的子串

## 核心方法

假设要删除末尾 **k** 个字符：

### 方法 1：`erase()`（最常用）

```cpp
std::string s = "Hello, World!";
int k = 6;

s.erase(s.size() - k);       // 从位置 size()-k 开始，删除到末尾
// s = "Hello, "

// 等价写法（指定删除长度）
s.erase(s.size() - k, k);   // 从位置 size()-k 开始，删除 k 个字符
```

### 方法 2：`resize()`（最简洁）

```cpp
std::string s = "Hello, World!";
int k = 6;

s.resize(s.size() - k);     // 把长度缩短为 size()-k，多余的自动删掉
// s = "Hello, "
```

### 方法 3：`pop_back()`（只删 1 个字符）

```cpp
std::string s = "Hello!";

s.pop_back();               // 删除最后 1 个字符
// s = "Hello"
```

---

## 对比

| 方法 | 语法 | 适用场景 |
| :--- | :--- | :--- |
| `s.erase(s.size()-k)` | 删除末尾 k 个 | **通用**，删任意长度 |
| `s.resize(s.size()-k)` | 截断到指定长度 | **最简洁**，删任意长度 |
| `s.pop_back()` | 删除最后 1 个 | 只删 1 个字符时最方便 |

---

## 算法题中的典型用法（回溯撤销）

结合你之前学的回溯，最常见的场景是：**添加时 `push_back`，撤销时 `pop_back`**

```cpp
// 添加一个字符
path.push_back(c);

// 回溯时撤销（删除末尾 1 个字符）
path.pop_back();
```

如果一次添加了多个字符，回溯时需要删除多个：

```cpp
// 添加了一个长度为 len 的子串
path.append(sub);

// 回溯时撤销（删除末尾 len 个字符）
path.resize(path.size() - len);
// 或
path.erase(path.size() - len);
```

---

## ⚠️ 注意边界

```cpp
std::string s = "Hi";

// 如果要删除的长度 >= 字符串长度，直接清空
s.erase(0);         // s = ""
s.resize(0);        // s = ""
s.clear();          // s = ""（最直观的清空写法）
```

---

**一句话总结**：
- 删末尾 **1** 个字符 → `s.pop_back()`
- 删末尾 **k** 个字符 → `s.resize(s.size() - k)` 或 `s.erase(s.size() - k)`
- 清空整个字符串 → `s.clear()`


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 
class Solution {
    vector<string> ans;
    string temp;
    void dfs(TreeNode* root)
    {
        if(root->left==nullptr && root->right==nullptr)
        {
            ans.push_back(temp);
            return;
        }
        if(root->left)
        {
            char ch='0'+root->val;
            temp+ch;
            temp+="->";
            dfs(root->left);
            temp.erase(temp.size()-3);
        }
        if(root->right)
        {
            char ch='0'+root->val;
            temp+ch;
            temp+="->";
            dfs(root->right);
            temp.erase(temp.size()-3);
        }
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
terminate called after throwing an instance of 'std::out_of_range'
  what():  basic_string::erase: __pos (which is 18446744073709551614) > this->size() (which is 1)
怎么回事


# 错误原因分析

你的代码有 **多个问题** 叠加导致了这个崩溃。让我逐一指出：

---

## 🔴 错误 1：`temp+ch` 没有修改 temp

```cpp
temp+ch;   // ❌ 这只是计算了一个临时值，然后丢弃了！temp 根本没变！
```

应该写成：
```cpp
temp += ch;          // ✅ 追加到 temp
// 或
temp.push_back(ch);  // ✅
```

---

## 🔴 错误 2：`temp.erase(temp.size()-3)` 无符号下溢

`temp.size()` 返回的是 **无符号整数 `size_t`**。当 `temp` 长度 < 3 时：

```cpp
temp.size() - 3  
// 比如 size()=1 时：1-3 在无符号下 = 18446744073709551614（巨大的数）
```

这就是报错信息里 `__pos (which is 18446744073709551614)` 的来源。

---

## 🔴 错误 3：`char ch='0'+root->val` 只能处理 0~9

如果节点值是 `12`、`100`，这样转出来的字符是错的。应该用 `std::to_string()`。

---

## 🔴 错误 4：逻辑问题——叶子节点的值没被加入

到达叶子节点时直接 `ans.push_back(temp)`，但此时 `temp` 里**没有包含叶子节点自己的值**。

---

## ✅ 正确写法（推荐：传值，最简洁）

这道题最优雅的写法是**传值**（`string path` 按值传递），递归返回后自动恢复，**不需要手动回溯**：

```cpp
class Solution {
    vector<string> ans;
    
    void dfs(TreeNode* root, string path) {
        path += to_string(root->val);  // 把当前节点值加入路径
        
        // 到达叶子节点，收集答案
        if (root->left == nullptr && root->right == nullptr) {
            ans.push_back(path);
            return;
        }
        
        path += "->";  // 不是叶子，加箭头
        
        if (root->left)  dfs(root->left, path);
        if (root->right) dfs(root->right, path);
    }
    
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        dfs(root, "");
        return ans;
    }
};
```

> **为什么不需要回溯？** 因为 `string path` 是**值传递**，每次递归都会拷贝一份。左子树递归结束后，`path` 自动恢复到进入左子树之前的状态，右子树不受影响。

---

## ✅ 如果坚持用全局变量 + 回溯

```cpp
class Solution {
    vector<string> ans;
    string temp;
    
    void dfs(TreeNode* root) {
        string nodeStr = to_string(root->val);
        temp += nodeStr;  // 添加当前节点值
        
        if (root->left == nullptr && root->right == nullptr) {
            ans.push_back(temp);
            temp.erase(temp.size() - nodeStr.size());  // 撤销当前节点值
            return;
        }
        
        temp += "->";  // 添加箭头
        
        if (root->left)  dfs(root->left);
        if (root->right) dfs(root->right);
        
        // 撤销 "节点值" + "->"
        temp.erase(temp.size() - nodeStr.size() - 2);
    }
    
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
```

---

## 📋 总结：你的代码 vs 正确代码

| 问题 | 你的写法 | 正确写法 |
| :--- | :--- | :--- |
| 添加字符 | `temp+ch`（无效） | `temp += to_string(val)` |
| 多位数节点值 | `'0'+val`（只适用0~9） | `to_string(val)` |
| 回溯删除 | `erase(size()-3)`（会下溢） | `erase(size() - 实际长度)` |
| 叶子节点值 | 没加入 temp | 先加入再判断 |
| 是否需要手动回溯 | 需要（容易出错） | **传值则不需要** ✅ |

**一句话建议**：对于二叉树路径这类题，**直接传值 `string path`** 是最不容易写错的方式，不用操心回溯删除。


情况 3：int 是一个多位数，想转成字符串
比如 123 → "123"（这不是转成单个 char，而是转成 string）
cpp

12
如果是负数的情况怎么办？


# `std::to_string()` 自动处理负数

**不需要你做任何额外处理**，`std::to_string()` 会自动把负号加进去：

```cpp
#include <string>
#include <iostream>

int a = 123;
int b = -456;
int c = 0;

std::string s1 = std::to_string(a);   // "123"
std::string s2 = std::to_string(b);   // "-456"  ← 负号自动带上
std::string s3 = std::to_string(c);   // "0"

std::cout << s2 << std::endl;  // 输出: -456
```

---

## 原理

`std::to_string(int)` 内部等价于调用 `sprintf` 的 `%d` 格式，`%d` 本身就会处理负号。

---

## 如果你需要手动处理（不用 to_string）

```cpp
#include <sstream>

int n = -789;
std::stringstream ss;
ss << n;
std::string s = ss.str();  // "-789"
```

或者用 C 风格：
```cpp
char buf[20];
sprintf(buf, "%d", -789);   // buf = "-789"
std::string s(buf);
```

---

## 一句话总结

| 输入 | `std::to_string()` 输出 |
| :--- | :--- |
| `123` | `"123"` |
| `-456` | `"-456"` |
| `0` | `"0"` |

**直接用 `std::to_string()` 就行，负数、零、正数全都自动搞定，不用操心。**



*/