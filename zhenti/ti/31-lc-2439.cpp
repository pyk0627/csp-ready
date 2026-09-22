class Solution
{
public:
	int minimizeArrayValue(vector<int>& nums)
	{
		auto check=[&](int limit)->bool
		{
			long long extra=0;
			for(int i=nums.size()-1;i>0;i--)
			{
				long long new_num=nums[i]+extra;
				extra=max(new_num-limit,0LL);
			}
			return nums[0]+extra<=limit;
		};

		int left=nums[0]-1;
		int right=ranges::max(nums);
		while(left+1<right)
		{
			int mid=(left+right)/2;
			(check(mid) ? right : left) = mid;
		}
		return right;
	}
};
/*
1.
上面这段代码中，这一行是什么意思：
       auto check = [&](int limit) -> bool { 


这行代码的作用是定义一个 Lambda 表达式（匿名函数），并将其赋值给名为 check 的变量。

这在 C++ 中非常常见，通常用于在函数内部快速定义一个局部函数。下面为您逐个部分拆解这行代码的含义：

auto check = [&](int limit) -> bool {

1. auto 告诉编译器自动推断 check 变量的类型。因为 Lambda 表达式的类型比较复杂（在 C++
中它是一个闭包类），我们通常不需要手动写出它的类型，直接用 auto 让编译器自己推断即可。

2. check
这是你给这个局部函数起的名字。在这行代码之后，你就可以像调用普通函数一样调用它，比如 check(5)。

3. =
赋值符号，把右边的 Lambda 表达式赋值给左边的 check。

4. [&] （捕获子句）
这是 Lambda 表达式的灵魂所在。方括号 [] 表示捕获外面的变量，以便在 Lambda 函数内部使用。
*   [&] 表示按引用捕获外部作用域中的所有变量。
*   在这段特定的代码中，它捕获了外部的 nums 数组。如果不加 [&]，Lambda 内部是访问不到 nums 的。按引用捕获可以避免拷贝整个数组，提高效率。

5. (int limit) （参数列表）
和普通函数一样，这是这个函数接收的参数。这个 check 函数接收一个整数 limit，代表二分查找时“猜测的最大值”。

6. -> bool （返回类型） 表示这个函数的返回值类型是布尔型（true 或 false）。在 C++ 中，如果 Lambda
表达式有明确的返回类型，通常用 -> 类型 来声明。如果不写，编译器也会尝试自动推断，但写出来更规范。

---

结合上下文看它的作用：
在这个算法中，作者使用了二分查找。二分查找的核心难点在于写一个 check 函数来验证某个猜测值是否合法。

这行代码定义了这个验证函数：“如果允许数组的最大值为 limit，我们能否通过把右边的数字转移给左边，使得整个数组的元素都不超过 limit？”
*   如果能，返回 true。
*   如果不能，返回 false。

然后在下面的二分查找循环中：

(check(mid) ? right : left) = mid;

直接像调用普通函数一样调用了 check(mid) 来缩小二分的边界。
*/

/*
2.
	extra = max(new_num - limit, 0LL); 
	这一行是什么意思？

这一行代码是整个 check 函数（二分查找的验证函数）的核心逻辑。

简单来说，它的作用是：计算当前元素超出了限制 limit 多少，并把这个“超出部分”继续丢给左边的元素去承担。

为了让你完全理解，我们逐个拆解这行代码的细节：

1. 算法背景：只能向左转移
题目允许的操作是：选中一个元素 nums[i]，将它减 1，并将 nums[i-1] 加 1。也就是说，数值只能从右向左转移。

在 check(limit) 函数中，我们要验证的是：“如果规定数组中所有元素都不能超过 limit，我们能不能通过向左转移做到？”
因为只能向左转移，所以我们从右向左遍历（for (int i = ...; i > 0; i--)）。

2. 变量解释
*   limit：我们二分猜测的“最大允许值”。
*   nums[i]：当前元素的原始值。
*   extra：从右边转移过来的“积木”（超出部分）。
*   new_num：nums[i] + extra，表示当前元素加上右边塞过来的东西后，现在的总价值。

3. max(new_num - limit, 0LL) 的两种情况

当我们在处理位置 i 时，现在的总价值是 new_num。我们要看它是否超过了 limit：

*   情况 A：new_num > limit（超标了）
    此时 new_num - limit 是一个正数。
    既然当前元素超标了，我们别无选择，只能把超出的这部分无脑丢给左边的 nums[i-1]。
    所以 max(正数, 0) 的结果就是这个正数，extra 被更新为这个超出量，在下一轮循环（处理 i-1 时）加到左边的元素上。

*   情况 B：new_num <= limit（没超标）
    此时 new_num - limit 是一个负数或 0。
    这说明当前元素加上右边过来的东西后，仍然在允许范围内。
    注意：我们不能把“没用完的额度”向左传递！（因为操作只能把当前元素的值减1往左加，不能凭空给左边加值）。所以对左边的贡献是 0。
    因此 max(负数, 0) 的结果是 0，extra 变成 0，表示不需要往左边丢任何东西。

4. 为什么是 0LL 而不是 0？ 这是一个 C++ 的防溢出小技巧。 new_num 的类型是 long long，limit 的类型是
int。它们相减时，int 会被提升为 long long，结果也是 long long。 如果这里写 0，它是一个 int 类型。虽然现代 C++
编译器通常能处理好 max(long long, int)，但为了绝对避免类型不匹配导致的编译警告或奇怪的行为，加上 LL 后缀，明确告诉编译器“这是一个
long long 类型的 0”，是最严谨的写法。

5. 举个直观的例子
假设 limit = 4，我们从右往左遍历：

i | nums[i] | 右边传来的 extra | new_num (当前总和) | new_num - limit | 传给左边的 extra: max(差值, 0LL)
3 | 5       | 0                | 5                  | 5 - 4 = 1       | 1 (超标了，把1丢给左边)
2 | 2       | 1                | 3                  | 3 - 4 = -1      | 0 (没超标，不用给左边加负担了)
1 | 3       | 0                | 3                  | 3 - 4 = -1      | 0

如果最后遍历到 i = 0 时，nums[0] + extra <= limit 成立，说明最左边的元素也撑住了，返回 true。否则返回 false。
*/

/*
3. int left = nums[0] - 1, 为什么是nums[0]-1？

这是配合开区间二分模板的边界设定，nums[0] - 1 是为了让 left 落在“答案下界之外”，从而维持开区间 (left, right) 的循环不变量。

一、开区间二分的不变量

灵神这里用的是开区间 (left, right) 写法，循环条件是 while (left + 1 < right)。其核心约定是：

- left 永远指向“不满足条件的值”（蓝色，不可行）；
- right 永远指向“满足条件的值”（红色，可行）；
- 真正的答案被夹在 (left, right] 这个区间里，循环结束时 left + 1 == right，right 就是答案。

也就是说，left 和 right 本身都不在待搜索的合法区间内，它们是两个“哨兵”，只负责把答案圈在中间。

二、答案的可能取值范围

本题求的是“经过操作后数组最大值的最小值”。由于操作只能把数值从右往左搬（nums[i]-- 且 nums[i-1]++），下标 0 这个位置只能接收、永远无法被减小，因此：

- 下界：答案至少是 nums[0]。因为 nums[0] 只增不减，最终数组里的最大值不可能比它还小。【turn0search5】【turn0search7】
- 上界：答案至多是 max(nums)。如果什么都不做，最大值就是原数组的最大值。【turn0search3】【turn0search7】

所以答案一定落在 [nums[0], max(nums)] 这个闭区间里。

三、为什么左边界要再减 1

既然答案的下界是 nums[0]，而开区间二分要求 left 必须落在“合法区间之外”，那么 left 就得取 nums[0] - 1，这样：

- left = nums[0] - 1：在答案下界之外（不可能是答案）；
- right = max(nums)：刚好是答案上界（有可能是答案）；
- 待搜索的合法区间是 (left, right] = (nums[0]-1, max(nums)]，正好覆盖 [nums[0], max(nums)]。【turn0search9】

如果只写 left = nums[0]，就把一个合法候选值放在了 left 上，破坏了“left 一定不可行”这个不变量，循环结束时的 right
就不一定是真正的最小可行值了。

四、对比闭区间写法更直观

如果改用闭区间 [left, right]，代码会长这样：

int left = nums[0], right = ranges::max(nums);
while (left < right) {           // 注意是 < 不是 <=
    int mid = (left + right) / 2;
    if (check(mid)) right = mid;  // mid 可行，往左压
    else            left = mid + 1;
}
return left;

 开区间写法（本题）  闭区间写法
left 初值  nums[0] - 1（界外）  nums[0]（界内）
right 初值  max(nums)  max(nums)
循环条件  left + 1 < right  left < right
边界更新  left = mid / right = mid  left = mid + 1 / right = mid
返回值  right  left

开区间的好处是边界更新都是 = mid，不用纠结 ±1，不容易写死循环；代价就是左右两个初值都要落在“合法区间之外”，所以 left
必须比真正的下界再小一点，于是就有了 nums[0] - 1。【turn0search13】【turn0search15】

小结

nums[0] - 1 的本质是：答案下界是 nums[0]，开区间模板要求 left 必须站在合法区间之外当哨兵，所以再往左退一步取 nums
[0] - 1，配合 right = max(nums) 和 while (left + 1 < right)，就能保证循环结束时 right
恰好收敛到答案。
*/

/*
4.

(check(mid) ? right : left) = mid;
这一行是什么意思？


这是一行非常巧妙且简洁的 C++ 代码。它的本质是根据 check(mid) 的返回值，决定是更新左边界还是右边界。

用通俗易懂的伪代码翻译，它等价于：

if (check(mid) == true) {
    right = mid;  // 如果 mid 可行，说明真正的答案可能更小，把右边界缩小到 mid
} else {
    left = mid;   // 如果 mid 不可行，说明真正的答案必须更大，把左边界缩小到 mid
}

为了让你彻底明白，我们从三个方面来拆解这行代码：

1. 逻辑含义（结合二分查找上下文） 这道题求的是“最小化的最大值”。 当 check(mid) 返回 true 时，说明“限制最大值为 mid
是可以做到的”。既然 mid 可以，那我们就要贪心地去试更小的值，所以我们把右边界 right 移到 mid。 当 check(mid) 返回 false
时，说明“限制最大值为 mid 做不到”。说明 mid 太小了，我们必须去试更大的值，所以把左边界 left 移到 mid。

2. C++ 语法原理：三元运算符的赋值
通常我们见到的三元运算符是拿来赋值的，比如 int a = (x > 0) ? 1 : -1;。
但在这里，三元运算符的结果被当作了“左值”来接收赋值。

在 C++ 中，如果三元运算符 ? : 的两个分支都是同一类型的变量（这里 right 和 left 都是 int
类型），那么它会返回该变量的引用。因此，= 右边的 mid 就可以直接赋值给被选中的那个变量。 这种写法省去了写 if-else
的花括号，非常极客和紧凑。

3. 呼应“开区间二分”的不变量
回忆一下上一个问题中提到的“开区间 (left, right)”模板：
*   left 永远指向“不可行”的值。
*   right 永远指向“可行”的值。

这行代码完美维持了这个不变量： 当 check(mid) 为 true 时，mid 是可行的，所以赋值给 right，保证 right 依然可行。 当
check(mid) 为 false 时，mid 是不可行的，所以赋值给 left，保证 left 依然不可行。

同时，因为是开区间，left 和 right 更新时直接等于 mid，不需要像闭区间那样写 left = mid + 1 或 right = mid -
1，这极大地减少了边界出错的可能。
*/