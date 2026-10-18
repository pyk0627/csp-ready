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

const int MAX_M = 40; // 资源最大数量
const int OWNER_FREE = 0; // 0 表示资源空闲

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

	int st;

	// 进程的最大等待限度
	int w;

	// 进程需要处理的任务数量
	int k;

	// 进程的任务列表
	vector<task> tasks;

	// 进程的状态
	// 等待开始，申请中，运行中，结束
	string state = "WAITING"; // 默认状态是等待

	// 正在执行的任务
	// 初始化为0,表示进程刚开始执行任务列表中的第一个任务
	int cur_task = 0; 
	
	// 已经运行的段数
	int run_time = 0; // 进程刚开始时已运行段数为0

	// 申请失败的次数
	int wait_cnt = 0;

	// 当前占有的资源集合
	set<int> held;

	// 进程的收益
	long long profit = 0;

	// c类进程是否准备抢夺
	bool force_grab = false;

	// a类进程是否准备释放资源
	bool will_release = false;

	// 进程彻底结束的时间段
	// 段号是从1开始的
	int end_time = -1;
};

// n个进程，m个资源
int n,m;

vector<process> processes;

// 记录每个资源分别被哪个进程占有
int owner[MAX_M + 5];

void handle_failure(process& p)
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

	processes.resize(n);

	for(int i=0;i<n;i++)
	{
		//给processes[i]其一个别名，p
		process& p = processes[i];
		p.id=i+1;
		cin>>p.type;

		if(p.type=='X')
		{
			cin>>p.st>>p.k;
			p.w=0;
		}else
		{
			cin>>p.st>>p.w>>p.k;
		}

		p.tasks.resize(p.k);
		for(int j=0;j<p.k;j++)
		{
			cin>>p.tasks[j].a>>p.tasks[j].t;
		}
	}

	const int MAX_TIME = 500000;

	// 所有的进程都空闲吗
	bool all_idle = false;

	for(int t=1;t<=MAX_TIME;t++)
	{

		// 阶段0，唤醒
		for(auto& p:processes)
		{

			if(p.state=="WAITING" && t>=p.st)
			{
				p.state="APPLYING"; // 资源申请状态
			}
	
		}// 唤醒所有需要唤醒的进程

		// 阶段1,段首，处理资源申请与抢夺
		map<int , vector<pair<int,bool>>> requests;
		// 由资源编号得到 本段段首申请该资源的所有进程请求
		// first是int，进程编号
		// second是bool，是不是c类进程

		// 遍历进程，得到 哪些资源被哪些进程申请
		for(auto& p : processes)
		{
			if(p.state == "APPLYING")
			{
				int a1=p.tasks[p.cur_task].a; // a1是被申请的资源编号
				bool is_grab = (p.type == 'C' && p.force_grab);
				requests[a1].push_back({p.id,is_grab});
			}
		}

		for(auto& req_pair : requests)
		{
			int a1=req_pair.first; // 某一个资源编号
			auto& reqs = req_pair.second; // 申请a1资源的所有进程

			bool has_grab = false; // 假设申请列表上没有抢夺请求
			for(auto& r:reqs)
			{
				if(r.second)
				{
					has_grab = true;
					break;
				}
			}

			if(has_grab)
			{
				// 找到抢夺进程中的最大id
				int max_grabber_id =-1;
				for(auto& r : reqs)
				{
					if(r.second)
					{
						max_grabber_id = max(max_grabber_id,
											     r.first);
					}
				}

				// 如果目标资源已经被其他进程占有，则处理受害者进程
				if(owner[a1] != OWNER_FREE && // 如果当前的进程被占有
					owner[a1] != max_grabber_id // 而且还不是被抢夺进程中的最大id占有
					)
				{
					int victim_id = owner[a1]; // 根据资源找到受害者进程id
					process& victim = processes[victim_id - 1]; // 根据id找到进程本身
					victim.held.erase(a1); // 该进程不再占用资源a1
				}

//我怎么知道每进行一次操作之后，我都要改变哪些变量？
//怎么从题目总推导出代码关系

				owner[a1] = max_grabber_id;

				// owner里面存的是进程id
				// processes里面存的是进程对象
				// processes[0] 表示第1个进程对象，它的id
				// processes[0].id是1
				process& grabber = processes[max_grabber_id-1];

				grabber.held.insert(a1);
				grabber.state = "RUNNING"; // 申请完之后是运行状态
				grabber.force_grab = false;
				grabber.wait_cnt = 0;

				for(auto& r : reqs)
				{
					if(r.first != max_grabber_id)
					{
						// 申请列表中的其他进程中的当前一个进程
						process& other = processes[r.first-1]; 
						if(r.second) // 如果这个进程也是抢夺进程
						{
							other.state = "RUNNING";
							other.force_grab = false;
							other.wait_cnt = 0;
						}else
						{
							// 如果不是c类，按普通进程的申请失败处理
							handle_failure(other); 
						}
					}
				}
			}else // 如果没有抢夺进程
			{
				if(owner[a1] != OWNER_FREE)
				{
					for(auto& r : reqs)
					{
						process& p = processes[r.first-1];
						handle_failure(p);
					}
				}else // 如果当前的资源是空闲的
				{
					int min_p_id = n + 1;
					for(auto& r : reqs)
					{
// 还有能做类似优化的地方吗
						min_p_id = min(min_p_id,r.first);
					}

					owner[a1] = min_p_id;
					process& min_p = processes[min_p_id-1];
					min_p.held.insert(a1);
					min_p.state = "RUNNING";
					min_p.wait_cnt = 0;

					for(auto& r : reqs)
					{
						if(r.first != min_p_id)
						{
							process& p = processes[r.first-1];
							handle_failure(p);
						}
					}
				}
			}
		}
		// 段中，计算收益
		for(auto& p : processes)
		{
			if(p.state == "RUNNING")
			{
// 怎么知道什么时候要动哪些变量？
// 怎么知道要有哪些变量
				p.profit +=p.held.size();
				p.run_time++;
			}
			//cout<<p.id<<"->profit:"<<p.profit<<endl;
			//cout<<p.id<<"->runt_time:"<<p.run_time<<endl;
			
		}

// 怎么知道没有泄露的处理
		// 段末
		for(auto& p : processes)
		{
			if(p.state == "RUNNING" && // 如果当前的进程正在运行
// 怎么知道找到某一个变量的方法？
				p.run_time == p.tasks[p.cur_task].t) // 而且运行时间已经够了
			{
				if(p.cur_task == p.k-1) // 如果是最后一个任务
				{
					p.state = "IDLE"; // 进程的状态改为空闲
					p.end_time = t;

					for(int r : p.held)
					{
						if(owner[r] == p.id) // 再确认一下，可以删除这个判断
						{
							owner[r] = OWNER_FREE;
						}
					}
					p.held.clear();
				}else
				{
					// 对于一个任务，如果资源已经占有了，还有运行一段时间才算完成
					p.cur_task++; // 执行下一个任务
					p.run_time = 0; // 新任务要重新计时
					p.state = "APPLYING";
				}
			}
			
			// 如果是A类进程
			if(p.will_release)
			{
				for(auto& resource_id : p.held)
				{
					if(owner[resource_id] == p.id)
					{
						owner[resource_id] = OWNER_FREE;
					}
				}
				p.held.clear();
				p.will_release = false;
			}
		}

		// 先假设所有进程都结束了
		all_idle = true;
		for(auto& p : processes)
		{
			if(p.state != "IDLE")
			{
				all_idle = false;
				break;
			}
		}

		if(all_idle) break;
	}


	// 格式化输出
	for(auto& p : processes)
	{
		if(p.state != "IDLE")
		{
			cout<<p.profit<<" -1\n";	
		}else
		{
			int duration = p.end_time - p.st + 1;
			cout<<p.profit<<" "<<duration<<"\n";
		}
	}	
	
	return 0;
}



















