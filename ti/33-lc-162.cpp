class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left=-1;
        int right=nums.size()-1;
        while(left+1<right)
        {
            int mid=(left+right)/2;
            if(nums[mid]>nums[mid+1])
            {
                right=mid;
            }else
            {
                left=mid;
            }
        }
        return right;
    }
};

/*
为什么
nums[mid]>nums[mid+1]就让right=mid?
这个代码用的应该是红蓝染色法

是的，这段代码确实可以理解为**红蓝染色法**。你问的关键点是：

> 为什么 `nums[mid] > nums[mid + 1]` 就可以让 `right = mid`？

一句话解释：

> 因为 `nums[mid] > nums[mid + 1]` 说明 `mid` 已经在“下坡”了。此时 `mid` 本身可能就是峰值；即使 `mid` 不是峰值，峰值也一定在 `mid` 左边或者就是 `mid`。所以可以安全地把搜索范围收缩到 `mid` 及其左边，也就是 `right = mid`。

下面详细解释。

---

## 1. 这段代码的区间含义

你的代码是：

```cpp
int left = -1;
int right = nums.size() - 1;

while (left + 1 < right) {
    int mid = (left + right) / 2;

    if (nums[mid] > nums[mid + 1]) {
        right = mid;
    } else {
        left = mid;
    }
}

return right;
```

它维护的是一个**左开右闭区间**：

```text
(left, right]
```

也就是说，答案一定在 `left + 1` 到 `right` 之间。

初始时：

```cpp
left = -1;
right = n - 1;
```

答案范围就是：

```text
( -1, n - 1 ]
```

也就是：

```text
[0, n - 1]
```

---

## 2. 红蓝染色怎么染？

这道题可以用“上坡 / 下坡”来理解。

题目假设：

```text
nums[-1] = -∞
nums[n] = -∞
```

并且相邻元素不相等：

```text
nums[i] != nums[i + 1]
```

所以任意一个位置 `i`，要么在上坡，要么在下坡。

---

### 红色：上坡

如果：

```cpp
nums[i] < nums[i + 1]
```

说明从 `i` 到 `i + 1` 是上升的。

此时 `i` 一定不是峰值，因为右边比它大。

所以可以把 `i` 染成红色，表示：

```text
峰值不在 i，应该往右边找。
```

在你的代码里：

```cpp
left = mid;
```

就是把 `mid` 染成红色。

---

### 蓝色：下坡

如果：

```cpp
nums[i] > nums[i + 1]
```

说明从 `i` 到 `i + 1` 是下降的。

此时 `i` 有可能是峰值。

为什么？

如果同时有：

```text
nums[i - 1] < nums[i]
nums[i] > nums[i + 1]
```

那么 `i` 就是峰值。

即使 `nums[i - 1] > nums[i]`，说明 `i` 不是峰值，那么峰值也一定在 `i` 的左边。

所以可以把 `i` 染成蓝色，表示：

```text
峰值可能是 i，或者在 i 左边。
```

在你的代码里：

```cpp
right = mid;
```

就是把 `mid` 染成蓝色。

---

## 3. 为什么 `nums[mid] > nums[mid + 1]` 时 `right = mid`？

因为这说明 `mid` 是下坡。

例如：

```text
nums[mid] > nums[mid + 1]
```

图形上相当于：

```text
        mid
         |
         v
... ?   / \ 
       /   \
```

`mid` 右边比 `mid` 小，所以从 `mid` 往右看，是下降的。

这时候有两种情况。

---

### 情况一：`mid` 自己就是峰值

如果：

```text
nums[mid - 1] < nums[mid]
nums[mid] > nums[mid + 1]
```

那么 `mid` 就是峰值。

所以不能把 `mid` 排除掉。

因此不能写：

```cpp
right = mid - 1;
```

而应该写：

```cpp
right = mid;
```

保留 `mid`。

---

### 情况二：`mid` 不是峰值

如果：

```text
nums[mid - 1] > nums[mid]
```

那么 `mid` 不是峰值，因为左边比它大。

但是注意，此时从更左边往 `mid` 看：

```text
nums[-1] = -∞
...
nums[mid - 1] > nums[mid] > nums[mid + 1]
```

左边最终是从 `-∞` 开始的，不可能一直上升到这里又突然没有峰值。

换句话说，从左边一路走到 `mid`，必然会出现一个“先上升后下降”的山顶。

所以峰值一定在：

```text
mid 左边，或者就是 mid
```

因此可以把右边界收缩到 `mid`：

```cpp
right = mid;
```

---

## 4. 反过来，为什么 `nums[mid] < nums[mid + 1]` 时 `left = mid`？

因为这说明 `mid` 是上坡：

```text
nums[mid] < nums[mid + 1]
```

此时 `mid` 一定不是峰值，因为右边比它大。

峰值一定在 `mid` 右边。

所以可以把左边界移动到 `mid`：

```cpp
left = mid;
```

注意你的代码使用的是左开右闭区间：

```text
(left, right]
```

所以：

```cpp
left = mid;
```

表示新的搜索范围是：

```text
(mid, right]
```

也就是不包含 `mid`。

---

## 5. 红蓝边界不变量

你的代码其实维护了这样一个不变量：

```text
left 是红色边界：nums[left] < nums[left + 1]
right 是蓝色边界：nums[right] > nums[right + 1]
```

初始时：

```text
left = -1
```

因为：

```text
nums[-1] = -∞ < nums[0]
```

所以 `left` 是红色边界。

初始时：

```text
right = n - 1
```

因为：

```text
nums[n - 1] > nums[n] = -∞
```

所以 `right` 是蓝色边界。

---

每次取 `mid`：

```cpp
if (nums[mid] > nums[mid + 1]) {
    right = mid;
} else {
    left = mid;
}
```

如果 `mid` 是蓝色，就让 `right = mid`。

如果 `mid` 是红色，就让 `left = mid`。

这样始终保持：

```text
left 红，right 蓝
```

也就是：

```text
nums[left] < nums[left + 1]
nums[right] > nums[right + 1]
```

当循环结束时：

```cpp
left + 1 == right
```

此时：

```text
nums[left] < nums[right]
nums[right] > nums[right + 1]
```

所以 `right` 比左边大，也比右边大。

因此 `right` 就是峰值。

---

## 6. 用例子看一遍

例如：

```text
nums = [1, 2, 3, 1]
```

下标：

```text
0: 1
1: 2
2: 3
3: 1
```

初始：

```text
left = -1
right = 3
```

---

### 第一次二分

```cpp
mid = (-1 + 3) / 2 = 1
```

比较：

```text
nums[1] = 2
nums[2] = 3
```

因为：

```text
2 < 3
```

所以 `mid = 1` 是上坡，染红：

```cpp
left = 1
```

现在区间是：

```text
(1, 3]
```

也就是：

```text
[2, 3]
```

---

### 第二次二分

```cpp
mid = (1 + 3) / 2 = 2
```

比较：

```text
nums[2] = 3
nums[3] = 1
```

因为：

```text
3 > 1
```

所以 `mid = 2` 是下坡，染蓝：

```cpp
right = 2
```

现在：

```text
left = 1
right = 2
```

满足：

```text
left + 1 == right
```

循环结束，返回：

```text
right = 2
```

`nums[2] = 3` 确实是峰值。

---

## 7. 重点：右边可能还有峰值，但不需要管

有时候 `nums[mid] > nums[mid + 1]` 时，右边其实也可能有峰值。

例如：

```text
[1, 5, 4, 3, 2, 1, 6, 0]
```

这里有两个峰值：

```text
5 是峰值
6 也是峰值
```

如果某次二分到一个下降位置，比如：

```text
nums[3] = 3
nums[4] = 2
```

满足：

```text
3 > 2
```

此时代码会：

```cpp
right = mid;
```

这表示它决定去左边找峰值。

虽然右边的 `6` 也是峰值，但题目只要求返回任意一个峰值，所以可以放弃右边。

只要保证左边或者 `mid` 这里一定还有峰值即可。

---

## 8. 等价的标准写法

你的代码用的是：

```cpp
left = -1;
right = n - 1;

while (left + 1 < right)
```

这是左开右闭写法。

也可以写成更常见的闭区间写法：

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[mid + 1]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};
```

这个写法的思想完全一样：

```text
如果 mid 在下坡，峰值在 mid 或左边；
如果 mid 在上坡，峰值在 mid 右边。
```

---

## 9. 总结

你的问题：

> 为什么 `nums[mid] > nums[mid + 1]` 就让 `right = mid`？

答案是：

```text
因为 nums[mid] > nums[mid + 1] 说明 mid 已经在下坡。
此时 mid 本身可能是峰值；
即使 mid 不是峰值，峰值也一定在 mid 左边。
所以可以把搜索右边界收缩到 mid。
```

用红蓝染色法说就是：

```text
nums[mid] < nums[mid + 1]：mid 是红色，答案在右边，left = mid。
nums[mid] > nums[mid + 1]：mid 是蓝色，答案可能是 mid 或在左边，right = mid。
```

最后红蓝边界相邻：

```text
left + 1 == right
```

此时：

```text
nums[left] < nums[right]
nums[right] > nums[right + 1]
```

所以 `right` 就是峰值。
*/