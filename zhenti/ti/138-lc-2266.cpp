const int MOD = 1e9+7;
class Solution {
public:
    int countTexts(string pressedKeys) {
        vector<int> ans(pressedKeys.size()+1);
        ans[0]=1;
        for(int i=1;i<=pressedKeys.size();i++)
        {
            if(pressedKeys[i-1]=='2'||
               pressedKeys[i-1]=='3'||
               pressedKeys[i-1]=='4'||
               pressedKeys[i-1]=='5'||
               pressedKeys[i-1]=='6'||
               pressedKeys[i-1]=='8')
            {
                for(int j=1;j<=3;j++)
                {
                    if(i-j>=0&&pressedKeys[i-1]==pressedKeys[i-j])
                    {
                        ans[i]=(ans[i]+ans[i-j])%(MOD);
                    }else
                    {
                        break;
                    }
                }
            }else
            {
                for(int j=1;j<=4;j++)
                {
                    if(i-j>=0&&pressedKeys[i-1]==pressedKeys[i-j])
                    {
                        ans[i]=(ans[i]+ans[i-j])%(MOD);
                    }else
                    {
                        break;
                    }
                }
            }
        }
        return ans[pressedKeys.size()]%(MOD);
    }
};
/*
              if (pressedKeys[i - j] != pressedKeys[i - 1]) {
                    break;
                }
为什么是i-j而不是i-j-1?

因为这里的 `i` 是 **DP 的长度下标**，不是字符串下标。

---

## 1. `dp[i]` 和字符串下标的关系

你定义的是：

```cpp
vector<int> dp(n + 1);
```

所以：

```cpp
dp[i] 表示 pressedKeys 前 i 个字符的方案数
```

而字符串本身是 0 下标：

```cpp
pressedKeys[0]
pressedKeys[1]
...
pressedKeys[n - 1]
```

因此：

```cpp
第 i 个字符对应的字符串下标是 i - 1
```

也就是当前字符是：

```cpp
pressedKeys[i - 1]
```

---

## 2. 如果最后一段长度是 j，它覆盖哪些字符？

假设我们正在算 `dp[i]`，当前字符是：

```cpp
pressedKeys[i - 1]
```

如果最后一段按键长度是 `j`，那么这一段包括：

```cpp
pressedKeys[i - j]
pressedKeys[i - j + 1]
...
pressedKeys[i - 1]
```

也就是说，最后这一段的范围是：

```cpp
[i - j, i - 1]
```

所以它的第一个字符是：

```cpp
pressedKeys[i - j]
```

因此需要判断：

```cpp
pressedKeys[i - j] != pressedKeys[i - 1]
```

---

## 3. 为什么不是 `i - j - 1`？

`i - j - 1` 是这一段前面的那个字符，不属于当前这一段。

图示：

```text
前 i - j 个字符        最后 j 个字符
----------------     ----------------
0 ... i-j-1          i-j ... i-1
```

所以：

```cpp
pressedKeys[i - j - 1]
```

是当前这一段 **前面一个字符**。

它不需要和当前字符相同。

---

## 4. 举个例子

假设：

```cpp
pressedKeys = "22233"
```

下标：

```text
下标:  0 1 2 3 4
字符:  2 2 2 3 3
```

现在算到：

```cpp
i = 5
```

当前字符是：

```cpp
pressedKeys[4] = '3'
```

如果最后一段长度 `j = 2`，那么最后一段应该是：

```text
下标 3 和 4
字符 3 和 3
```

也就是：

```cpp
pressedKeys[3] 和 pressedKeys[4]
```

而：

```cpp
i - j = 5 - 2 = 3
```

所以判断：

```cpp
pressedKeys[3] != pressedKeys[4]
```

是对的。

如果写成：

```cpp
i - j - 1 = 5 - 2 - 1 = 2
```

那就变成了判断：

```cpp
pressedKeys[2] != pressedKeys[4]
```

也就是判断：

```text
'2' != '3'
```

但 `pressedKeys[2]` 是最后一段前面的字符，不属于最后一段 `"33"`，所以不应该用它来判断当前段是否合法。

---

## 5. 再看一下循环过程

代码：

```cpp
for (int j = 1; j <= limit; j++) {
    if (i - j < 0) break;

    if (pressedKeys[i - j] != pressedKeys[i - 1]) {
        break;
    }

    ways += dp[i - j];
}
```

当 `j = 1`：

```text
最后一段长度 1
范围: [i - 1, i - 1]
判断 pressedKeys[i - 1] == pressedKeys[i - 1]
```

当 `j = 2`：

```text
最后一段长度 2
范围: [i - 2, i - 1]
判断 pressedKeys[i - 2] == pressedKeys[i - 1]
```

当 `j = 3`：

```text
最后一段长度 3
范围: [i - 3, i - 1]
判断 pressedKeys[i - 3] == pressedKeys[i - 1]
```

因为循环是从 `j = 1` 逐渐增加的，如果 `j = 2` 已经不满足，就会 `break`，不会继续判断 `j = 3`。

所以这个写法实际上保证了：

```text
pressedKeys[i - j ... i - 1] 这一整段都相同
```

---

## 6. 简单记忆

`dp[i]` 表示前 `i` 个字符。

如果最后一段长度是 `j`：

```text
最后一段起点是 i - j
最后一段终点是 i - 1
```

所以应该比较：

```cpp
pressedKeys[i - j]
pressedKeys[i - 1]
```

而不是：

```cpp
pressedKeys[i - j - 1]
```

因为 `i - j - 1` 是最后一段前面的字符，不属于最后一段。



2. 你现在代码的真正问题：没有 break
你现在写的是：
cpp

1234
这个判断只检查了这一组的第一个字符和最后一个字符是否相同，但没有保证中间字符也相同。
比如：
text

1
第一个是 4，最后一个也是 4，但中间是 6，显然不能组成一组连续按键。
你的代码会错误地把这种情况当成合法情况


*/