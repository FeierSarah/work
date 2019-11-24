#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#define MAX_I 100//设置最大进程数
#define MAX_J 100//设置最大资源种数

int i;//进程数
int j;//资源种数
//定义结构体：资源和进程
struct Available
{
	int j_num;//剩余资源数
	int Work;//系统可提供给进程继续运行所需的各类资源数目
}Ava[MAX_J];

struct IProcess
{
	int Max[MAX_J];//最大需求
	int Allocation[MAX_J];//已经分配
	int Need[MAX_J];//剩余需求
	int Requesti[MAX_J];//发出请求
	bool Count;//中间参数，判断命令是否执行
	bool Finish[MAX_J];//判断安全状态
}IPro[MAX_I];

//使结构体参数初始为0或false
void Init1()
{
	for (int a = 0; a < MAX_J; a++)
	{
		Ava[MAX_J].j_num = Ava[MAX_J].Work = 0;
	}
	for (int a = 0; a < MAX_I; a++)
	{
		for (int b = 0; b < MAX_J; b++)
		{
			IPro[i].Max[j] = 0;
			IPro[i].Allocation[j] = 0;
			IPro[i].Need[j] = 0;
			IPro[i].Requesti[j] = 0;
			IPro[i].Count = false;
			IPro[i].Finish[j] = false;
		}
	}
}

//从键盘键入数据获得基本矩阵信息
void Init2(int i, int j)
{
	cout << "资源种类数为：" << j << endl;
	for (int a = 0; a < j; a++)
	{
		cout << "第" << a + 1 << "种资源数为：";
		cin >> Ava[a].j_num;
		Ava[a].Work = Ava[a].j_num;//使资源剩余数与资源数相等
	}
	cout << "进程总数为：" << i << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << "第" << a + 1 << "个进程对第" << b + 1 <<
				"种资源的最大需求为：";
			//判断资源最大需求是否超出资源数，超出，则重新输入
			while (!IPro[a].Count)
			{
				cin >> IPro[a].Max[b];
				if (IPro[a].Max[b] <= Ava[b].Work)
				{
					IPro[a].Count = true;
					break;
				}
				else
					cout << "超出资源总数，重新输入：";
			}
			cout << "第" << a + 1 << "个进程对第" << b + 1 <<
				"种资源的已分得数为：";
			while (IPro[a].Count)
			{
				cin >> IPro[a].Allocation[b];
				//判断已经分配是否超出最大需求，超出，则重新输入
				if (IPro[a].Allocation[b] <= IPro[a].Max[b])
				{
					//判断已经分配是否超出资源数，超出，则重新输入
					if (IPro[a].Allocation[b] <= Ava[b].j_num)
					{
						//更新剩余资源数
						Ava[b].j_num -= IPro[a].Allocation[b];
						cout << "第" << b + 1
							<< "种资源数剩余为：" << Ava[b].j_num << endl;
						IPro[a].Count = false;//更改中间参数
					}
					else
						cout << "超出资源总数，重新输入：";
				}
				else
					cout << "超出资源需求，重新输入：";
			}
			//根据已知获得剩余需求 Need［i,j］=Max［i,j］-Allocation［i,j］
			IPro[a].Need[b] = IPro[a].Max[b] - IPro[a].Allocation[b];
		}
	}
}

//分配函数：为进程分配相应资源
void Request(int i, int j)
{
	cout << "输入对第" << i + 1 << "个进程对第" << j + 1 << "种资源的申请量：";
	while (!IPro[i].Count)
	{
		cin >> IPro[i].Requesti[j];
		//判断即将分配是否超出剩余需求，超出，则重新输入
		if (IPro[i].Requesti[j] <= IPro[i].Need[j])
		{
			//判断即将分配是否超出资源数，超出，则重新输入
			if (IPro[i].Requesti[j] <= Ava[j].j_num)
			{
				//更新已经分配
				IPro[i].Allocation[j] += IPro[i].Requesti[j];
				//更新剩余需求
				IPro[i].Need[j] -= IPro[i].Requesti[j];
				//更新资源剩余数
				Ava[j].j_num -= IPro[i].Requesti[j];
				cout << "申请成功" << endl;
				IPro[i].Count = true;//更改中间参数
			}
			else
				cout << "输入超出总量，重新输入：";
		}
		else
			cout << "输入超出需求，重新输入：";
	}
	IPro[i].Count = false;
}

//输出矩阵函数
void Print()
{
	for (int a = 0; a < i; a++)
	{
		cout << a;
		for (int b = 0; b < 2 * j; b++)
		{
			cout << " ";
		}
	}
	cout << "(进程)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << Ava[b].Work << " ";
		}
		cout << " ";
	}
	cout << "(资源总数)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << Ava[b].j_num << " ";
		}
		cout << " ";
	}
	cout << "(剩余资源)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << IPro[a].Max[b] << " ";
		}
		cout << " ";
	}
	cout << "(最大需求)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << IPro[a].Allocation[b] << " ";
		}
		cout << " ";
	}
	cout << "(已经分配)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << IPro[a].Need[b] << " ";
		}
		cout << " ";
	}
	cout << "(剩余需求)" << endl;
}

//更新work,finish为后面更新安全性
void test()
{
	//若各进程最大需求总和小于资源总数，更新finish为true
	for (int a = 0; a < j; a++)
	{
		int count = 0;
		for (int b = 0; b < i; b++)
		{
			count += IPro[b].Max[a];
			if (count <= Ava[a].Work)
			{
				for (int c = 0; c < j; c++)
				{
					IPro[b].Need[c] = true;
				}
			}
		}
	}
}

//安全性检测
bool Safe()
{
	//如果所有进程的Finish［i］ = true都满足， 
	//则表示系统处于安全状态；否则，系统处于不安全状态
	test();
	int flag = 1;
	//循环判断各进程是否安全
	for (int a = 0; a < i; a++)
	{
		if (flag == 0)
			break;
		for (int b = 0; b < j; b++)
		{
			if (!IPro[a].Finish[b])
			{
				flag = 0;
				break;
			}
		}
	}
	if (flag)
	{
		cout << "系统状态安全" << endl;
		return true;
	}
	else
	{
		cout << "系统状态不安全" << endl;
		return false;
	}
}

//银行家算法
void banker() {
	//判断安全性，安全则分配
	if (Safe())
	{
		char k;
		cout << "是否分配(y/n)";
		cin >> k;
		if (k == 'y')
		{
			int a, b;
			cout << "输入进程数和资源个数：";
			cin >> a >> b;
			Request(a - 1, b - 1);
		}
	}
	else
		cout << "不允许分配" << endl;
}

//菜单函数
void menu() 
{	
	int code;
	while (1) 
	{
		cout << endl << "请输入指令" << endl <<
			"1.初始化" << endl <<
			"2.显示矩阵" << endl <<
			"3.判断安全性" << endl <<
			"4.申请资源" << endl <<
			"0.退出" << endl;
		cin >> code;
		//键盘键入初始化矩阵
		if (code == 1)
		{
			Init1();
			cout << "输入进程数和资源个数：";
			cin >> i >> j;
			Init2(i, j);
		}
		//显示矩阵
		else if (code == 2)
		{
			Print();
		}
		//判断安全性
		else if (code == 3)
		{
			Safe();
		}
		//申请资源
		else if (code == 4)
		{
			cout << "是否使用银行家算法保证安全性（y/n）" << endl;
			char k;
			cin >> k;
			//申请资源前是否进行安全性检测
			if (k == 'y')
			{
				banker();
			}
			else
			{
				int a, b;
				cout << "输入进程数和资源个数：";
				cin >> a >> b;
				Request(a - 1, b - 1);
			}
		}
		//退出操作
		else if (code == 0)
		{
			return;
		}
		else
			cout << "命令无效，请重新输入" << endl;
	}

}

int main()
{
	Init1();//正式开始前初始矩阵为0
	menu();
	getchar();
	return 0;
}