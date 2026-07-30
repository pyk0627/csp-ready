class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if(root1==nullptr||root2==nullptr)
        {
            return root1==root2;
        }
        return root1->val==root2->val&&
                (
                (
                    flipEquiv(root1->left,root2->left)&&
                    flipEquiv(root1->right,root2->right)
                )
                ||
                (
                    flipEquiv(root1->left,root2->right)&&
                    flipEquiv(root1->right,root2->left)
                )
                );
    }
};

/*
调用文件夹中的skill

【新题目】

951. 翻转等价二叉树

我们可以为二叉树 T 定义一个 翻转操作 ，如下所示：选择任意节点，然后交换它的左子树和右子树。

只要经过一定次数的翻转操作后，能使 X 等于 Y，我们就称二叉树 X 翻转 等价 于二叉树 Y。

这些树由根节点 root1 和 root2 给出。如果两个二叉树是翻转 等价 的树，则返回 true ，否则返回 false 。

示例 1：
输入：root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
输出：true
解释：我们翻转值为 1，3 以及 5 的三个节点。
示例 2:
输入: root1 = [], root2 = []
输出: true
示例 3:
输入: root1 = [], root2 = [1]
输出: false

提示：
每棵树节点数在 [0, 100] 范围内
每棵树中的每个值都是唯一的、在 [0, 99] 范围内的整数

【我的代码（错误版）】
class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if(root1==nullptr||root2==nullptr)
        {
            return root1==root2;
        }
        if(root1->left!=nullptr&&
            root2->left!=nullptr&&
            root1->left->val==root2->left->val)
        {
            return root1->val==root2->val&&flipEquiv(root1->left,root2->left);
        }
        ...(一共8个if分支枚举各种匹配情况，省略)...
        return root1->val==root2->val;  // 危险兜底！
    }
};

【我的卡点】
root1 = [1,2,3], root2 = [1,2,null,3]
预期 false，我的代码输出 true
枚举式写法漏掉了"两边孩子都为空 vs 对方还有孩子"的情况


## 一、当前理解

- **题目**：判断两棵二叉树是否"翻转等价"——即是否可以通过任意次交换任意节点的左右子树，使两棵树变得相同。
- **你的代码思路**：试图枚举所有可能的孩子匹配情况（左对左、左对右等，再加各种 null 组合），通过比对 val 来决定递归方向。
- **卡点**：root1=[1,2,3] 和 root2=[1,2,null,3] 本应返回 false，但代码返回了 true。

---

## 二、历史题关联判断

**判断结果：强相关**

| 历史文件 | 题目 | 核心模式 |
|----------|------|----------|
| `64-lc-100.cpp` | Same Tree（相同树） | 递归比较 left==left && right==right |
| `65-lc-101.cpp` | Symmetric Tree（对称二叉树） | 递归比较 left==right && right==left（交叉比较） |

**相通点**：LC 951 是这两道题的"组合版"：
- LC 100：不翻转时，左对左、右对右。
- LC 101：翻转时，左对右、右对左。
- LC 951：在每个节点，你可以选择"翻转"或"不翻转"，两种可能性是 **或** 的关系。

---

## 三、提示式教学

### 递进提示

**提示 1（这道题像什么）：**
这道题的递归结构和 Same Tree (LC 100) 几乎一模一样——只是每次递归多了一个选择。
```cpp
// Same Tree: 必须左对左、右对右
return p->val==q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
```

**提示 2（关键模式）：**
再看看 LC 101（对称二叉树）：
```cpp
// Symmetric: 必须左对右、右对左
return l->val==r->val && f(l->left, r->right) && f(l->right, r->left);
```
LC 951 允许你**两种都试**。

**提示 3（如何修改）：**
你不需要 8 个 if 分支去"预判"。递归的美妙之处在于：每一层只需要说——
"要么不翻转（左对左 且 右对右），要么翻转（左对右 且 右对左），只要有一条路走通就行。"
这只需要**一个 `||`**。

**提示 4（突破口）：**
你的代码失败原因：root1 的节点 2 是叶子（左右都 null），root2 的节点 2 有左孩子 3，你的 8 个 if 都跳过了，最后掉到了 `return root1->val==root2->val`——只比了值，没有递归检查孩子。正确的写法不需要枚举。

### 思考题

1. 如果在当前节点，r1->left 和 r2->left 的值不一样，只能走"翻转"路径吗？
2. 代码里最后一行 `return root1->val==root2->val` 在什么情况下会"放过"一个本不该通过的情况？

---

## 四、我的代码问题

1. **试图在父节点就"决定"子节点怎么匹配**。正确做法：父节点只比较自己的 val，把"孩子怎么匹配"交给递归。
2. **枚举覆盖不全**。组合情况太多，漏了"自己这边两个孩子都 null，对面还有孩子"的情况。
3. **最后的 `return root1->val==root2->val` 是危险兜底**。当所有 if 都不命中时，直接返回 true，完全没有检查子树。

---

## 五、下一步行动

把 40 行的 8 个 if 分支全部删掉，改成和 LC 100 一样的递归结构：

```
if (一个空一个不空) return false;
if (两个都空) return true;
if (值不相等) return false;
return (不翻转情况) || (翻转情况);
```

只需要 5 行代码。
*/