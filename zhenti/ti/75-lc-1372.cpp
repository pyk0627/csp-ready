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
    int ans=0;
    void dfs(TreeNode* root,bool left=false,int len=0)
    {
        if(root==nullptr)
        {
            return;
        }
        ans=max(ans,len);
        if(left)
        {
            dfs(root->right,false,len+1);
            dfs(root->left,true,1);
        }else
        {
            dfs(root->left,true,len+1);
            dfs(root->right,false,1);
        }
    }
public:
    int longestZigZag(TreeNode* root,int f=0,int len=0) {
        dfs(root);
        return ans;
    }
};
/*
调用该文件夹中的skill，解决下面的问题
【新题目】
1372. 二叉树中的最长交错路径
中等
相关标签
premium lock icon
相关企业
提示
给你一棵以 root 为根的二叉树，二叉树中的交错路径定义如下：

选择二叉树中 任意 节点和一个方向（左或者右）。
如果前进方向为右，那么移动到当前节点的的右子节点，否则移动到它的左子节点。
改变前进方向：左变右或者右变左。
重复第二步和第三步，直到你在树中无法继续移动。
交错路径的长度定义为：访问过的节点数目 - 1（单个节点的路径长度为 0 ）。

请你返回给定树中最长 交错路径 的长度。

 

示例 1：



输入：root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
输出：3
解释：蓝色节点为树中最长交错路径（右 -> 左 -> 右）。
示例 2：



输入：root = [1,1,1,null,1,null,null,1,1,null,1]
输出：4
解释：蓝色节点为树中最长交错路径（左 -> 右 -> 左 -> 右）。
示例 3：

输入：root = [1]
输出：0
 

提示：

每棵树最多有 50000 个节点。
每个节点的值在 [1, 100] 之间。

【我的代码】
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
    int ans=0;
    int dfs(TreeNode* root,int f=0,int len=0)
    {
        if(root==nullptr)
        {
            ans=max(ans,len);
            return 0;
        }
        if(f!=1&&root->right!=nullptr)
        {
            ans=max(ans,len);
            return 1+longestZigZag(root->right,1,++len);
        }
        if(f!=-1&&root->left!=nullptr)
        {
            ans=max(ans,len);
            return 1+longestZigZag(root->left,-1,++len);
        }
        return len;
    }
public:
    int longestZigZag(TreeNode* root,int f=0,int len=0) {
        dfs(root);
        return ans;
    }
};/**
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
    int ans=0;
    int dfs(TreeNode* root,int f=0,int len=0)
    {
        if(root==nullptr)
        {
            ans=max(ans,len);
            return 0;
        }
        if(f!=1&&root->right!=nullptr)
        {
            ans=max(ans,len);
            return 1+longestZigZag(root->right,1,++len);
        }
        if(f!=-1&&root->left!=nullptr)
        {
            ans=max(ans,len);
            return 1+longestZigZag(root->left,-1,++len);
        }
        return len;
    }
public:
    int longestZigZag(TreeNode* root,int f=0,int len=0) {
        dfs(root);
        return ans;
    }
};

【我的卡点】
我现在彻底乱了，不知道该怎么办了


## 一、当前理解

- **题目**：找二叉树中最长的"交错路径"——每一步必须交替左/右，不能连续走同一边。长度 = 经过的节点数 - 1。可以从任意节点开始。
- **你的代码**：用了 `f` 标记上一步方向（1=右, -1=左, 0=起点），用 `len` 跟踪当前长度，`ans` 存全局最大。然后 `dfs` 里按 `f` 决定下一步走哪边。
- **你的卡点**："彻底乱了"。你的核心思路（方向标记 + 长度跟踪）其实方向对了，但实现上有几个致命问题让你越写越乱。

---

## 二、历史题关联判断

**判断结果：强相关** 🔥

| 历史文件 | 题目 | 相通点 |
|----------|------|--------|
| `63-lc-1448.cpp` | Count Good Nodes | **自顶向下**，把"路径上的历史信息"作为参数传下去 |
| `74-lc-1026.cpp` | Max Ancestor Diff | 你的 LC 1026 最终代码：`void dfs(root, maxnum, minnum)`，传两个参数、用全局 `ans` 收结果 |

你在 LC 1448 和 LC 1026 中都掌握了这个模式：**自顶向下带参递归 + 全局变量收答案**。LC 1372 完全就是这个模式的又一个变体。

---

## 三、提示式教学

### 🔑 递进提示

**提示 1（数据流向）：**

这道题和 LC 1026 一样，是 **自顶向下**。你要维护的信息是："上一步是从哪边来的"和"当前交错路径已经多长"。这两个信息必须作为参数从父节点传给子节点，不能靠返回值。

你已经在代码里用了 `f`（方向）和 `len`（长度），方向是对的。

---

**提示 2（关键 bug：`if-else` 让你只走了一条路）：**

看你的代码：

```cpp
if(f!=1 && root->right!=nullptr)   // 尝试往右
{
    return ...longestZigZag(root->right, 1, ++len);
}
if(f!=-1 && root->left!=nullptr)   // 尝试往左 —— 但这行永远走不到！
{
    return ...longestZigZag(root->left, -1, ++len);
}
```

第一个 `if` 里用了 `return`，所以第二个 `if` 永远不会执行。当 `f=0`（起点），你只尝试了往右走，从来没试过往左走。

**你应该同时对左右两边递归，像一个叉路口两个方向都要探。**

---

**提示 3（参数设计——简化你的想法）：**

你现在的逻辑太复杂了。换个角度想：

> 如果我上一步走的是左边，那继续交错就必须走右边。同时，我也可以选择从当前节点"重新开始"走左边（长度为 1）。

把这两个选择都交给递归：

```cpp
void dfs(TreeNode* node, bool wentLeft, int len)
```

- `wentLeft=true`：上一步走了左边 → 这一步想继续交错，**必须走右边**
- `wentLeft=false`：上一步走了右边 → 这一步想继续交错，**必须走左边**

到每个节点时，做什么？

1. `ans = max(ans, len)`
2. 继续交错：走 MUST 的方向，`len+1`
3. 重新开始：走"另一条"方向，`len=1`

**不需要 if-else 选一条路，两条都递归进去。**

---

### ❓ 思考题

1. 你的代码里 `++len` 作为参数传进去，如果有两次递归调用（左和右），第二次调用的 `len` 是加了几次？
2. 你的 `dfs` 和 `longestZigZag` 两个函数互相调用，为什么会出现这种混乱？你想让 `dfs` 做什么？`longestZigZag` 做什么？

---

## 四、我的代码问题

1. **`return` 断送了另一条路**：你在第一个 `if` 里 `return` 了，导致永远只探索一个方向。交错路径需要在**两个方向都尝试**并取最大。
2. **`++len` 是陷阱**：`++len` 会改变 `len` 本身的值。如果调用两次递归，第二次的 `len` 已经被第一次的 `++` 污染了。应该用 `len+1`。
3. **`dfs` 里调用 `longestZigZag`**：函数名不一致，说明你在反复改名字时把调用搞乱了。
4. **`if(f!=1)` 的逻辑是反直觉的**：`f=1` 表示"上一步走了右边"，那要交错就要走左边，但 `f!=1` 的检查是"只要上一步不是右，就可以走右"——这包括了 `f=-1`（上一步走左）的情况，意味着走完左又走右？不是的，`f=-1` 时 `f!=1` 为 true，所以又会往右走——但这其实是重新开始，不是继续交错。

    更清晰的思路是：**明确分"继续交错"和"重新开始"两种情况**。

---

## 五、下一步行动

**最小下一步：重写 DFS 函数。**

```cpp
void dfs(TreeNode* node, bool wentLeft, int len) {
    if (!node) return;
    ans = max(ans, len);
    if (wentLeft) {
        dfs(node->right, false, len + 1);  // 继续交错：必须走右
        dfs(node->left, true, 1);           // 重新开始：走左，长度重置为1
    } else {
        dfs(node->left, true, len + 1);     // 继续交错：必须走左
        dfs(node->right, false, 1);         // 重新开始：走右
    }
}
```

调用入口：
```cpp
dfs(root->left, true, 1);
dfs(root->right, false, 1);
```

注意：`wentLeft` 的意思是"上一步走了左边"，不是"这一步要往左走"。你试试这个版本，体会一下和你的代码有什么本质不同。
*/