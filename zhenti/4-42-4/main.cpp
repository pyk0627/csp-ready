#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000005
#define LOG 21

int n, q;
vector<int> exact;
//因为1<=n<=1000000,所以jump中的log取值是0到20，2的20次幂大于1000000
int jump[LOG][MAXN + 2];

// type = 1 处理奇数位置，type = 2 处理偶数位置
void process(vector<int>& arr, int type)
{
	// m，奇数位置仓库的个数
	int m = (int)arr.size() - 1;
	
	// 数组中的每个元素是一个二元组
	vector<pair<int, int>> pref;
	pref.reserve(m + 1);
//	pref[0] = (0, 0)
//	pref[1] = (a1, 1)
//	pref[2] = (a1^a2, 2)
//	pref[3] = (a1^a2^a3, 3)
	int cur_xor = 0;
	pref.push_back({0, 0});
	
	for (int i = 1; i <= m; i++)
	{
		cur_xor ^= arr[i];
		pref.push_back({cur_xor, i});
	}
	
	// 先按异或值从小到大排序，再按下标从小到大排序
	sort(pref.begin(), pref.end());
	
	int sz = (int)pref.size();
	
	for (int i = 0; i + 1 < sz; i++)
	{
		// 看相邻元素的前缀异或值是否相等
		if (pref[i].first == pref[i + 1].first)
		{
			// 两个端点的下标
			int u = pref[i].second;
			int t = pref[i + 1].second;
			
//			pref_xor[k] = arr[1] ⊕ arr[2] ⊕ ... ⊕ arr[k]
//			pref_xor[0] = 0
			
//			pref_xor[u] ⊕ pref_xor[t]
//			= (arr[1] ⊕ ... ⊕ arr[u]) ⊕ (arr[1] ⊕ ... ⊕ arr[u] ⊕ arr[u+1] ⊕ ... ⊕ arr[t])
//			= arr[u+1] ⊕ arr[u+2] ⊕ ... ⊕ arr[t]
			
			
			int start = 0, end = 0;
			
			if (type == 1)
			{
				// 奇数数组：pref[k] 对应 b[2k-1]
				start = 2 * u + 1;
				end = 2 * t - 1;
			}
			else
			{
				// 偶数数组：pref[k] 对应 b[2k]
				start = 2 * u + 2;
				end = 2 * t;
			}
			
			if (end <= n)
			{
				exact[start] = min(exact[start], end);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	if (!(cin >> n >> q)) return 0;
	
	vector<int> b(n + 1);
	for (int i = 1; i <= n; i++)
	{
		cin >> b[i];
	}
	
	// 先清空所有元素，再放入n+2个值为n+1的元素
	exact.assign(n + 2, n + 1);
	//exact[i]表示以i为起点的最短必胜区间的右端点
	//初始化为n+1,表示不存在
	
	
	// 奇数数组
	vector<int> odd_arr;
	odd_arr.push_back(0);
	for (int i = 1; i <= n; i += 2)
	{
		odd_arr.push_back(b[i]);
	}
	
	// 1代表奇数
	process(odd_arr, 1);
	
	vector<int> even_arr;
	even_arr.push_back(0);
	for (int i = 2; i <= n; i += 2)
	{
		even_arr.push_back(b[i]);
	}
	process(even_arr, 2);
	
	// best[i] 是 exact[i], exact[i+1], ..., exact[n] 中的最小值
	vector<int> best(n + 2, n + 1);
	for (int i = n; i >= 1; i--)
	{
		best[i] = min(exact[i], best[i + 1]);
	}
	
	// 通过best数组初始化 jump 第 0 层
	for (int i = 1; i <= n; i++)
	{
		if (best[i] <= n)
		{
			jump[0][i] = best[i] + 1;
		}
		else
		{
			jump[0][i] = n + 2;
		}
	}
	
	jump[0][n + 1] = n + 2;
	jump[0][n + 2] = n + 2;
	
	// 通过jump数组的第0层初始化jump数组的1到20层
	for (int p = 1; p < LOG; p++)
	{
		for (int i = 1; i <= n + 2; i++)
		{		
			//从i跳2^p的位置等于从i跳2^(p-1)再跳2^(p-1)次
			jump[p][i] = jump[p - 1][jump[p - 1][i]];
		}
	}
	
	while (q--)
	{
		int l, r;
		cin >> l >> r;
		
		int ans = 0;
		int cur = l;
		
		for (int p = LOG - 1; p >= 0; p--)
		{
			//能从cur位置跳跃2^p个必胜区间吗
			if (jump[p][cur] <= r + 1)
			{
				ans += (1 << p);
				cur = jump[p][cur];
			}
		}
		
		cout << ans << "\n";
	}
	
	return 0;
}
