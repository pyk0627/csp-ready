#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map> 

using namespace std;

// 【第4点优化】：用常量代替魔法数字，让代码意图一目了然
const int MAX_M = 40;        // 资源最大数量
const int OWNER_FREE = 0;    // 0 代表资源空闲

// 定义任务结构体
struct Task {
    int a; // 申请的资源编号
    int t; // 需要运行的段数
};

// 定义进程结构体
struct Process {
    int id;
    char type;       // 进程类型: 'X', 'A', 'B', 'C'
    int st, w, k;    // 开始时间, 忍耐限度, 任务数量
    vector<Task> tasks; // 任务列表
    
    // 【第3点优化】：直接在定义时给变量赋默认初值
    string state = "WAITING"; 
    int cur_task = 0;    
    int run_time = 0;    
    int wait_count = 0;  
    
    set<int> held;       
    long long profit = 0;
    
    bool force_grab = false;   
    bool will_release = false; 
    int end_time = -1;     
};

int n, m;
vector<Process> processes;

// 【第4点优化】：用常量定义数组大小
int owner[MAX_M + 5]; 

// 辅助函数：处理申请失败后的逻辑
void handle_failure(Process& p) {
    p.wait_count++;
    // 如果连续失败次数达到了忍耐限度 w
    if (p.wait_count == p.w) {
        if (p.type == 'B') {
            p.state = "RUNNING";
            p.wait_count = 0;
        } else if (p.type == 'A') {
            p.will_release = true;
            p.wait_count = 0;
        } else if (p.type == 'C') {
            p.force_grab = true;
            p.wait_count = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    processes.resize(n);
    // 1. 读入并初始化所有进程
    for (int i = 0; i < n; i++) {
        Process& p = processes[i];
        p.id = i + 1;
        cin >> p.type;
        
        if (p.type == 'X') {
            cin >> p.st >> p.k;
            p.w = 0; 
        } else {
            cin >> p.st >> p.w >> p.k;
        }
        
        p.tasks.resize(p.k);
        for (int j = 0; j < p.k; j++) {
            cin >> p.tasks[j].a >> p.tasks[j].t;
        }
        
        // 【第3点优化】：因为结构体里已经有了默认值，
        // 所以这里原来那一大坨初始化代码（state, cur_task, run_time等）全部被删掉了！
    }

    const int MAX_TIME = 500000; 
    bool all_idle = false;

    // 2. 开始按“段”模拟时间轴
    for (int T = 1; T <= MAX_TIME; T++) {
        
        // 【阶段 0】：唤醒到达开始时间的进程
        for (auto& p : processes) {
            if (p.state == "WAITING" && T >= p.st) {
                p.state = "APPLYING";
            }
        }

        // 【阶段 1】：段首 - 处理资源申请与抢夺
        // 【第2点优化】：vector 里面存进程的 ID (int)，不再存指针 (Process*)
        map<int, vector<pair<int, bool>>> requests; 
        for (auto& p : processes) {
            if (p.state == "APPLYING") {
                int res = p.tasks[p.cur_task].a;
                bool is_grab = (p.type == 'C' && p.force_grab);
                requests[res].push_back({p.id, is_grab}); // 存入 p.id
            }
        }

        // 逐个资源处理冲突 (遍历 map)
        for (auto& req_pair : requests) {
            int res = req_pair.first;
            auto& reqs = req_pair.second;

            bool has_grab = false;
            for (auto& r : reqs) {
                if (r.second) { has_grab = true; break; }
            }

            if (has_grab) {
                // 【第2点优化】：用 ID 记录抢夺者，不再用指针
                int max_grabber_id = -1; 
                for (auto& r : reqs) {
                    if (r.second) {
                        if (max_grabber_id == -1 || r.first > max_grabber_id) {
                            max_grabber_id = r.first;
                        }
                    }
                }

                // 【第4点优化】：使用 OWNER_FREE
                if( owner[res] != OWNER_FREE && 
                     owner[res] != max_grabber_id)
                {
                    int victim_id = owner[res];
                    // 【第2点优化】：通过 ID 找到对应的进程，用点号 (.) 代替箭头 (->)
                    Process& victim = processes[victim_id - 1];
                    victim.held.erase(res);
                }

                owner[res] = max_grabber_id;
                Process& grabber = processes[max_grabber_id - 1];
                grabber.held.insert(res);
                grabber.state = "RUNNING";
                grabber.force_grab = false;
                grabber.wait_count = 0;

                for (auto& r : reqs) {
                    if (r.first != max_grabber_id) {
                        Process& other = processes[r.first - 1];
                        if (r.second) {
                            other.state = "RUNNING";
                            other.force_grab = false;
                            other.wait_count = 0;
                        } else {
                            handle_failure(other);
                        }
                    }
                }
            } else {
                // 【第4点优化】：使用 OWNER_FREE
                if (owner[res] != OWNER_FREE) {
                    for (auto& r : reqs) {
                        Process& p = processes[r.first - 1];
                        handle_failure(p);
                    }
                } else {
                    // 【第2点优化】：用 ID 记录最小申请者
                    int min_p_id = -1;
                    for (auto& r : reqs) {
                        if (min_p_id == -1 || r.first < min_p_id) {
                            min_p_id = r.first;
                        }
                    }
                    
                    owner[res] = min_p_id;
                    Process& min_p = processes[min_p_id - 1];
                    min_p.held.insert(res);
                    min_p.state = "RUNNING";
                    min_p.wait_count = 0;

                    for (auto& r : reqs) {
                        if (r.first != min_p_id) {
                            Process& other = processes[r.first - 1];
                            handle_failure(other);
                        }
                    }
                }
            }
        }

        // 【阶段 2】：段中 - 计算收益
        for (auto& p : processes) {
            if (p.state == "RUNNING") {
                p.profit += p.held.size(); 
                p.run_time++;
            }
        }

        // 【阶段 3】：段末 - 任务结束与释放资源
        for (auto& p : processes) {
            if (p.state == "RUNNING" && p.run_time == p.tasks[p.cur_task].t) {
                if (p.cur_task == p.k - 1) {
                    p.state = "IDLE";
                    p.end_time = T;
                    for (int r : p.held) {
                        // 【第4点优化】：使用 OWNER_FREE
                        if (owner[r] == p.id) owner[r] = OWNER_FREE;
                    }
                    p.held.clear();
                } else {
                    p.cur_task++;
                    p.run_time = 0;
                    p.state = "APPLYING";
                }
            }
            
            if (p.will_release) {
                for (int r : p.held) {
                    // 【第4点优化】：使用 OWNER_FREE
                    if (owner[r] == p.id) owner[r] = OWNER_FREE;
                }
                p.held.clear();
                p.will_release = false;
            }
        }

        // 检查是否所有进程都结束了
        all_idle = true;
        for (auto& p : processes) {
            if (p.state != "IDLE") {
                all_idle = false;
                break;
            }
        }
        if (all_idle) break; 
    }

    // 3. 格式化输出结果
    for (auto& p : processes) {
        if (p.state != "IDLE") {
            cout << p.profit << " -1\n";
        } else {
            int duration = p.end_time - p.st + 1;
            cout << p.profit << " " << duration << "\n";
        }
    }

    return 0;
}