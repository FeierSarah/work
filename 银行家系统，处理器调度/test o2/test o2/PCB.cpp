#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <malloc.h>
using namespace std;
#define N 5 //������������

void menu()
{
	int choose;
	//�������֡�ʱ�䡢���ȼ���״̬����洢��Ϣ
	string name[N];
	int n, time[N], prio[N];
	int prio1[N];//�����м����鸴�����ȼ����飬���ں���ָ������
	char state[N];
	//��������ģ��ָ��
	int array[N] = { 0 };
	//��¼�����еĽ�����
	int Count;
	while (1)//ѭ��ʵ�ֲ�������
	{
		//menu����
		cout << "1.��ʼ��" << endl;
		cout << "2.��ӡ" << endl;
		cout << "3.����" << endl;
		cout << "0.�˳�ϵͳ" << endl;
		cin >> choose;
		//�Ӽ��̼������ݳ�ʼ������
		if (choose == 1)
		{
			cout << "�����������";
			cin >> n;
			Count = n;//��ʼ�����н�����Ϊ������
			for (int i = 0; i < n; i++)
			{
				cout << "�����������ʱ�䡢������������״̬��";
				cin >> name[i] >> time[i] >> prio[i] >> state[i];
				array[i] = i;//��ʼָ��Ϊ����˳��
			}
		}
		//������ʾ��������
		else if (choose == 2)
		{
			cout << "��ʱ�����б�Ϊ��" << endl;
			cout << "������ ���ȼ� ʱ�� ״̬��" << endl;
			for (int i = 0; i < n; i++)
			{
				cout << name[i] << " " << prio[i] << " " << time[i] << " " << state[i] << endl;
			}
		}
		//������н��
		else if (choose == 3)
		{
			//���ж��Ƿ��д�ִ�еĽ���
			if (Count>0)
			{
				int count = n;
				//����ʼ���ȼ��͸��µ����ȼ������м�����
				for (int i = 0; i < n; i++)
				{
					prio1[i] = prio[i];
				}
				while (count != 0)//�Ƚ����ȼ����ı�ָ������
				{
					int tmp = 0;
					for (int i = 0; i < n; i++)
					{
						if (prio1[i] > prio1[tmp])
							tmp = i;
					}
					prio1[tmp] = 0;//������ָ����м������Ϊ0
					array[n - count] = tmp;
					count--;
				}
				//����ָ�����������һ������
				cout << "��ʱִ�н���Ϊ��" << name[array[0]] << endl;
				//����֮�����ȼ����ͣ�ʱ�����
				prio[array[0]] -= 1;
				time[array[0]] -= 1;
				//�Ƚϸ��º�����ȼ����ҳ���һ�����н���
				cout << "֮���������Ϊ��";
				//��������ǣ�����н���ʱ��Ϊ0������״̬��Count,�������ȼ�����Ϊһ���㹻С��ֵ
				if (time[array[0]] == 0)
				{
					state[array[0]] = 'E';
					prio[array[0]] = -100;//�����ȼ�����Ϊһ���㹻С��ֵ
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
				cout << "û�п�ִ�еĽ���" << endl;
				break;
			}

		}
		//�����˳���������ѭ��
		else if (choose == 0)
		{
			break;
		}
		else
			cout << "������Ч������������" << endl;
	}
}

int main()
{
	menu();
	return 0;
}
