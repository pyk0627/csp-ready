// 时间单位是段，每一段分为3个部分，段首，段中，段末

// 第i个进程会从第st_i段首开始活动，意思是
// 第i个进程在第st_i这一段的“段首”开始参与资源申请
// st_i，第i个进程的“开始段号”，st是start的缩写

// 每个进程有一个任务列表，（a，t）
// ai,1：第i个进程，第一次运行前要申请的资源编号
// ti,1：第i个进程，第1次运行的时间

// 第i个进程完成第1个任务的时间：从st_i段首开始到 st_i +ti,1 - 1 段末结束

// 每个进程有两种状态，

// 只有当第i号进程所有任务结束完之后才会释放所有它之前申请过的资源

//  号进程从开始活动到结束的理想总收益为：
// 1×ti,1 + 2×ti,2 +…+ ki×ti,k

#include <bits/stdc++.h>
using namespace std;


//定义任务结构体
struct task
{
	//每个任务都有需要申请的资源编号和持续时间
	int a;
	int t;
};

//
struct process
{
	int id;

	// 进程类型:X,A,B,C
	char type;

	int starttime;

	// 进程的最大等待限度
	int w;

	// 进程需要处理的任务数量
	int k;

	// 进程的任务列表
	vector<task> tasks;

	// 进程的状态
	// 等待开始，申请中，运行中，结束
	string state;

	// 正在执行的任务
	int cur_task;

	// 已经运行的段数
	int run_time;

	// 申请失败的次数
	int wait_cnt;

	// 当前占有的资源集合
	ser<int> held;

	// 进程的收益
	long long profit;

	// 特殊情况
	//
	// c类进程是否出发抢夺
	bool force_grab;

	// a类进程是否需要释放资源
	bool will_release;

	// 进程彻底结束的时间段
	int end_time;
};

// n个进程，m个资源
int n,m;

vector<process> processes;

// 记录每个资源分别被哪个进程占有
int owner[45];

void handel_failure(process& p)
{
	p.wait_cnt++;
	if(p.wait_cnt==p.w)
	{
		if(p.type=='B')
		{
			p.state="RUNNING";
			p.wait_cnt=0;
		}else if(p.type=='A')
		{
			p.will_release=true;
			p.wait_cnt=0;
		}else if(p.type=='C')
		{
			p.force_grab=true;
			p.wait_cnt=0;
		}
	}
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	if(!(cin>>n>>m))return 0;

	process.resize(n);

	for(int i=0;i<n;i++)
	{
		//给processes[i]其一个别名，p
		process& p = preocess[i];
		p.id=i+1;
		cin>>p.type;

		if(p.type=='X')
		{
			cin>>p.starttime>>p.k;
			p.w=0;
		}else
		{
			cin>>p.starttime>>p.w>>p.k;
		}

		p.tasks.resize(p.k);


		for(int j=0;j<p.k;j++)
		{
			cin>>p.tasks[j].a>>p.tasks[j].t;
		}

		// 进程初始化为等待状态
		p.state="WAITING";

		p.cur_task=0;
		p.run_time=0;
		p.wait_cnt=0;
		p.profit=0;

		// 是否去抢夺别人的进程
		p.force_grab=false;
		p.will_release=false;

		// 初始化进程结束的段号
		p.end_time=-1;
	}

	const int MAX_TIME = 500000;

	// 所有的进程都空闲吗
	bool all_idle = false;

	for(int t=1;t<=MAX_TIME;t++)
	{

		//阶段0，唤醒
		for(auto& p:processes)
		{

			if(p.state=="WAITING" && t>=p.st)
			{
				p.state="APPLYING";
			}
	
		}// 唤醒所有需要唤醒的进程

		vector<pair<process*
}



















