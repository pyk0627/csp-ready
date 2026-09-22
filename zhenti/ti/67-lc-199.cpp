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
    vector<int> ans;
    void d(TreeNode* root,int depth)
    {
        if(root==nullptr)
        {
            return;
        }
        if(depth==ans.size())
        {
            ans.push_back(root->val);
        }
        d(root->right,depth+1);
        d(root->left,depth+1);
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        d(root,0);
        return ans;
    }
};
/*
为什么这段代码能解决题目？

这段代码用的是 **DFS（递归） + 优先遍历右子树** 的思路来得到二叉树的右视图。

---

## 1. 右视图是什么意思？

站在树的右边看，每一层只能看到最右边的节点。

例如：

```text
        1
       / \
      2   3
       \    \
        5    4
```

右边看到的是：

```text
1
3
4
```

也就是每一层最右边的节点。

---

## 2. 代码核心思路

```cpp
void d(TreeNode* root, int depth)
{
    if(root == nullptr)
    {
        return;
    }

    if(depth == ans.size())
    {
        ans.push_back(root->val);
    }

    d(root->right, depth + 1);
    d(root->left, depth + 1);
}
```

它递归遍历树，但是顺序是：

```cpp
先访问当前节点
再访问右子树
最后访问左子树
```

也就是：

```text
根 -> 右 -> 左
```

这很关键。

---

## 3. `depth == ans.size()` 的作用

`depth` 表示当前节点所在的层数，根节点是第 `0` 层。

`ans.size()` 表示目前已经记录了多少层的结果。

比如：

```cpp
if(depth == ans.size())
{
    ans.push_back(root->val);
}
```

意思是：

> 如果当前层第一次被访问到，就把当前节点的值加入答案。

因为每层只需要一个节点，也就是右视图能看到的节点。

---

## 4. 为什么第一次访问到某一层时，当前节点就是右视图节点？

因为递归顺序是：

```cpp
d(root->right, depth + 1);
d(root->left, depth + 1);
```

也就是说，对于同一层，代码会优先访问右边的节点。

所以当你第一次到达某一层时，访问到的一定是该层最右边的节点。

之后即使再访问该层的左边节点，由于 `ans.size()` 已经变大了，条件：

```cpp
depth == ans.size()
```

不再成立，所以不会加入答案。

---

## 5. 举个例子

输入：

```text
        1
       / \
      2   3
       \    \
        5    4
```

递归过程大致如下：

### 第一次进入根节点

```cpp
root = 1, depth = 0
ans.size() = 0
```

满足：

```cpp
depth == ans.size()
```

所以加入 `1`：

```cpp
ans = [1]
```

然后先访问右子树：

```cpp
d(root->right, 1)
```

---

### 进入节点 3

```cpp
root = 3, depth = 1
ans.size() = 1
```

满足：

```cpp
depth == ans.size()
```

加入 `3`：

```cpp
ans = [1, 3]
```

继续访问节点 3 的右子树：

```cpp
d(4, 2)
```

---

### 进入节点 4

```cpp
root = 4, depth = 2
ans.size() = 2
```

满足：

```cpp
depth == ans.size()
```

加入 `4`：

```cpp
ans = [1, 3, 4]
```

最终输出：

```cpp
[1, 3, 4]
```

这正是右视图。

---

## 6. 为什么后面的左侧节点不会加入？

假设某一层已经加入了最右边的节点，那么 `ans.size()` 就已经增加了。

例如现在：

```cpp
ans = [1, 3]
ans.size() = 2
```

如果后面访问到第 2 层的左边节点：

```cpp
depth = 2
```

此时：

```cpp
depth == ans.size()
```

本来成立，但注意如果该层已经加入过节点，`ans.size()` 已经是 `3` 了。

比如访问节点 5：

```cpp
depth = 2
ans.size() = 3
```

不满足：

```cpp
depth == ans.size()
```

所以不会加入。

这就保证了每一层最多只加入一个节点，而且加入的是最先访问到的右侧节点。

---

## 7. 整体执行逻辑

函数：

```cpp
vector<int> rightSideView(TreeNode* root) {
    d(root,0);
    return ans;
}
```

从根节点开始，深度为 `0`。

然后递归函数 `d` 会：

1. 遇到空节点直接返回；
2. 如果当前深度第一次出现，就记录当前节点；
3. 优先递归右子树；
4. 再递归左子树。

因此最终 `ans` 中保存的就是每一层最右边的节点。

---

## 8. 正确性总结

这段代码正确的关键在于两点：

### 第一点：先右后左

```cpp
d(root->right, depth + 1);
d(root->left, depth + 1);
```

保证每一层最先被访问到的是最右边的节点。

---

### 第二点：每层只记录第一个节点

```cpp
if(depth == ans.size())
{
    ans.push_back(root->val);
}
```

保证每一层只加入一个节点。

结合起来：

> 每层第一个被访问到的节点，就是右视图能看到的节点。

---

## 9. 复杂度

### 时间复杂度

每个节点最多访问一次：

```text
O(n)
```

其中 `n` 是节点数量。

---

### 空间复杂度

递归栈的深度等于树的高度。

最坏情况下树退化成链表：

```text
O(n)
```

平衡树时：

```text
O(log n)
```

答案数组最多保存每层一个节点，空间也是树的高度级别。

---

## 10. 一个小建议

你把 `ans` 定义成了成员变量：

```cpp
class Solution {
    vector<int> ans;
    ...
};
```

在 LeetCode 上通常每次测试会创建新的 `Solution` 对象，所以一般没问题。

但更稳妥的写法是每次调用时清空：

```cpp
vector<int> rightSideView(TreeNode* root) {
    ans.clear();
    d(root, 0);
    return ans;
}
```

或者把 `ans` 放在函数内部，通过参数传递：

```cpp
class Solution {
    void d(TreeNode* root, int depth, vector<int>& ans)
    {
        if(root == nullptr) return;

        if(depth == ans.size())
        {
            ans.push_back(root->val);
        }

        d(root->right, depth + 1, ans);
        d(root->left, depth + 1, ans);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        d(root, 0, ans);
        return ans;
    }
};
```

这样更安全。

---

一句话总结：

> 这段代码通过“优先访问右子树”的 DFS，保证每一层最先访问到的是最右侧节点；再用 `depth == ans.size()` 保证每层只记录第一个节点，因此得到的结果就是二叉树的右视图。
*/