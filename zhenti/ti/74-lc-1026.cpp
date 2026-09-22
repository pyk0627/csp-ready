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
    void dfs(TreeNode* root,int maxnum=-1,int minnum=100005)
    {
        if(root==nullptr)
        {
            return;
        }
        ans=max(ans,maxnum-root->val);
        ans=max(ans,root->val-minnum);
        if(root->val>maxnum)
        {
            maxnum=root->val;
        }
        if(root->val<minnum)
        {
            minnum=root->val;
        }
        dfs(root->left,maxnum,minnum);
        dfs(root->right,maxnum,minnum);
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        dfs(root);
        return ans;
    }
};

/*
调用当前文件夹中的skill,
【新题目】
1026. 节点与其祖先之间的最大差值
中等
相关标签
premium lock icon
相关企业
提示
给定二叉树的根节点 root，找出存在于 不同 节点 A 和 B 之间的最大值 V，其中 V = |A.val - B.val|，且 A 是 B 的祖先。

（如果 A 的任何子节点之一为 B，或者 A 的任何子节点是 B 的祖先，那么我们认为 A 是 B 的祖先）

 

示例 1：



输入：root = [8,3,10,1,6,null,14,null,null,4,7,13]
输出：7
解释： 
我们有大量的节点与其祖先的差值，其中一些如下：
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
在所有可能的差值中，最大值 7 由 |8 - 1| = 7 得出。
示例 2：


输入：root = [1,null,2,null,0,3]
输出：3
 

提示：

树中的节点数在 2 到 5000 之间。
0 <= Node.val <= 105
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
    int dfs(TreeNode* root)
    {
        if(root==nullptr)
        {
            return 0;
        }
        ans=max(
                max(
                    ans,abs(root->val-dfs(root->left))
                ),
                max(
                    ans,abs(root->val-dfs(root->left))
                )
            );
        return root->val;
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        return ans;
    }
};

【我的卡点】
唉，我不知道是自顶向上还是自顶向下，根本无从下手


Skill 工具暂时无法识别本地文件。我手动按教练流程来。

先检索你的历史题中最相关的那道。

## 一、当前理解

- **题目**：找二叉树中任意节点 B 和它祖先 A 之间，`|A.val - B.val|` 的最大值。
- **关键**：祖先必须是从根到该节点路径上的某个节点，不是任意两节点。
- **你的代码**：想用 DFS 做，但有几个明显问题：
  - 第 21 和 24 行都调用了 `dfs(root->left)`，`dfs(root->right)` 不见了
  - 只比较了 `root->val` 和直接孩子 `dfs(孩子)` 的返回值，这只能算父子差，不是祖先差
  - `dfs` 返回 `root->val`，这个返回值对上层父节点毫无帮助——父节点需要的是它路径上的**最值**，不是它的值
- **你的卡点**：不知道数据流向应该向上还是向下，不知道这个递归该传什么参数、该返回什么。

---

## 二、历史题关联判断

**判断结果：强相关** 🔥

你做过一道和本题几乎一模一样的题：

| 历史文件 | 题目 | 和本题的相通点 |
|----------|------|---------------|
| `63-lc-1448.cpp` | Count Good Nodes（统计二叉树中好节点的数目） | **核心模式完全一致**：自顶向下，把路径上的"最值"作为参数传给子节点 |

### 看 LC 1448 你写的代码：

```cpp
int goodNodes(TreeNode* root, int num=-INT_MAX)
{
    if(root==nullptr) return 0;
    if(root->val >= num)
    {
        num = root->val;                              // 更新路径上的最大值
        return 1 + goodNodes(root->left, num) + goodNodes(root->right, num);
    }
    else
    {
        return goodNodes(root->left, num) + goodNodes(root->right, num);
    }
}
```

**它做了什么？**
- 维护一个参数 `num`：**从根到当前节点的路径上，见过的最大的值**。
- 到每个节点时，用 `root->val` 和 `num` 比大小，判断当前节点是不是"好节点"。

**LC 1026 要做什么？**
- 维护 **两个** 参数：路径上的**最大值**和**最小值**。
- 到每个节点时，用 `root->val` 和这两个最值算出差值的最大值：`max(|root->val - 路径最小值|, |root->val - 路径最大值|)`。
- 取全局最大值。

**两道题的差异就是：LC 1448 只跟踪一个参数 `max`，LC 1026 需要同时跟踪 `min` 和 `max`。**

---

## 三、提示式教学

### 🔑 递进提示

**提示 1（数据流向）：**

这道题是 **自顶向下**。想想看：你要算的是"当前节点 vs 它的祖先"，而祖先信息是在**来路上的**。就像你走在一条小路上，每到一站你回头看"我和之前经过的最高/最低点差了多少"——你需要把"最高点"和"最低点"的信息一路带下来，不能从叶子往上报。

你在 LC 1448 中已经完美掌握了这个模式。

---

**提示 2（参数设计）：**

LC 1448 你写的是：

```cpp
goodNodes(TreeNode* root, int num=-INT_MAX)
```

只有一个 `num`（路径最大值）。那这道题你把函数签名改成什么样？提示：你需要两个参数。

---

**提示 3（递归里做什么）：**

到每个节点时，做三件事：

1. 用当前 `root->val` 和传下来的 **最大/最小** 算差值，更新全局答案
2. 更新路径最大/最小（把 `root->val` 考虑进去）
3. 把更新后的两个值继续传给左右孩子

你不需要返回值。用一个成员变量 `ans` 存答案就行了（这个你已经有了）。

---

### ❓ 思考题

1. 在 LC 1448 中，`num` 的初始值是 `-INT_MAX`。在这道题里，两个参数的初始值应该是什么？
2. 你的代码里 `dfs` 返回 `root->val`，你当时想用这个返回值做什么？为什么这个思路行不通？

---

## 四、我的代码问题

1. **抄错行了**：两个 `dfs(root->left)`，没有 `dfs(root->right)`。
2. **数据流向反了**：你想用 `abs(root->val - dfs(child))` 从子节点拿信息，但这只能拿到子节点的 `val`，拿不到"路径上的最值"。祖先比较需要**上游信息往下传**。
3. **返回值无意义**：`dfs` 返回 `root->val` 对父节点没用——父节点需要的不是这个值本身，而是整条路径的历史最值。

---

##  五、下一步行动

打开你写过的 `63-lc-1448.cpp`，看看它的结构和参数传递方式。然后在你的 LC 1026 代码中：

1. 把 `dfs` 签名改为 `void dfs(TreeNode* root, int mx, int mn)`
2. 递归体：`ans = max(ans, max(|root->val - mx|, |root->val - mn|))`，然后更新 `mx` 和 `mn` 传给左右孩子

不要让它返回值，你现有的 `ans` 成员变量足够了。写完发给我。

*/