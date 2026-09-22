/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> st(nums.begin(),nums.end());
        ListNode* dummy = new ListNode(0,head);
        ListNode* cur=dummy;
        while(cur->next != nullptr)
        {
        //     int f=0;
        //     for(int i=0;i<nums.size();i++)
        //     {
        //         if(nums[i]==cur->next->val)
        //         {
        //             f=1;
        //             break;
        //         }
        //     }
            if(st.contains(cur->next->val))
            {
                cur->next=cur->next->next;
                
            }else
            {
                cur=cur->next;   
            }
        }
        return dummy->next;
    }
};
/*
unordered_set是什么？为什么用上了这个就不会超时？什么时候应该用这个？

`unordered_set` 是 C++ STL 提供的**基于哈希表实现的无序集合容器**，存储唯一元素，插入、删除、查找的平均时间复杂度为 O(1)。它之所以能让原题代码不超时，关键在于把"判断 `cur->next->val` 是否在 `nums` 中"这一步从 O(n) 的线性扫描降到了 O(1) 的哈希查找【turn0search0】【turn0search5】。

## 哈希表为什么能做到 O(1)

`unordered_set` 内部维护一个"桶数组"。插入元素时，先用哈希函数 `std::hash<T>` 把元素值映射成一个 `size_t` 哈希值，再通过 `bucket_index = hash(value) % bucket_count` 定位到某个桶；查找时走同样的路径，直接定位到桶后只需在该桶内（通常是链表）做少量比较即可。只要哈希函数分布均匀、冲突不严重，单次操作几乎是常数时间【turn0search5】【turn0search7】。

两种写法在判断节点是否要删除这一步的差异，可以通过下面的流程直观对比：

```mermaid
flowchart LR
    subgraph A["vector + ranges::contains（超时写法）"]
        A1["访问一个节点 val"] --> A2["线性扫描整个 nums<br/>逐个比较"]
        A2 --> A3{"找到?"}
        A3 -- 是 --> A4["删除"]
        A3 -- 否 --> A5["保留"]
        A4 --> A6["下一节点"]
        A5 --> A6
    end
    subgraph B["unordered_set（AC 写法）"]
        B1["访问一个节点 val"] --> B2["hash(val) 定位桶"]
        B2 --> B3["桶内少量比较<br/>平均 O(1)"]
        B3 --> B4{"找到?"}
        B4 -- 是 --> B5["删除"]
        B4 -- 否 --> B6["保留"]
        B5 --> B7["下一节点"]
        B6 --> B7
    end
```

在原题数据规模下（`nums` 与链表长度均可达 10⁵），超时写法每个节点都要扫描一次 `nums`，总操作约 10¹⁰ 次；而用 `unordered_set` 预处理后，每个节点只需一次哈希查找，总操作约 10⁵ 次，差距悬殊。

## 两种写法逐节点复杂度对比

| 写法 | 单次查询方式 | 单次查询复杂度 | 总复杂度（n=|nums|, m=链表长度） |
|---|---|---|---|
| `vector` + `ranges::contains` | 线性扫描数组 | O(n) | O(n × m) |
| `unordered_set::contains` | 哈希函数定位桶 | 平均 O(1) | O(n + m) |
| `vector` + `ranges::max`（超时代码额外开销） | 线性扫描数组 | O(n) | 每个节点都重算一次 |

`unordered_set` 的预处理（把 `nums` 全部 insert 进去）是一次性 O(n)，之后每次查询摊销下来几乎免费，这正是从 TLE 到 AC 的核心【turn0search2】【turn0search10】。

## 退化风险：平均 O(1) 不等于最坏 O(1)

需要明确的是，`unordered_set` 的 O(1) 是**平均情况**。在最坏情况下（哈希冲突极其严重，所有元素挤进同一个桶），查找会退化成在桶内链表上线性扫描，复杂度变为 O(n)【turn0search10】【turn0search22】。

触发退化的常见原因：

- **数据被构造性针对**：LeetCode 等竞赛平台会针对默认 `std::hash<int>` 构造大量同哈希值的用例，导致所有元素落在同一个桶里。
- **负载因子过高未及时 rehash**：元素数量远超桶数量时冲突概率上升。
- **自定义类型未提供良好哈希函数**：例如用 `pair<int,int>` 做 key 时没有特化 `std::hash`。

应对手段：调用 `reserve(n)` 预分配足够的桶、用 `max_load_factor` 调低负载因子阈值、或对关键场景换用 `set`（红黑树，稳定 O(log n)）【turn0search21】【turn0search23】。不过在力扣日常题里，默认 `unordered_set<int>` 几乎不会被卡。

## 什么时候该用 unordered_set

- **频繁判断"某元素是否存在"**：如本题删除链表中出现在数组里的节点、两数之和的查表、图遍历中标记已访问状态。
- **大规模去重**：输入规模上万、只需要唯一性而不关心顺序时，比 `set` 的 O(log n) 更快【turn0search27】。
- **用空间换时间可接受**：哈希表需要额外的桶数组开销，内存敏感场景要权衡。

反过来，下面这些情况不该用它：

| 场景 | 应选容器 | 原因 |
|---|---|---|
| 需要元素有序遍历、范围查询（`lower_bound` 等） | `set` | `unordered_set` 无序，不支持有序操作【turn0search11】【turn0search13】 |
| 需要稳定最坏复杂度、不能接受哈希退化 | `set` | 红黑树保证 O(log n)，无哈希冲突风险【turn0search18】 |
| 数据量极小（几十个元素）且查询次数少 | `vector` + 线性扫描 | 哈希表常数开销大于线性扫描，反而更慢 |
| 自定义类型作为 key 且不想写哈希函数 | `set` | `set` 只需 `operator<`，`unordered_set` 需特化 `std::hash`【turn0search20】 |

一句话判断标准：**只关心"在不在"、不关心顺序、数据量大 → `unordered_set`；需要有序或稳定 → `set`；数据极小 → `vector` 直接扫**。
*/