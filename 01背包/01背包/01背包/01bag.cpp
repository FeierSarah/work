#include <iostream>
#include <cstring>
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
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= num; j++) {
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

void bag3(int n, int num)
{

}

void test()
{
	int n;
	int count = 0, num = 0;
	cout << "������Ʒ������";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		weight[i] = rand() % 1000;
		value[i] = rand() % 1000;
	}
	cout << "��Ʒ������" << endl;
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
	cout << "��Ʒ��ֵ��" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << value[i];
		if (i % 10 == 0)
		{
			cout << endl;
		}
	}
	cout << "���ɱ���������" << num << endl;

	clock_t start1, end1, start2, end2, start3, end3;
	start1 = clock();
	bag1(n, num);
	state1(n, num);
	end1 = clock();
	double time1 = ((double)end1 - (double)start1) / CLOCKS_PER_SEC;
	printf("��̬�滮������ʱ�䣺%.3lf s\n", time1);

	start2 = clock();
	bag2(n, num);
	end2 = clock();
	double time2 = ((double)end2 - (double)start2) / CLOCKS_PER_SEC;
	printf("���ݷ�����ʱ�䣺%.3lf s\n", time2);

	start3 = clock();
	bag3(n, num);
	end3 = clock();
	double time3 = ((double)end3 - (double)start3) / CLOCKS_PER_SEC;
	printf("��֧���޷�����ʱ�䣺%.3lf s\n", time3);

	cout << "״̬Ϊ��" << endl;
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