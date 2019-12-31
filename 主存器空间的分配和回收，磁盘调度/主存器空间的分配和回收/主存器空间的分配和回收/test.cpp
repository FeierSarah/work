#include <iostream>
using namespace std;
#define COUNT 512

//定义作业结构体代表作业状态
typedef struct Task
{
	char name;//名称
	int start;//起始位置
	int end;//大小
	int flag;//是否分配的标志
}Task;

//定义结构体数组存储各项作业状态，代表作业表
Task OS[COUNT];
int counts;//被分成的块数统计

char c;//作业名
int num;//资源申请量

//初始化
void init()
{
	counts = 1;
	OS[0].name = 'P';//未分配命名为P
	OS[0].start = 0;//初始位置0
	OS[0].end = COUNT;
	OS[0].flag = 1;//分配标志未分配 = 1
}

//插入数组数据
void insert(int m, int st, int en)
{
	int i;
	counts++;//数组长度加一
	for (i = counts; i > m ; i--)//从插入位由后往前后移数据
	{
		OS[i] = OS[i - 1];
	}
	OS[m].start = st;//插入数据
	OS[m].end = en;
}

//删除数组数据
void move(int m)
{
	int i;
	for (i = m; i < counts - 1; i++)//从删除位由前往后前移数据
	{
		OS[i] = OS[i + 1];
	}
	counts--;//数组长度减一
}

//合并没有分配的相邻块
void remove(int m, int st, int en)
{
	if (!OS[m - 1].flag && !OS[m + 1].flag)
		//如果m位置前后标志都已分配则正常处理，不分配
	{
		OS[m].name = 'P';
		OS[m].flag = 1;
	}
	if (OS[m - 1].flag)
		//如果m位置前标志未分配，后标志已分配则与前一个合并
	{
		OS[m - 1].end = OS[m - 1].end + en;
		move(m);
	}
	if (OS[m + 1].flag)
		//如果m位置后标志未分配，前标志已分配则与后一个合并
	{
		OS[m].end = OS[m].end + OS[m + 1].end;
		OS[m].name = 'P';
		OS[m].flag = 1;
		move(m + 1);
	}
}

//打印输出
void show()
{
	int i;
	cout << "(名称  标识  起址  长度  状态)" << endl;
	for (i = 0; i < counts; i++)
	{
		if (OS[i].flag)//未分配
			cout << "P    ";
		else//已分配
			cout << OS[i].name << "    ";
		cout << i << "    " << OS[i].start << "    " << OS[i].end << "    ";
		//依次输出块的编号，起始位置，长度
		if (OS[i].flag)
			cout << "未分配" << endl;
		else
			cout << "已分配" << endl;
	}
}

//录入数据
void put()
{
	cout << "输入申请或者释放的进程名称及资源数：" << endl;
	cin >> c;
	cin >> num;
}

//申请资源
int apply()
{
	int i = 0;
	int applyflag = 0;//标记
	while (!applyflag && i < counts)//遍历数组查找连续的可分配资源是否存在
	{
		if (OS[i].end >= num && OS[i].flag)//通过比较块大小和是否已分配来找资源空间
		{
			if (OS[i].end == num)//大小相等则直接修改信息
			{
				OS[i].name = c;
				OS[i].flag = 0;
			}
			else//若偏大则修改信息同时更新原先块为已分配和未分配两部分
			{
				insert(i + 1, OS[i].start + num, OS[i].end - num);
				OS[i + 1].flag = 1;
				OS[i + 1].name = 'P';
				OS[i].start = OS[i].start;
				OS[i].name = c;
				OS[i].end = num;
				OS[i].flag = 0;
			}
			applyflag = 1;//申请成功更改标记
		}
		i++;
	}
	if (applyflag)
	{
		cout << "申请成功" << endl;
		return 1;
	}
	else
	{
		cout << "没有足够大的空闲空间" << endl;
		return 0;
	}
}

//释放资源
int free()
{
	int i = 0;
	int freeflag = 0;//标记
	while (!freeflag && i < counts)//遍历数组查找所对应作业是否存在
	{
		if (OS[i].name == c)//找到作业
		{
			if (OS[i].end == num)//释放大小相等，合并未分配区
			{
				remove(i, OS[i].start, OS[i].end);
			}
			else
			{
				if (OS[i].end >num)//释放大小不足，将已分配区拆分为未分配和已分配两个区
				{
					insert(i + 1, OS[i].start + num, OS[i].end - num);
					OS[i + 1].name = 'P';
					OS[i + 1].flag = 0;
					OS[i].end = num;
					OS[i].flag = 1;
					if (OS[i - 1].flag)//合并未分配区
					{
						remove(i, OS[i].start, OS[i].end);
					}
				}
				else
				{
					cout << "正使用的数量小于释放的数量" << endl;
					return 0;
				}
			}
			freeflag = 1;//修改标记
		}
		i++;
	}
	if (freeflag)
	{
		cout << "释放成功" << endl;
		return 1;
	}
	else
	{
		cout << "未找到匹配的进程名称" << endl;
		return 0;
	}
}

//菜单函数
void menu()
{
	int code;	
	while (1)
	{
		cout << "输入选择" << endl << 
			"1.初始化" << endl <<
			"2.输出" << endl <<
			"3.申请" << endl <<
			"4.释放" << endl <<
			"0.退出" << endl;
		cin >> code;
		//初始化
		if (code == 1)
		{
			init();
		}
		//显示输出
		else if (code == 2)
		{
			show();
		}
		//申请
		else if (code == 3)
		{
			put();
			apply();
			show();
		}
		//释放
		else if (code == 4)
		{
			put();
			free();
			show();
		}
		//退出操作
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
	menu();
	return 0;
}