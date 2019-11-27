#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <malloc.h>
using namespace std;
#define N 5 //设置最大进程数

void menu()
{
	int choose;
	//定义名字、时间、优先级、状态数组存储信息
	string name[N];
	int n, time[N], prio[N];
	int prio1[N];//设置中间数组复制优先级数组，便于后面指针排序
	char state[N];
	//定义数组模拟指针
	int array[N] = { 0 };
	//记录待运行的进程数
	int Count;
	while (1)//循环实现步骤输入
	{
		//menu界面
		cout << "1.初始化" << endl;
		cout << "2.打印" << endl;
		cout << "3.运行" << endl;
		cout << "0.退出系统" << endl;
		cin >> choose;
		//从键盘键入数据初始化进程
		if (choose == 1)
		{
			cout << "输入进程数：";
			cin >> n;
			Count = n;//初始待运行进程数为进程数
			for (int i = 0; i < n; i++)
			{
				cout << "输入进程名、时间、优先数、运行状态：";
				cin >> name[i] >> time[i] >> prio[i] >> state[i];
				array[i] = i;//初始指针为键入顺序
			}
		}
		//依次显示输入数据
		else if (choose == 2)
		{
			cout << "此时进程列表为：" << endl;
			cout << "（进程 优先级 时间 状态）" << endl;
			for (int i = 0; i < n; i++)
			{
				cout << name[i] << " " << prio[i] << " " << time[i] << " " << state[i] << endl;
			}
		}
		//输出运行结果
		else if (choose == 3)
		{
			//先判断是否有待执行的进程
			if (Count>0)
			{
				int count = n;
				//将初始优先级和更新的优先级传给中间数组
				for (int i = 0; i < n; i++)
				{
					prio1[i] = prio[i];
				}
				while (count != 0)//比较优先级，改变指针数组
				{
					int tmp = 0;
					for (int i = 0; i < n; i++)
					{
						if (prio1[i] > prio1[tmp])
							tmp = i;
					}
					prio1[tmp] = 0;//将加入指针的中间数组改为0
					array[n - count] = tmp;
					count--;
				}
				//根据指针数组输出第一个进程
				cout << "此时执行进程为：" << name[array[0]] << endl;
				//运行之后优先级降低，时间更新
				prio[array[0]] -= 1;
				time[array[0]] -= 1;
				//比较更新后的优先级，找出下一个运行进程
				cout << "之后进程运行为：";
				//分情况考虑，如果有进程时间为0，更新状态和Count,并把优先级更新为一个足够小的值
				if (time[array[0]] == 0)
				{
					state[array[0]] = 'E';
					prio[array[0]] = -100;//把优先级更新为一个足够小的值
				}
				if (prio[array[0]] <= prio[array[1]])
				{
					cout << name[array[1]] << endl;
				}
				else
				{
					cout << name[array[0]] << endl;
				}
			}
			else
			{
				cout << "没有可执行的进程" << endl;
				break;
			}

		}
		//设置退出程序，跳出循环
		else if (choose == 0)
		{
			break;
		}
		else
			cout << "命令无效，请重新输入" << endl;
	}
}

int main()
{
	menu();
	return 0;
}
