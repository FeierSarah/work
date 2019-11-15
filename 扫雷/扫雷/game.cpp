#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#define MAX_ROW 9
#define MAX_COL 9
#define MINE_COUNT 10
//扫雷思路
//1.使用二维数组表示地图
//a）show_map表示每个位置是否被翻开，b)mine_map表示位置是否是地雷
//a)'0'表示不是地雷，'1'表示是地雷
//a)*表示未翻开，'1'表示周围8个格子中有几个地雷
//2.初始化
//a)show_map来说初始化全成为*
//b)mine_map先初始化全成为'0',然后随机生成10个位置作为地雷
//3.打印地图（show_map）
//4.让用户输入一组坐标，需要检查坐标的合法性
//5.判定当前位置如果是地雷，提示GameOver
//6.如果不是地雷，判定是否游戏胜利(胜利条件是翻开了所有不是地雷的格子)
//7.如果不是地雷，就需要更新一个数字，这个数字表示周围八个格子中有几个地雷
void Init(char show_map[MAX_ROW][MAX_COL],char mine_map[MAX_ROW][MAX_COL])
{
	//show_map初始化为*
	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_ROW; ++col)
		{
			show_map[row][col] = '0';
		}
	}
	//随机生成10个位置作为地雷
	int mine_count = MINE_COUNT;
	while (mine_count>0)
	{
		//生成一组随机坐标
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (mine_map[row][col] == '1')
		{
			continue;
		}
		mine_map[row][col] == '1';
		--mine_count;
	}
}
void PrintMap(char map[MAX_ROW][MAX_COL])
{
	/*for (int row = 0; row < MAX_ROW; ++row)
	{
		printf("%d",row );
	}
	for (int row = 0; row < MAX_ROW; ++row)
	{
		printf("___");
	}
	for (int col = 0; col < MAX_COL; ++col)
	{
		printf("%d", col);
	}
	for (int col = 0; col < MAX_ROW; ++col)
	{
		printf("|||");
	}*/
	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_ROW; ++col)
		{
			printf("%c",map[row][col]);
		}
		printf("\n");
	}
}
void UpdateShowMap(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL])
{
	//判定周围有几个雷
	int count = 0;
	int row = MAX_ROW;
	int col = MAX_COL;
	if (row - 1 >= 0 && col - 1 >= 0 && mine_map[row - 1][col - 1] == '1')
	{
		++count;
	}
	if (row - 1 >= 0 && mine_map[row - 1][col] == '1')
	{
		++count;
	}
	if (row - 1 >= 0 && col + 1 < MAX_COL && mine_map[row - 1][col + 1] == '1')
	{
		++count;
	}
	if (col - 1 >= 0 && mine_map[row][col - 1] == '1')
	{
		++count;
	}
	if (col + 1 < MAX_COL && mine_map[row][col + 1] == '1')
	{
		++count;
	}
	if (row + 1 < MAX_ROW && mine_map[row + 1][col] == '1')
	{
		++count;
	}
	if (row + 1 < MAX_ROW && col + 1 < MAX_COL && mine_map[row + 1][col + 1] == '1')
	{
		++count;
	}
	if (row + 1 < MAX_ROW && col - 1 >= 0 && mine_map[row + 1][col - 1] == '1')
	{
		++count;
	}
	show_map[row][col] = count + '0';
}
void Game()
{//1.创建两个二维数组
	char show_map[MAX_ROW][MAX_COL];
	char mine_map[MAX_ROW][MAX_COL];
	//2.对两个二维数组进行初始化
	Init(show_map, mine_map);
	int blank_count = 0;//未翻开数量
	PrintMap(mine_map);
	printf("\n\n");
	while (1)
	{
		system("cls");
		PrintMap(show_map);
		//4.让用户输入一组坐标，并进行校验
		printf("输入坐标：\n");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL)
		{
			printf("输入有误，重输\n");
			continue;
		}
		if (show_map[row][col] != '*')
		{
			printf("位置翻开，重输\n");
			continue;
		}
		//5.判定是否踩雷
		if (mine_map[row][col] == '1')
		{
			printf("游戏结束\n");
			break;
		}
		++blank_count;
		if (blank_count == MAX_ROW*MAX_COL - MINE_COUNT)
		{
			printf("扫雷成功\n");
			break;
}
	}
 //7.显示地雷数
	system("cls");
	PrintMap(mine_map);
}
int Menu()
{
	printf("================================================\n");
	printf("===================1.开始游戏===================\n");
	printf("===================0.结束游戏===================\n");
	printf("================================================\n");
	printf("请输入你的选择：");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}
int main()
{
	srand((unsigned int)time(0));
	while (1)
	{
		int choice = Menu();
		if (choice == 1)
		{
			Game();
		}
		else if (choice == 0)
		{
			printf("再见\n");
		}
		else
		{
			printf("输入有误\n");
		}
	}
	system("pause");
	return 0;
}
