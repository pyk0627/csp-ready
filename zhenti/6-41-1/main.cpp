/*
202604-1平衡数

题目描述
小P在学习了位运算后，定义如下“平衡数”：

· 对于一个正整数 a，如果其二进制表示中 1 和 0 的个数相等，则称其为平衡数。
  这里的二进制表示以 1 为最高位，即不考虑更高位用于补位的 0。例如，正整数 12 的二进制表示为 1100，包含两个 1 和两个 0。在实际存储中，更高位可能需要填 0 补位，如 00001100，在本题中无需考虑此种情况。
  小P已经生成了 n 个正整数 a_1, a_2, \cdots, a_n，试编程统计里面有多少个平衡数。

输入格式
从标准输入读入数据。
输入的第一行包含一个正整数 n，第二行包含空格分隔的 n 个正整数 a_1, a_2, \cdots, a_n。

输出格式
输出到标准输出。
输出一个整数，表示 a_1, a_2, \cdots, a_n 中平衡数的个数。

样例输入

```
3
2 5 9
```

样例输出

```
2
```

样例解释
2 的二进制表示为 10，是平衡数；
5 的二进制表示为 101，不是平衡数；
9 的二进制表示为 1001，是平衡数。

子任务
50% 的测试点满足：0 < a_i \leq 256；
全部的测试点满足：0 < n \leq 100 且 0 < a_i \leq 10^9。*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	vector<int> nums(n);
	for(int i=0;i<n;i++)
	{
		cin>>nums[i];
	}

	int ans=0;

	for(auto& x:nums)
	{
		//使用这个内置命令可以算出x中有多少个1
		//这是32位中的数量
		int ones=__builtin_popcount(x);

		//算出有多少位
		int bits_num=0;
		int temp=x;
		
		//如果temp不等于0
		while(temp)
		{
			bits_num++;
			//将temp最右端的数字去除
			//temp = temp>>1;
			temp>>=1;
		}
		int zeros=bits_num-ones;
		if(ones==zeros)
		{
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
