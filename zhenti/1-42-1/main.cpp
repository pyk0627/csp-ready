/*
以下是图片中内容的完整还原：

202606-1银行家舍入

题目背景

IEEE二进制浮点数算术标准（IEEE 754）是20世纪80年代以来最广泛使用的浮点数运算标准，为许多CPU与浮点运算器所采用。银行家舍入法（Banker's Rounding），又称“向偶数舍入”（round half to even），是IEEE 754推荐的默认舍入方式。

题目描述

小P的实验表格里有$n$个形如xxx.x的、保留一位小数的非负实数，其中：

· 小数点前的xxx表示整数部分$a$，为任意非负整数；
· 小数点后的x表示小数部分$b$，为一位数字，取值0~9；
· $a$可以是任意位数（如2026、531或0）；$b$必为一位，且当$b=0$时不会省略（如13.0）。

为方便统计分析，小P想将它们都近似为整数，具体定义两种计算方式。

1. 四舍五入法

· 当$0 \leq b \leq 4$时，向下舍去，结果为$a$；
· 当$5 \leq b \leq 9$时，向上进位，结果为$a+1$。

2. 银行家舍入法（向偶数舍入）

· 当$b \neq 5$时，处理与四舍五入法一致（$b \leq 4$向下、$b \geq 6$向上）。
· 当$b = 5$时，由于$a+0.5$与相邻整数$a$和$a+1$的距离相同，为避免系统性偏差，向偶数舍入：若$a$为偶数，则结果为$a$；否则结果为$a+1$。
X
现给出小P表格中的$n$个实数（格式如上）。对每个实数，分别计算上述两种方法的取整结果。

输入格式

从标准输入读入数据。

· 第一行包含一个正整数$n$，表示实数个数。
· 接下来$n$行，每行一个实数，格式与题目描述相符。建议按字符串读取并按规则解析（以避免浮点解析误差），也可采用其他合理方式处理。

输出格式

输出到标准输出。
输出共两行：

· 第一行输出空格分隔的$n$个整数，表示采用四舍五入法得到的结果；
· 第二行输出空格分隔的$n$个整数，表示采用银行家舍入法得到的结果。

样例输入

```
4
7.5
0.0
13.9
2026.5
```

样例输出

```
8 0 14 2027
8 0 14 2026
```

样例解释

对于最后一个实数2026.5，采用四舍五入法进位到2027，而采用银行家舍入法则取相邻的偶数2026。

子任务

50%的测试数据满足：不存在小数部分$b=5$的情况，即两种舍入方法结果相同；
全部的测试数据满足：$n \leq 100$且每个实数的整数部分$a \leq 10^5$。

提示

不同编程语言的内置函数（如round()）可能采用不同的舍入策略，建议按照题目描述自行实现上述两种舍入算法。
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    vector<int> res1;
    vector<int> res2;
    //接受输入怎么写？
    //怎么把接受的数字以小数点分开？
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        string str;
        cin>>str;

        //用string中的find来找到小数点的位置
        size_t pos=str.find('.');
        string a=str.substr(0,pos);
        string b=str.substr(pos+1);
        
        int numa=0;
        int numbera=stoi(a);
        //1
        if(b[0]>='5')
        {
            numa=numbera+1;
        }else
        {
            numa=numbera;
        }
        res1.push_back(numa);

        //2
        if(b[0]>='6')
        {
            numa=numbera+1;
        }else if(b[0]=='5')
        {
            if(numbera%2==0)
            {
                numa=numbera;
            }else
            {
                numa=numbera+1;
            }
        }else
        {
            numa=numbera;
        }
        res2.push_back(numa);
    }

    for(auto x:res1)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    for(auto x:res2)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}
