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
    map<int,int> cnt;
    int dfs(TreeNode* root)
    {
        if(root==nullptr)
        {
            return 0;
        }
        int left=dfs(root->left);
        int right=dfs(root->right);
        int sum=root->val+left+right;
        cnt[sum]++;
        return sum;
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        dfs(root);
        vector<int> result;
        int freq=0;
        for(auto& [sum,f]:cnt)
        {
            if(f>freq)
            {
                freq=f;
                result.clear();
                result.push_back(sum);
            }else if(f==freq)
            {
                result.push_back(sum);
            }
        }
        return result;
    }
};

/*
调用文件夹中的skill

【新题目】

508. 出现次数最多的子树元素和

给你一个二叉树的根结点 root ，请返回出现次数最多的子树元素和。如果有多个元素出现的次数相同，返回所有出现次数最多的子树元素和（不限顺序）。

一个结点的「子树元素和」定义为以该结点为根的二叉树上所有结点的元素之和（包括结点本身）。

示例 1：
输入: root = [5,2,-3]
输出: [2,-3,4]

示例 2：
输入: root = [5,2,-5]
输出: [2]

提示:
节点数在 [1, 10^4] 范围内
-10^5 <= Node.val <= 10^5

【我的代码（错误版）】
class Solution {
    map<int,int> cnt;
    int dfs(TreeNode* root,int sum=0)
    {
        if(root==nullptr)
        {
            return 0;
        }
        sum+=root->val+dfs(root->left,root->val)+dfs(root->right,root->val);
        cnt[sum]++;
        return sum;
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        dfs(root);
        // 不知道怎么写答案构造...
    }
};

【我的卡点】
1. 不知道这个递归对不对
2. 不会从 cnt map 中构造最终答案


## 一、当前理解

- **题目**：对每个节点，计算以该节点为根的子树所有节点之和，统计这些"子树和"的出现频率，返回出现次数最多的那些子树和（可能有多个并列）。
- **你的代码思路**：用 DFS 递归计算子树和 + map 计数，方向是对的。
- **卡点**：① 递归公式有 bug，算出来的子树和是错的；② 不知道如何从 cnt map 中提取最终答案。

---

## 二、历史题关联判断

**判断结果：弱相关**

| 历史文件 | 题目 | 相通点 |
|----------|------|--------|
| `62-lc-129.cpp` | Sum Root to Leaf Numbers | 你用了带默认参数 `sum` 的 DFS。注意：129 是**自顶向下**传值，这道题需要**自底向上** |
| `60-lc-404.cpp` | Sum of Left Leaves | 用**成员变量**在递归间累积结果（你的 cnt map 也是这种模式） |
| `26-lc-2080.cpp` | RangeFreqQuery | 你用过 unordered_map 的迭代模式，对遍历 cnt 构造答案有帮助 |

---

## 三、教学

### 1. 这道题属于什么类型

**二叉树后序遍历 + 哈希表频率统计**。本质上是一个"自底向上求子树和"的 DFS，然后用 map 找出众数。

### 2. 核心思路

**关键观察：子树和可以自底向上累加**：

```
左子树的子树和 = dfs(root->left)
右子树的子树和 = dfs(root->right)
当前子树和 = root->val + 左子树的子树和 + 右子树的子树和
```

这就是典型的**后序遍历**——先处理左右孩子，再用孩子结果算自己的。

**你学过的 62-lc-129.cpp 和这道题的关键区别：**

| | LC 129 (Sum Root to Leaf) | LC 508 (本题) |
|---|---|---|
| 数据流向 | **自顶向下**（把父节点的值 sum*10 传给子节点） | **自底向上**（子节点算完把和返回给父节点） |
| 参数含义 | 把"到当前为止的路径和"传下去 | 不需要参数，只需要返回值 |

### 3. 算法步骤

**步骤 1：递归函数设计（不用带 sum 参数）**
```cpp
int dfs(TreeNode* root) {
    if (root == nullptr) return 0;
    
    int leftSum  = dfs(root->left);   // 左子树和
    int rightSum = dfs(root->right);  // 右子树和
    int total     = root->val + leftSum + rightSum;  // 当前子树和
    
    cnt[total]++;  // 记录频率
    return total;   // 把和返回给父节点用
}
```

**步骤 2：构造答案**
```cpp
vector<int> result;
int maxFreq = 0;
for (auto& [sum, freq] : cnt) {
    if (freq > maxFreq) {
        maxFreq = freq;
        result.clear();
        result.push_back(sum);
    } else if (freq == maxFreq) {
        result.push_back(sum);
    }
}
```

### 4. 复杂度分析

- **时间**：O(n)，每个节点访问一次
- **空间**：O(n)，递归栈深度最坏 n

### 5. 你的 sum 参数错在哪里

你写的是：
```cpp
sum += root->val + dfs(root->left, root->val) + dfs(root->right, root->val);
```

手动追踪 root = [5, 2, -3]：
```
dfs(5, 0):
    dfs(2, 5):       ← 5 是 root->val，被当"初始和"传进去了
        sum = 5 + 2 + 0 + 0 = 7    ← 错！节点 2 的子树和应该是 2
        cnt[7]++, return 7
    dfs(-3, 5):
        sum = 5 + (-3) + 0 + 0 = 2  ← 错！节点 -3 的子树和应该是 -3
        cnt[2]++, return 2
    sum = 0 + 5 + 7 + 2 = 14       ← 错！根节点子树和应该是 4
    cnt[14]++, return 14
```

你把 root->val 重复加进了孩子的计算里。去掉 sum 参数，让递归只靠返回值就够了。

---

## 四、我的代码问题

1. **递归公式错误**：`dfs(root->left, root->val)` 把父节点的值误传给了子节点做加数，导致每个子树和都被父节点的值污染了。
2. **sum 参数是多余的**：这题是自底向上，不需要自顶向下传参数。
3. **没有构造答案**：findFrequentTreeSum 函数体不完整，dfs 调用后缺少遍历 cnt 的代码。

---

## 五、下一步行动

**最小下一步：改写 dfs 函数。**
1. 去掉 sum 参数，dfs 只接受 root
2. 用两行分别接收 dfs(root->left) 和 dfs(root->right) 的返回值
3. 当前子树和 = root->val + 左返回值 + 右返回值
4. 把结果用 cnt 记录后，再 return 它

改完 dfs 后，再去补 findFrequentTreeSum 里的答案构造逻辑。
*/