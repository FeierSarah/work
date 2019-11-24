#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#define MAX_I 100//������������
#define MAX_J 100//���������Դ����

int i;//������
int j;//��Դ����
//����ṹ�壺��Դ�ͽ���
struct Available
{
	int j_num;//ʣ����Դ��
	int Work;//ϵͳ���ṩ�����̼�����������ĸ�����Դ��Ŀ
}Ava[MAX_J];

struct IProcess
{
	int Max[MAX_J];//�������
	int Allocation[MAX_J];//�Ѿ�����
	int Need[MAX_J];//ʣ������
	int Requesti[MAX_J];//��������
	bool Count;//�м�������ж������Ƿ�ִ��
	bool Finish[MAX_J];//�жϰ�ȫ״̬
}IPro[MAX_I];

//ʹ�ṹ�������ʼΪ0��false
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

//�Ӽ��̼������ݻ�û���������Ϣ
void Init2(int i, int j)
{
	cout << "��Դ������Ϊ��" << j << endl;
	for (int a = 0; a < j; a++)
	{
		cout << "��" << a + 1 << "����Դ��Ϊ��";
		cin >> Ava[a].j_num;
		Ava[a].Work = Ava[a].j_num;//ʹ��Դʣ��������Դ�����
	}
	cout << "��������Ϊ��" << i << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << "��" << a + 1 << "�����̶Ե�" << b + 1 <<
				"����Դ���������Ϊ��";
			//�ж���Դ��������Ƿ񳬳���Դ��������������������
			while (!IPro[a].Count)
			{
				cin >> IPro[a].Max[b];
				if (IPro[a].Max[b] <= Ava[b].Work)
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
				//�ж��Ѿ������Ƿ񳬳�������󣬳���������������
				if (IPro[a].Allocation[b] <= IPro[a].Max[b])
				{
					//�ж��Ѿ������Ƿ񳬳���Դ��������������������
					if (IPro[a].Allocation[b] <= Ava[b].j_num)
					{
						//����ʣ����Դ��
						Ava[b].j_num -= IPro[a].Allocation[b];
						cout << "��" << b + 1
							<< "����Դ��ʣ��Ϊ��" << Ava[b].j_num << endl;
						IPro[a].Count = false;//�����м����
					}
					else
						cout << "������Դ�������������룺";
				}
				else
					cout << "������Դ�����������룺";
			}
			//������֪���ʣ������ Need��i,j��=Max��i,j��-Allocation��i,j��
			IPro[a].Need[b] = IPro[a].Max[b] - IPro[a].Allocation[b];
		}
	}
}

//���亯����Ϊ���̷�����Ӧ��Դ
void Request(int i, int j)
{
	cout << "����Ե�" << i + 1 << "�����̶Ե�" << j + 1 << "����Դ����������";
	while (!IPro[i].Count)
	{
		cin >> IPro[i].Requesti[j];
		//�жϼ��������Ƿ񳬳�ʣ�����󣬳���������������
		if (IPro[i].Requesti[j] <= IPro[i].Need[j])
		{
			//�жϼ��������Ƿ񳬳���Դ��������������������
			if (IPro[i].Requesti[j] <= Ava[j].j_num)
			{
				//�����Ѿ�����
				IPro[i].Allocation[j] += IPro[i].Requesti[j];
				//����ʣ������
				IPro[i].Need[j] -= IPro[i].Requesti[j];
				//������Դʣ����
				Ava[j].j_num -= IPro[i].Requesti[j];
				cout << "����ɹ�" << endl;
				IPro[i].Count = true;//�����м����
			}
			else
				cout << "���볬���������������룺";
		}
		else
			cout << "���볬�������������룺";
	}
	IPro[i].Count = false;
}

//���������
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
	cout << "(����)" << endl;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			cout << Ava[b].Work << " ";
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
	cout << "(ʣ������)" << endl;
}

//����work,finishΪ������°�ȫ��
void test()
{
	//����������������ܺ�С����Դ����������finishΪtrue
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

//��ȫ�Լ��
bool Safe()
{
	//������н��̵�Finish��i�� = true�����㣬 
	//���ʾϵͳ���ڰ�ȫ״̬������ϵͳ���ڲ���ȫ״̬
	test();
	int flag = 1;
	//ѭ���жϸ������Ƿ�ȫ
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
		cout << "ϵͳ״̬��ȫ" << endl;
		return true;
	}
	else
	{
		cout << "ϵͳ״̬����ȫ" << endl;
		return false;
	}
}

//���м��㷨
void banker() {
	//�жϰ�ȫ�ԣ���ȫ�����
	if (Safe())
	{
		char k;
		cout << "�Ƿ����(y/n)";
		cin >> k;
		if (k == 'y')
		{
			int a, b;
			cout << "�������������Դ������";
			cin >> a >> b;
			Request(a - 1, b - 1);
		}
	}
	else
		cout << "���������" << endl;
}

//�˵�����
void menu() 
{	
	int code;
	while (1) 
	{
		cout << endl << "������ָ��" << endl <<
			"1.��ʼ��" << endl <<
			"2.��ʾ����" << endl <<
			"3.�жϰ�ȫ��" << endl <<
			"4.������Դ" << endl <<
			"0.�˳�" << endl;
		cin >> code;
		//���̼����ʼ������
		if (code == 1)
		{
			Init1();
			cout << "�������������Դ������";
			cin >> i >> j;
			Init2(i, j);
		}
		//��ʾ����
		else if (code == 2)
		{
			Print();
		}
		//�жϰ�ȫ��
		else if (code == 3)
		{
			Safe();
		}
		//������Դ
		else if (code == 4)
		{
			cout << "�Ƿ�ʹ�����м��㷨��֤��ȫ�ԣ�y/n��" << endl;
			char k;
			cin >> k;
			//������Դǰ�Ƿ���а�ȫ�Լ��
			if (k == 'y')
			{
				banker();
			}
			else
			{
				int a, b;
				cout << "�������������Դ������";
				cin >> a >> b;
				Request(a - 1, b - 1);
			}
		}
		//�˳�����
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
	Init1();//��ʽ��ʼǰ��ʼ����Ϊ0
	menu();
	getchar();
	return 0;
}