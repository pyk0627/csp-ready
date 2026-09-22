class Solution {

    int lb(vector<int>& nums,int target)
    {
        int l=-1;
        int r=nums.size();
        while(l+1 < r)
        {
            int mid = (r-l)/2+l;
            if(nums[mid]>=target)
            {
                r=mid;
            }else
            {
                l=mid;
            }
        }
        return r;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans;
        int a = lb(nums,target);
        int b = lb(nums,target+1)-1;
        if(a==nums.size() || nums[a] != target)
        {
            return {-1,-1};
        }else
        {
            return {a,b};
        }
    }
};

/*
为什么这里end可以这样确定？

这段代码中 `end` 的确定方式非常巧妙，它利用了 `lower_bound` 函数的定义来复用代码。我们可以通过以下几个步骤来理解为什么这样写是正确的：

### 1. 明确 `lower_bound` 的作用
你的 `lower_bound(nums, target)` 返回的是**第一个大于等于 `target`** 的元素下标。
如果数组中所有的元素都小于 `target`，它会返回 `nums.size()`。

### 2. 分析 `lower_bound(nums, target + 1)` 的含义
如果我们把传入的参数由 `target` 改成 `target + 1`，那么 `lower_bound` 返回的就是**第一个大于等于 `target + 1`** 的元素下标。

因为数组里的元素都是整数，**“大于等于 `target + 1`” 等价于 “严格大于 `target`**”。
所以，`lower_bound(nums, target + 1)` 返回的就是数组中**第一个严格大于 `target`** 的元素的下标。

我们假设这个下标为 `j`，即 `j = lower_bound(nums, target + 1)`。

### 3. 为什么减 1 就是 `end`？
既然 `j` 是第一个严格大于 `target` 的元素的下标，那么在数组非递减（排序）的前提下，下标 `j` 前面的那个元素（即下标 `j - 1`），必定是**最后一个小于等于 `target`** 的元素。

回到 `searchRange` 函数的前半部分：
```cpp
int start = lower_bound(nums, target);
if (start == nums.size() || nums[start] != target) {
    return {-1, -1}; // nums 中没有 target
}
```
这段代码已经保证了数组中**必定存在 `target`**。
既然数组中存在 `target`，且 `j - 1` 是最后一个小于等于 `target` 的元素，那么 `j - 1` 必定就是**最后一个等于 `target`** 的元素的下标。

因此，`end = lower_bound(nums, target + 1) - 1` 完美地找到了 `target` 的结束位置。

### 4. 举个具体的例子
假设 `nums = [5, 7, 7, 8, 8, 10]`，`target = 8`。

1. **找 `start`**：
   `lower_bound(nums, 8)` 会找到第一个 `>= 8` 的元素，即下标 `3`（第一个 `8`）。
   此时 `nums[3] == 8`，说明目标存在，`start = 3`。

2. **找 `end`**：
   `lower_bound(nums, 8 + 1)` 也就是 `lower_bound(nums, 9)`。
   它会找到第一个 `>= 9` 的元素，即下标 `5`（元素 `10`）。
   那么 `end = 5 - 1 = 4`。
   看看下标 `4`，它正是数组中最后一个 `8`。

3. **边界情况测试**：如果 `nums = [5, 7, 7, 8, 8]`，`target = 8`。
   `lower_bound(nums, 9)` 找不到 `>= 9` 的元素，会返回 `nums.size()`，也就是 `5`。
   那么 `end = 5 - 1 = 4`。
   下标 `4` 刚好是最后一个 `8`。完全正确！

### 总结
这种写法的核心思想是：**要求一个数的右边界，可以转化为求比它大 1 的数的左边界，然后左边界减 1 就是原数的右边界。** 这样就不需要专门写一个寻找右边界的二分查找函数了，代码非常简洁且不容易出错。

*/

/*
开区间的写法里面：
为什么要写成left+1<right的形式
怎么理解 


在二分查找中，区间的定义方式（闭区间、左闭右开、开区间）直接决定了 `while` 循环的条件和指针的更新方式。

对于你提供的**开区间 `(left, right)`** 写法，循环条件写成 `left + 1 < right` 是非常严谨且巧妙的。我们可以从以下三个角度来深刻理解：

### 1. 从“区间不为空”的数学定义来理解

在开区间 `(left, right)` 中，**合法的候选下标是严格大于 `left` 且严格小于 `right` 的整数**。
那么，这个区间里还剩多少个元素呢？
* 如果 `left + 1 == right`，比如 `left = 2`, `right = 3`，开区间是 `(2, 3)`，这中间没有任何整数了，说明**区间为空**，应该退出循环。
* 如果 `left + 1 < right`，比如 `left = 2`, `right = 5`，开区间是 `(2, 5)`，中间还有 `3, 4` 两个下标，说明**区间不为空**，需要继续循环。

所以，`left + 1 < right` 就是开区间不为空的充要条件。它等价于 `right - left > 1`。

### 2. 对比“闭区间”的写法

为了看得更清楚，我们对比一下你最开始提供的闭区间 `[left, right]` 写法：
* **闭区间 `[left, right]`**：合法下标包含 `left` 和 `right` 本身。只要 `left <= right`，区间里就至少有一个元素。所以条件是 `while (left <= right)`。更新时，因为 `mid` 已经检查过了，必须严格排除，所以是 `left = mid + 1` 或 `right = mid - 1`。
* **开区间 `(left, right)`**：合法下标不包含 `left` 和 `right` 本身。只要 `left + 1 < right`，区间里就至少有一个元素。所以条件是 `while (left + 1 < right)`。更新时，因为 `mid` 虽然检查过了，但我们可以直接把边界移动到 `mid` 处（即 `left = mid` 或 `right = mid`），新的区间 `(left, mid)` 或 `(mid, right)` 天然就不包含 `mid` 了，不需要加减 1。这也是开区间写法不容易越界、代码更简洁的原因。

### 3. 从“循环不变量”的角度来理解

这段代码的注释写得非常好，它维护了两个循环不变量：
* `nums[left] < target` （`left` 及其左侧的值，一定都小于 target）
* `nums[right] >= target` （`right` 及其右侧的值，一定都大于等于 target）

初始时，`left = -1`, `right = nums.size()`。我们假想 `nums[-1]` 是负无穷，`nums[n]` 是正无穷，不变量成立。
在循环中：
* 如果 `nums[mid] >= target`，说明 `mid` 可以作为新的 `right`，更新 `right = mid`，不变量依然维持。
* 如果 `nums[mid] < target`，说明 `mid` 可以作为新的 `left`，更新 `left = mid`，不变量依然维持。

**当循环结束时（即 `left + 1 == right` 时）：**
此时 `left` 和 `right` 紧挨着。根据不变量：
* `nums[left] < target`
* `nums[right] >= target`

这两个指针就像两堵墙，把整个数组分成了两半。左半部分全 `< target`，右半部分全 `>= target`。而 `right` 正是右半部分的第一个元素的下标！所以直接 `return right` 就完美得到了第一个 `>= target` 的下标。

### 总结
`while (left + 1 < right)` 的核心思想是：**只要这两个边界指针之间还有空隙（至少隔着一个元素），就说明搜索区间内还有元素，需要继续二分；当它们相邻时，搜索区间为空，二分结束。** 这种写法避免了繁琐的 `+1` 和 `-1`，只需修改指针指向 `mid` 即可，是二分查找中最不容易写错的一种模板。
*/

/*
lower_bound这个函数如果数组中没有target的话，会返回什么？

如果数组中没有 `target`，`lower_bound` 函数会返回**第一个严格大于 `target` 的元素的下标**。

如果数组中所有的元素都小于 `target`（或者数组为空），那么它会返回 `nums.size()`（即数组长度，相当于尾后迭代器/越界下标）。

我们可以分几种情况来详细说明，假设 `nums = [1, 3, 5, 7]`：

1. **`target` 在数组中间的空隙（不存在）**：
   * 例如 `target = 4`。数组中没有 4，但第一个大于等于 4 的元素是 `5`（下标为 2）。
   * `lower_bound` 返回 `2`。

2. **`target` 比数组所有元素都大（不存在）**：
   * 例如 `target = 8`。数组中所有元素都小于 8。
   * `lower_bound` 返回 `nums.size()`，也就是 `4`。

3. **`target` 比数组所有元素都小（不存在）**：
   * 例如 `target = 0`。第一个大于等于 0 的元素是 `1`（下标为 0）。
   * `lower_bound` 返回 `0`。

**结合你提供的 `searchRange` 代码来看：**

正是因为 `lower_bound` 在找不到 `target` 时会返回“第一个大于 `target` 的下标”或“越界下标”，所以你的代码中有这样一句关键的安全检查：

```cpp
int start = lower_bound(nums, target);
if (start == nums.size() || nums[start] != target) {
    return {-1, -1}; // nums 中没有 target
}
```

* 如果 `start == nums.size()`，说明所有元素都小于 `target`，自然不存在 `target`。
* 如果 `nums[start] != target`，说明 `lower_bound` 找到的是第一个**大于** `target` 的元素（因为等于的不存在），这也说明数组中不存在 `target`。

只有当 `start` 没越界，且 `nums[start] == target` 时，才说明真正找到了 `target` 的起始位置。
*/