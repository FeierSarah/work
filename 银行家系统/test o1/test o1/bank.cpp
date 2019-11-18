#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#define MAX_I 100
#define MAX_J 100

int i;
int j;
struct Available
{
	int j_num;
	int num;
	int Work;
}Ava[MAX_J];

struct IProcess
{
	int Max[MAX_J];
	int Allocation[MAX_J];
	int Need[MAX_J];
	int Requesti[MAX_J];
	bool Count;
	bool Finish;
}IPro[MAX_I];

void Init1()
{
	for (int a = 0; a < MAX_J; a++)
	{
		Ava[MAX_J].j_num = Ava[MAX_J].num = 0;
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
			IPro[i].Finish = false;
		}
	}
}

void Init2(int i, int j)
{
	cout << "资源种类数为：" << j << endl;
	for (int a = 0; a < j; a++)
	{
		cout << "第" << a + 1 << "种资源数为：" ;
		cin >> Ava[a].j_num;
		Ava[a].num = Ava[a].j_num;
	}
	cout << "进程总数为：" << i << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << "第" << a + 1 << "个进程对第" << b + 1 <<
				"种资源的最大需求为：" ;
			while (!IPro[a].Count)
			{
				cin >> IPro[a].Max[b];
				if (IPro[a].Max[b] <= Ava[b].num)
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
				if (IPro[a].Allocation[b] <= IPro[a].Max[b])
				{
					if (IPro[a].Allocation[b] <= Ava[b].j_num)
					{
						IPro[a].Count = 1;
						Ava[b].j_num -= IPro[a].Allocation[b];
						cout << "第" << b + 1
							<< "种资源数剩余为：" << Ava[b].j_num << endl;
						IPro[a].Count = false;
					}
					else
						cout << "超出资源总数，重新输入：";
				}
				else
					cout << "超出资源需求，重新输入：";
			}
			IPro[a].Need[b] = IPro[a].Max[b] - IPro[a].Allocation[b];
		}
	}
}

void Request(int i,int j)
{
	cout << "输入对第" << i + 1 << "个进程对第" << j + 1 << "种资源的申请量：";
	while (!IPro[i].Count)
	{
		cin >> IPro[i].Requesti[j];
		if (IPro[i].Requesti[j] <= IPro[i].Need[j])
		{
			if (IPro[i].Requesti[j] <= Ava[j].j_num)
			{
				IPro[i].Count = 0;
				IPro[i].Allocation[j] += IPro[i].Requesti[j];
				IPro[i].Need[j] -= IPro[i].Requesti[j];
				Ava[j].j_num -= IPro[i].Requesti[j];
				cout << "申请成功" << endl;
				IPro[i].Count = true;
			}
			else
				cout << "输入超出总量，重新输入：";
		}
		else
			cout << "输入超出需求，重新输入：";
	}
	IPro[i].Count = false;
}

void Print()
{
	for (int a = 0; a < i; a++)
	{
		cout << a;
		for (int b = 0; b < 2 * j ; b++)
		{
			cout << " ";
		}
	}
	cout << "(进程)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << Ava[b].num << " ";
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
	cout << "(剩余需求)\n";
}

void test()
{
	for (int a = 0; a < i; a++)
	{
		int flag = 1;
		if (!IPro[a].Finish)
		{
			for (int b = 0; b < j; b++)
			{
				if (IPro[a].Need[b] > Ava[b].Work)
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				for (int b = 0; b < j; b++)
				{
					Ava[b].Work += IPro[a].Allocation[b];
					IPro[i].Finish = true;
				}
				test();
			}
		}
	}
}

bool Safe()
{
	for (int a = 0; a < j; a++) 
	{
		Ava[j].Work = Ava[j].num;
	}
	test();
	int flag = 1;
	for (int a = 0; a < i; a++) 
	{
		if (!IPro[a].Finish) 
		{
			flag = 0;
			break;
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

void banker() {//银行家算法
	if (Safe()) 
	{
		char k;
		cout << "是否分配(y/n)";
		cin >> k;
		if (k == 'y')
		{
			int a, b;
			cout << "输入进程数和资源个数：" << a << b;
			Request(a - 1, b - 1);
		}
	}
	else 
		cout << "不允许分配" << endl;
}

void menu() {	//菜单函数
	int code;
	while (1) {
		cout << endl << "请输入指令" << endl <<
			"1.初始化" << endl <<
			"2.显示矩阵" << endl <<
			"3.判断安全性" << endl <<
			"4.申请资源" << endl <<
			"0.退出" << endl;
		cin >> code;
		if (code == 1) 
		{	
			Init1();
			cout << "输入进程数和资源个数：";
			cin >> i >> j;
			Init2(i, j);
		}
		else if (code == 2) 
		{	
			Print();
		}
		else if (code == 3) 
		{	
			Safe();
		}
		else if (code == 4) 
		{
			cout << "是否使用银行家算法保证安全性（y/n）" << endl;
			char k;
			cin >> k;
			if (k == 'y')
			{
				banker();
			}
			else
			{
				int a, b;
				cout << "输入进程数和资源个数：";
				cin>>a >> b;
				Request(a - 1, b - 1);
			}
		}
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
	Init1();
	menu();
	getchar();
	return 0;
}