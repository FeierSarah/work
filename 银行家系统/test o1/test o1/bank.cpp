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
	cout << "��Դ������Ϊ��" << j << endl;
	for (int a = 0; a < j; a++)
	{
		cout << "��" << a + 1 << "����Դ��Ϊ��" ;
		cin >> Ava[a].j_num;
		Ava[a].num = Ava[a].j_num;
	}
	cout << "��������Ϊ��" << i << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << "��" << a + 1 << "�����̶Ե�" << b + 1 <<
				"����Դ���������Ϊ��" ;
			while (!IPro[a].Count)
			{
				cin >> IPro[a].Max[b];
				if (IPro[a].Max[b] <= Ava[b].num)
				{
					IPro[a].Count = true;
					break;
				}
				else
					cout << "������Դ�������������룺";
			}
			cout << "��" << a + 1 << "�����̶Ե�" << b + 1 <<
				"����Դ���ѷֵ���Ϊ��";
			while (IPro[a].Count)
			{
				cin >> IPro[a].Allocation[b]; 
				if (IPro[a].Allocation[b] <= IPro[a].Max[b])
				{
					if (IPro[a].Allocation[b] <= Ava[b].j_num)
					{
						IPro[a].Count = 1;
						Ava[b].j_num -= IPro[a].Allocation[b];
						cout << "��" << b + 1
							<< "����Դ��ʣ��Ϊ��" << Ava[b].j_num << endl;
						IPro[a].Count = false;
					}
					else
						cout << "������Դ�������������룺";
				}
				else
					cout << "������Դ�����������룺";
			}
			IPro[a].Need[b] = IPro[a].Max[b] - IPro[a].Allocation[b];
		}
	}
}

void Request(int i,int j)
{
	cout << "����Ե�" << i + 1 << "�����̶Ե�" << j + 1 << "����Դ����������";
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
				cout << "����ɹ�" << endl;
				IPro[i].Count = true;
			}
			else
				cout << "���볬���������������룺";
		}
		else
			cout << "���볬�������������룺";
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
	cout << "(����)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << Ava[b].num << " ";
		}
		cout << " ";
	}
	cout << "(��Դ����)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << Ava[b].j_num << " ";
		}
		cout << " ";
	}
	cout << "(ʣ����Դ)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << IPro[a].Max[b] << " ";
		}
		cout << " ";
	}
	cout << "(�������)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << IPro[a].Allocation[b] << " ";
		}
		cout << " ";
	}
	cout << "(�Ѿ�����)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << IPro[a].Need[b] << " ";
		}
		cout << " ";
	}
	cout << "(ʣ������)\n";
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
		cout << "ϵͳ״̬��ȫ" << endl;
		return true;
	}
	else 
	{
		cout << "ϵͳ״̬����ȫ" << endl;
		return false;
	}
}

void banker() {//���м��㷨
	if (Safe()) 
	{
		char k;
		cout << "�Ƿ����(y/n)";
		cin >> k;
		if (k == 'y')
		{
			int a, b;
			cout << "�������������Դ������" << a << b;
			Request(a - 1, b - 1);
		}
	}
	else 
		cout << "���������" << endl;
}

void menu() {	//�˵�����
	int code;
	while (1) {
		cout << endl << "������ָ��" << endl <<
			"1.��ʼ��" << endl <<
			"2.��ʾ����" << endl <<
			"3.�жϰ�ȫ��" << endl <<
			"4.������Դ" << endl <<
			"0.�˳�" << endl;
		cin >> code;
		if (code == 1) 
		{	
			Init1();
			cout << "�������������Դ������";
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
			cout << "�Ƿ�ʹ�����м��㷨��֤��ȫ�ԣ�y/n��" << endl;
			char k;
			cin >> k;
			if (k == 'y')
			{
				banker();
			}
			else
			{
				int a, b;
				cout << "�������������Դ������";
				cin>>a >> b;
				Request(a - 1, b - 1);
			}
		}
		else if (code == 0) 
		{	
			return;
		}
		else 
			cout << "������Ч������������" << endl;
	}

}

int main()
{
	Init1();
	menu();
	getchar();
	return 0;
}