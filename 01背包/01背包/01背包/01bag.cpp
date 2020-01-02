#include <iostream>
#include <cstring>
#include <queue>
#include <assert.h>
#include <ctime>
using namespace std;
#define N 110

int weight[N], value[N],
int state[N] = { 0 };
int dp[N][1000000] = { 0 };

int max(int m, int n)
{
	if (m <= n)
		return n;
	else
		return m;
}

void bag1(int n, int num)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= num; j++) 
		{
			if (j < weight[i])
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
			}
		}
	}
}

void state1(int n, int num)
{
	if (n >= 0) 
	{
		if (dp[n][num] == dp[n - 1][num]) 
		{
			state[n] = 0;
			state1(n - 1, num);
		}
		else if (num - weight[n] >= 0 && dp[n][num] == dp[n - 1][num - weight[n]] + value[n]) 
		{
			state[n] = 1;
			state1(n - 1, num - weight[n]);
		}
	}
}

void bag2(int n, int num)
{

}

typedef struct treenode
{
	int weight;
	int value;
	int level;
	int flag;
}treenode;
queue<struct treenode> que;
int enQueue(int w, int v, int level, int flag, int n, int* bestvalue)
{
	treenode node;
	node.weight = w;
	node.value = v;
	node.level = level;
	node.flag = flag;
	if (level == n)
	{
		if (node.value > *bestvalue)
		{
			*bestvalue = node.value;
		}
		return 0;
	}
	else
	{
		que.push(node);
	}
}
//w为重量数组，v为价值数组，n为物品个数，c为背包容量，bestValue为全局最大价值
int bbfifoknap(int n, int num, int* bestValue)
{
	//初始化结点
	int i = 1;
	treenode tag, livenode;
	livenode.weight = 0;
	livenode.value = 0;
	livenode.level = 1;
	livenode.flag = 0;//初始为0
	tag.weight = -1;
	tag.value = 0;
	tag.level = 0;
	tag.flag = 0;//初始为0
	que.push(tag);
	while (1)
	{
		if (livenode.weight + weight[i - 1] <= num)
		{
			enQueue(livenode.weight + weight[i - 1], livenode.value + value[i - 1], i, 1, n, bestValue);
		}
		enQueue(livenode.weight, livenode.value, i, 0, n, bestValue);
		livenode = que.front();
		que.pop();
		if (livenode.weight == -1)
		{
			if (que.empty() == 1)
			{
				break;
			}
			livenode = que.front();
			que.pop();
			que.push(tag);
			i++;
		}
	}
	return 0;
}

void test()
{
	int n;
	int count = 0, num = 0;
	cout << "输入物品数量：";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		weight[i] = rand() % 1000;
		value[i] = rand() % 1000;
	}
	cout << "物品重量：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << weight[i];
		count += weight[i];
		if (i % 10 == 0)
		{
			cout << endl;
		}
	}
	num = count * 6 / 10;
	cout << "物品价值：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << value[i];
		if (i % 10 == 0)
		{
			cout << endl;
		}
	}
	cout << "生成背包容量：" << num << endl;

	clock_t start1, end1, start2, end2, start3, end3;
	start1 = clock();
	bag1(n, num);
	state1(n, num);
	end1 = clock();
	double time1 = ((double)end1 - (double)start1) / CLOCKS_PER_SEC;
	printf("动态规划法运行时间：%.3lf s\n", time1);

	start2 = clock();
	bag2(n, num);
	end2 = clock();
	double time2 = ((double)end2 - (double)start2) / CLOCKS_PER_SEC;
	printf("回溯法运行时间：%.3lf s\n", time2);

	start3 = clock();
	bag3(n, num);
	end3 = clock();
	double time3 = ((double)end3 - (double)start3) / CLOCKS_PER_SEC;
	printf("分支界限法运行时间：%.3lf s\n", time3);

	cout << "状态为：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << state[i];
		if (i % 10 == 0)
		{
			cout << endl;
		}
	}
}

int main()
{
	test();
	return 0;
}