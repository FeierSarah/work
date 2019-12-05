//����ʶ�����ʽϵͳ
//һ��ʵ��Ŀ��
//����һ���򵥵Ķ���ʶ�����ʽϵͳ��ѧʵ����ͨ����ʵ����ѧ����Ⲣ���֪ʶ�������ϵͳ�໥���������ܲ���ʽϵͳ��һ����������Ϊ�Ժ���Ʋ�ʵ�ָ��ӵ�ר��ϵͳ�춨������
//����ʵ������
//��Ʋ�ʵ�־���15���������Զ�ʶ��7�ֶ���Ĳ���ʽϵͳ��
//��.���˼��
//������������ͷ�����������֪�Ĳ���ʽ��������������
//��.Դ����
//1.��������

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm> 
#include<stdlib.h>
#include<memory.h>

using namespace std;

char *animal[] = { "���", "����", "����", "����", "����¹", "��", "��Ǯ��" };

char *feature[] = { "��ë", "����", "����ë", "���", "���µ�", "����", "��Ȯ��", "��צ", "�۾���ǰ��", "����", "��ۻ", "�ƺ�ɫ", "�аߵ�",

//    0        1      2       3      4         5       6       7         8        9      10       11    12

"�к�ɫ����", "����", "����", "�����", "����Ӿ", "�ڰ���ɫ", "�Ʒ�", "������", "����", "��ʳ��", "����",

//       13        14      15     16       17      18        19     20      21      22      23    

"���", "����", "����", "����", "����¹", "��", "��Ǯ��" };

//     24     25     26    27       28      29    30

typedef struct //��Ź���Ľṹ��

{

	int relation[5];

	int name;

}Rule;

Rule rule[15] = {

	{ { 0, -1 }, 20 },

	{ { 1, -1 }, 20 },

	{ { 2, -1 }, 21 },

	{ { 3, 4, -1 }, 21 },

	{ { 20, 5, -1 }, 22 },

	{ { 6, 7, 8, -1 }, 22 },

	{ { 20, 8, -1 }, 23 },

	{ { 20, 9, -1 }, 23 },

	{ { 22, 11, 12, -1 }, 30 },

	{ { 22, 11, 13, -1 }, 29 },

	{ { 23, 14, 15, 12, -1 }, 28 },

	{ { 23, 13, -1 }, 27 },

	{ { 21, 14, 15, 16, -1 }, 26 },

	{ { 21, 19, -1 }, 25 },

	{ { 21, 17, 18, 16, -1 }, 24 } };

int flag[23] = { 0 };//��Ǹ��������Ƿ�ѡ��

int IsAnimal(int a);

int inference();

void input();

void menu();



void menu()

{

	int i = 0;

	for (i = 0; i<24; i++)

	{

		if (i % 4 == 0 && i != 0)

		{

			cout << endl;

		}

		printf("%-3d.%-15s", i, feature[i]);



	}

}

void input()

{

	int ti = 0;

	for (int i = 0; i<24; i++)

	{

		flag[i] = 0;

	}

	while (ti != -1)

	{

		cout << "\n����ѡ��-1��������";

		cin >> ti;

		if (ti >= 0 && ti <= 23)

			flag[ti] = 1;

		else if (ti != -1)

		{

			cout << "�������!������0~23֮�������!" << endl;  //notanimal=25

			cin.clear();//��������������

			cin.sync(); ////////////������뻺����

		}

	}

}

int IsAnimal(int a)

{

	if (a >= 24 && a <= 30)

		return 1;

	return 0;

}

int inference()//��������

{

	int ti;

	int i, j;

	int tres;

	cout << endl;

	for (i = 0; i<15; i++)

	{

		j = 0;

		ti = rule[i].relation[j];

		while (ti != -1) //-1��Ϊ����

		{

			if (flag[ti] == 0)

				break;

			j++;

			ti = rule[i].relation[j];

		}

		if (ti == -1)//ti==-1�����������

		{

			tres = rule[i].name;

			flag[tres] = 1;

			printf("�����˹���%d : ", i);

			j = 0;

			while (rule[i].relation[j] != -1)

			{

				cout << feature[rule[i].relation[j]] << " ";

				j++;

			}

			cout << "====> " << feature[tres] << endl;

			if (IsAnimal(tres))

			{

				return 1;

			}

		}

	}

	if (i == 15)

	{
		cout << "û�����ֶ���";
	}

	return -1;

}

void main()

{

	char q;

	while (q != 'n')

	{

		menu();

		input();

		inference();

		cout << "\n������(Y/N)" << endl;

		cin >> q;

		system("cls");

	}

}
