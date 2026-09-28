/*
202606-4 石子游戏

题目背景
小C和小S正在玩一种石子游戏，规则如下：
· 有 m 个仓库，从左到右编号为 1, 2, ..., m，i 号仓库初始存有 a_i 个石子。
· 两位玩家轮流操作，小S先手。每轮操作可任选一个仓库 i，从中取出任意大于0数量的石子，将取出石子移至 i - 1 号仓库。特别地，若 i = 1，取出的石子将直接被丢弃。
· 当全部仓库石子均被清空时游戏终止，此时无法进行操作的玩家判负。
聪明的小C发现他必胜的条件为：所有奇数编号仓库的石子数异或和为0，即 a_1 ⊕ a_3 ⊕ ... ⊕ a_{2k-1} = 0，m = 2k - 1 或 2k，其中 ⊕ 表示二进制异或操作。

题目描述
给定 n 个仓库，从左到右编号为 1, 2, ..., n，i 号仓库初始存有 b_i 个石子。
定义子游戏 (l, r)：选取仓库 l ∼ r 进行上述石子游戏，将其视作一组新仓库，i 号仓库初始石子数为 a_i = b_{l+i-1}。
共有 q 个互相独立的询问，每个询问给出区间 [L, R]，小C需要把 [L, R] 分割为若干个区间 [l_1, r_1], [l_2, r_2], ..., [l_k, r_k]，
满足 l_1 = L, r_k = R, r_i = l_{i+1} - 1 (1 ≤ i < k)，使得在 k 个子游戏 (l_1, r_1), (l_2, r_2), ..., (l_k, r_k) 
中他必胜的子游戏数量尽可能地多。求所有合法分割方案里，小C必胜的子游戏数量的最大值。

输入格式
从标准输入读入数据。
第一行读入两个正整数 n, q，表示仓库数量和询问次数。
第二行读入 n 个非负整数 b_1, b_2, ..., b_n，表示各仓库的石子个数。
接下来 q 行，每行读入两个正整数 L, R，表示一个询问。题目保证 1 ≤ L ≤ R ≤ n。

输出格式
输出到标准输出。
输出 q 行，每行一个整数，表示每组询问中小C能得到的必胜子游戏数量的最大值。

样例输入
4 2
1 2 1 0
2 3
1 4

样例输出
0
2

样例解释
容易得知，只有子游戏 (1, 3), (1, 4), (4, 4) 是小C必胜的。
因此第一个询问 (2, 3) 中不存在一个区间满足小C必胜，答案为0；
第二个询问 (1, 4) 可以分割为 (1, 3) 和 (4, 4)，答案为2。

子任务
本题采用捆绑测试，你只有通过一个子任务中的所有测试点才能得到该子任务的分数。

子任务    测试点编号    约束
一        1 ~ 10        1 ≤ n, q ≤ 100
二        11 ~ 20       1 ≤ n, q ≤ 3000
三        21 ~ 30       1 ≤ n, q ≤ 10^5
四        31 ~ 40       1 ≤ n, q ≤ 10^6

保证对于所有测试点，均有 0 ≤ b_i < 2^{31}。
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN=1000005;
const int LOG=21;

//因为1<=n<=1000000,所以jump中的log取值是0到20，2的20次幂大于1000000
int jump[LOG][MAXN+2];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n,q;
	if(!(cin>>n>>q))return 0;

	vector<int> b(n+1);
	for(int i=1;i<=n;i++)
		cin>>b[i];

	//exact[i]表示以i为起点的最短必胜区间的右端点
	//初始化为n+1,表示不存在
	vector<int> exact(n+2,n+1);

	//const表示我们只读取，不修改
	auto process = [&](const vector<int>& arr,int type)
	{
		//传入数组的元素个数
		int m=arr.size()-1;
		//第一个int用来存放前缀异或和，第二个int用来存对应的下标位置
		vector<pair<int,int>> pref;
		//预分配内存
		pref.reserve(m+1);

		int cur_xor=0;
		pref.push_back({0,0});
		for(int i=1;i<=m;i++)
		{
			cur_xor^=arr[i];
			pref.push_back({cur_xor,i});
		}

		//先按异或值从小到大排序，再按下标从小到大排序
		sort(pref.begin(),pref.end());

		for(int i=0;i+1<pref.size();i++)
		{
			if(pref[i].first==pref[i+1].first)
			{
				int u=pref[i].second;
				int t=pref[i+1].second;

				int start=0,end=0;
				//奇数
				if(type==1)
				{
					//pref[i].first==pref[i+1].first
					//表示，pref[]数组中，pref[u+1]到pref[t]的元素异或和为0
					//pref[]只是元素中的奇数组或者偶数组
					//如果是奇数组，pref[k]=b[2k-1]
					start=2*u+1;
					end=2*t-1;
				}else
				{
					//如果是偶数组，pref[k]=b[2k]
					start=2*u+2;
					end=2*t;
				}

				if(end<=n)
				{
					exact[start]=min(exact[start],end);
				}
			}
		}
	};

	//奇数
	vector<int> odd_arr;
	odd_arr.push_back(0);
	for(int i=1;i<=n;i+=2)
	{
		odd_arr.push_back(b[i]);
	}
	process(odd_arr,1);

	vector<int> even_arr;
	even_arr.push_back(0);
	for(int i=2;i<=n;i+=2)
	{
		even_arr.push_back(b[i]);
	}
	process(even_arr,2);

	//best[i]是exact[i],exact[i+1],exact[i+2]...exact[n]中的最小值
	vector<int> best(n+2,n+1);
	for(int i=n;i>=1;i--)
	{
		best[i]=min(exact[i],best[i+1]);
	}

	//通过best数组初始化jump数组的第0层
	for(int i=1;i<=n;i++)
	{
		if(best[i]<=n)
		{
			jump[0][i]=best[i]+1;
		}else
		{
			jump[0][i]=n+2;
		}
	}
	jump[0][n+1]=n+2;
	jump[0][n+2]=n+2;

	//通过jump数组的第0层初始化jump数组的1到20层
	for(int p=1;p<LOG;p++)
	{
		for(int i=1;i<=n+2;i++)
		{
			//从i跳2^p的位置等于从i跳2^(p-1)再跳2^(p-1)次
			jump[p][i]=jump[p-1][jump[p-1][i]];
		}
	}	

	while(q--)
	{
		int l,r;
		cin>>l>>r;
		int ans=0;
		int cur=l;
		for(int p=LOG-1;p>=0;p--)
		{
			//能从cur位置跳跃2^p个必胜区间吗
			if(jump[p][cur]<=r+1)
			{
				ans+=(1<<p);
				cur=jump[p][cur];
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}