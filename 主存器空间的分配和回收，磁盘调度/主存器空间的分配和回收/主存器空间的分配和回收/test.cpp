#include <iostream>
using namespace std;
#define COUNT 512

//������ҵ�ṹ�������ҵ״̬
typedef struct Task
{
	char name;//����
	int start;//��ʼλ��
	int end;//��С
	int flag;//�Ƿ����ı�־
}Task;

//����ṹ������洢������ҵ״̬��������ҵ��
Task OS[COUNT];
int counts;//���ֳɵĿ���ͳ��

char c;//��ҵ��
int num;//��Դ������

//��ʼ��
void init()
{
	counts = 1;
	OS[0].name = 'P';//δ��������ΪP
	OS[0].start = 0;//��ʼλ��0
	OS[0].end = COUNT;
	OS[0].flag = 1;//�����־δ���� = 1
}

//������������
void insert(int m, int st, int en)
{
	int i;
	counts++;//���鳤�ȼ�һ
	for (i = counts; i > m ; i--)//�Ӳ���λ�ɺ���ǰ��������
	{
		OS[i] = OS[i - 1];
	}
	OS[m].start = st;//��������
	OS[m].end = en;
}

//ɾ����������
void move(int m)
{
	int i;
	for (i = m; i < counts - 1; i++)//��ɾ��λ��ǰ����ǰ������
	{
		OS[i] = OS[i + 1];
	}
	counts--;//���鳤�ȼ�һ
}

//�ϲ�û�з�������ڿ�
void remove(int m, int st, int en)
{
	if (!OS[m - 1].flag && !OS[m + 1].flag)
		//���mλ��ǰ���־���ѷ�������������������
	{
		OS[m].name = 'P';
		OS[m].flag = 1;
	}
	if (OS[m - 1].flag)
		//���mλ��ǰ��־δ���䣬���־�ѷ�������ǰһ���ϲ�
	{
		OS[m - 1].end = OS[m - 1].end + en;
		move(m);
	}
	if (OS[m + 1].flag)
		//���mλ�ú��־δ���䣬ǰ��־�ѷ��������һ���ϲ�
	{
		OS[m].end = OS[m].end + OS[m + 1].end;
		OS[m].name = 'P';
		OS[m].flag = 1;
		move(m + 1);
	}
}

//��ӡ���
void show()
{
	int i;
	cout << "(����  ��ʶ  ��ַ  ����  ״̬)" << endl;
	for (i = 0; i < counts; i++)
	{
		if (OS[i].flag)//δ����
			cout << "P    ";
		else//�ѷ���
			cout << OS[i].name << "    ";
		cout << i << "    " << OS[i].start << "    " << OS[i].end << "    ";
		//���������ı�ţ���ʼλ�ã�����
		if (OS[i].flag)
			cout << "δ����" << endl;
		else
			cout << "�ѷ���" << endl;
	}
}

//¼������
void put()
{
	cout << "������������ͷŵĽ������Ƽ���Դ����" << endl;
	cin >> c;
	cin >> num;
}

//������Դ
int apply()
{
	int i = 0;
	int applyflag = 0;//���
	while (!applyflag && i < counts)//����������������Ŀɷ�����Դ�Ƿ����
	{
		if (OS[i].end >= num && OS[i].flag)//ͨ���ȽϿ��С���Ƿ��ѷ���������Դ�ռ�
		{
			if (OS[i].end == num)//��С�����ֱ���޸���Ϣ
			{
				OS[i].name = c;
				OS[i].flag = 0;
			}
			else//��ƫ�����޸���Ϣͬʱ����ԭ�ȿ�Ϊ�ѷ����δ����������
			{
				insert(i + 1, OS[i].start + num, OS[i].end - num);
				OS[i + 1].flag = 1;
				OS[i + 1].name = 'P';
				OS[i].start = OS[i].start;
				OS[i].name = c;
				OS[i].end = num;
				OS[i].flag = 0;
			}
			applyflag = 1;//����ɹ����ı��
		}
		i++;
	}
	if (applyflag)
	{
		cout << "����ɹ�" << endl;
		return 1;
	}
	else
	{
		cout << "û���㹻��Ŀ��пռ�" << endl;
		return 0;
	}
}

//�ͷ���Դ
int free()
{
	int i = 0;
	int freeflag = 0;//���
	while (!freeflag && i < counts)//���������������Ӧ��ҵ�Ƿ����
	{
		if (OS[i].name == c)//�ҵ���ҵ
		{
			if (OS[i].end == num)//�ͷŴ�С��ȣ��ϲ�δ������
			{
				remove(i, OS[i].start, OS[i].end);
			}
			else
			{
				if (OS[i].end >num)//�ͷŴ�С���㣬���ѷ��������Ϊδ������ѷ���������
				{
					insert(i + 1, OS[i].start + num, OS[i].end - num);
					OS[i + 1].name = 'P';
					OS[i + 1].flag = 0;
					OS[i].end = num;
					OS[i].flag = 1;
					if (OS[i - 1].flag)//�ϲ�δ������
					{
						remove(i, OS[i].start, OS[i].end);
					}
				}
				else
				{
					cout << "��ʹ�õ�����С���ͷŵ�����" << endl;
					return 0;
				}
			}
			freeflag = 1;//�޸ı��
		}
		i++;
	}
	if (freeflag)
	{
		cout << "�ͷųɹ�" << endl;
		return 1;
	}
	else
	{
		cout << "δ�ҵ�ƥ��Ľ�������" << endl;
		return 0;
	}
}

//�˵�����
void menu()
{
	int code;	
	while (1)
	{
		cout << "����ѡ��" << endl << 
			"1.��ʼ��" << endl <<
			"2.���" << endl <<
			"3.����" << endl <<
			"4.�ͷ�" << endl <<
			"0.�˳�" << endl;
		cin >> code;
		//��ʼ��
		if (code == 1)
		{
			init();
		}
		//��ʾ���
		else if (code == 2)
		{
			show();
		}
		//����
		else if (code == 3)
		{
			put();
			apply();
			show();
		}
		//�ͷ�
		else if (code == 4)
		{
			put();
			free();
			show();
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
	menu();
	return 0;
}