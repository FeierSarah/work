//动物识别产生式系统
//一、实验目的
//这是一个简单的动物识别产生式系统教学实例，通过本实验让学生理解并体会知识库与控制系统相互独立的智能产生式系统与一般程序的区别，为以后设计并实现复杂的专家系统奠定基础。
//二、实验内容
//设计并实现具有15条规则能自动识别7种动物的产生式系统。
//三.设计思想
//根据正向推理和反向推理，和已知的产生式规则推理出结果。
//五.源程序
//1.正向推理

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm> 
#include<stdlib.h>
#include<memory.h>

using namespace std;

char *animal[] = { "企鹅", "海燕", "鸵鸟", "斑马", "长颈鹿", "虎", "金钱豹" };

char *feature[] = { "有毛", "产奶", "有羽毛", "会飞", "会下蛋", "吃肉", "有犬齿", "有爪", "眼睛盯前方", "有蹄", "反刍", "黄褐色", "有斑点",

//    0        1      2       3      4         5       6       7         8        9      10       11    12

"有黑色条纹", "长脖", "长腿", "不会飞", "会游泳", "黑白两色", "善飞", "哺乳类", "鸟类", "肉食类", "蹄类",

//       13        14      15     16       17      18        19     20      21      22      23    

"企鹅", "海燕", "鸵鸟", "斑马", "长颈鹿", "虎", "金钱豹" };

//     24     25     26    27       28      29    30

typedef struct //存放规则的结构体

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

int flag[23] = { 0 };//标记各个特征是否选择

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

		cout << "\n输入选择（-1结束）：";

		cin >> ti;

		if (ti >= 0 && ti <= 23)

			flag[ti] = 1;

		else if (ti != -1)

		{

			cout << "输入错误!请输入0~23之间的数字!" << endl;  //notanimal=25

			cin.clear();//清除流错误错误标记

			cin.sync(); ////////////清空输入缓冲区

		}

	}

}

int IsAnimal(int a)

{

	if (a >= 24 && a <= 30)

		return 1;

	return 0;

}

int inference()//正向推理

{

	int ti;

	int i, j;

	int tres;

	cout << endl;

	for (i = 0; i<15; i++)

	{

		j = 0;

		ti = rule[i].relation[j];

		while (ti != -1) //-1作为结束

		{

			if (flag[ti] == 0)

				break;

			j++;

			ti = rule[i].relation[j];

		}

		if (ti == -1)//ti==-1代表规则满足

		{

			tres = rule[i].name;

			flag[tres] = 1;

			printf("运用了规则%d : ", i);

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
		cout << "没有这种动物";
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

		cout << "\n继续？(Y/N)" << endl;

		cin >> q;

		system("cls");

	}

}
