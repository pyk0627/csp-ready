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
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==nullptr||q==nullptr)
        {
            return p==q;
        }
        return p->val==q->val && isSameTree(p->left,q->left)&&isSameTree(p->right,q->right);
    }
};
/*
为什么上面的代码是对的？
这一段是什么意思：
        if(p==nullptr||q==nullptr)
        {
            return p==q;
        } 

这段代码使用的是**深度优先搜索（递归）**的思想。整体逻辑非常清晰且优雅。

我们先来详细解释你问的这一段，再看整体代码为什么是对的。

### 这一段是什么意思：
```cpp
if(p==nullptr || q==nullptr)
{
    return p==q;
}
```

这段代码的作用是：**处理节点为空（到达树或子树的底部）的情况，同时判断两棵树的结构是否一致。**

具体拆解如下：
1. `if(p==nullptr || q==nullptr)`：
   这个条件的意思是：只要 `p` 和 `q` 之中**至少有一个**是空指针（`nullptr`），就进入这个 if 语句。
   （注意：如果两个都不为空，就不会进这个 if，而是去执行下面的 `return p->val == q->val ...`）

2. `return p==q;`：
   既然已经进入了 if 语句，说明至少有一个是空的。那么此时只有两种可能：
   * **可能一**：`p` 和 `q` **都为空**。此时 `p == q` 的结果是 `true`。这意味着两棵树在这个位置都结束了，结构相同，返回 `true`。
   * **可能二**：`p` 和 `q` **一个为空，一个不为空**。此时 `p == q` 的结果是 `false`。这意味着一棵树在这个位置有节点，而另一棵树没有，结构不同，返回 `false`。

**总结这段代码的巧妙之处：**
它用极简的代码同时处理了三种情况：
* 两个都空 $\rightarrow$ 结构相同，过。
* 一空一不空 $\rightarrow$ 结构不同，错。
* 都不空 $\rightarrow$ 跳过 if，去下面比较节点的值。

---

### 为什么整个代码是对的？

如果跳过了上面的 `if`，说明 `p` 和 `q` 都不为空（都是真实的节点）。接着执行：
```cpp
return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
```

这段代码完美契合了题目要求：“两个树在结构上相同，并且节点具有相同的值”。它同时检查了三个条件：
1. `p->val == q->val`：当前两个节点的值必须相等。
2. `isSameTree(p->left, q->left)`：递归检查它们的**左子树**是否完全相同。
3. `isSameTree(p->right, q->right)`：递归检查它们的**右子树**是否完全相同。

这三个条件用 `&&`（逻辑与）连接，意味着**只要有一个条件不满足，就会立刻返回 `false`**。只有当当前节点值相等，且左右子树都完全相同时，才返回 `true`。

---

### 举个例子（示例 2）帮你走一遍：

输入：`p = [1,2]`, `q = [1,null,2]`
1. 调用 `isSameTree(p节点1, q节点1)`。
2. 两个节点都不为空，跳过 `if`。
3. 判断 `1 == 1`（真）且 `isSameTree(p的左节点2, q的左节点null)` 且 `...`。
4. C++ 的 `&&` 有**短路特性**，接下来去执行 `isSameTree(节点2, nullptr)`。
5. 在这个新的递归中，`p` 是节点2，`q` 是 `nullptr`。
6. 触发 `if(p==nullptr || q==nullptr)`（因为 q 为空）。
7. 执行 `return p == q;`。此时 `p` 不为空，`q` 为空，所以 `p == q` 为 `false`。
8. 这个 `false` 往上返回，导致最开始的 `&&` 表达式变为 `false`，最终整个函数返回 `false`。

这就是为什么这段代码能正确判断两棵树是否相同的原因。它把复杂的问题拆解成了：“看当前节点是否一样，并且让左右孩子也去做同样的比较”。        
*/