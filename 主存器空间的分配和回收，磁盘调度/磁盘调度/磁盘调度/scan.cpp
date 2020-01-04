#include <iostream>
using namespace std;
#define MAX 20 
//电梯调度算法
void SCAN(int array[], int m)
{
	int now;  //当前磁头位置
	int temp;  //冒泡排序标记，电梯调度存储最后一位不符合位置标记
	int i, j;  
	int sum = 0;  //总寻道长度 
	float avg;  //平均寻道长度
	//对磁道号序列进行从小到大排列
	for (i = 0; i < m; i++)
	{
		for (j = i + 1; j < m; j++) //对磁道号序列进行从小到大排列       
		{
			if (array[i] > array[j])//两磁道号之间比较      
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	cout << "输出排序后的磁道号数组： ";
	for (i = 0; i < m; i++)     
	{
		cout << array[i] << " ";
	}
	cout << endl << "输入当前的磁道号： ";
	cin >> now;
	cout << "磁道方向：向磁道号增加的方向上移动" << endl;
	cout << "SCAN调度结果:  ";
	for (i = 0; i < m; i++)
	{      
		if (now <= array[i])//符合属于当前顺序
		{    
			cout << array[i] << " ";
			sum = array[i] - now + sum;//计算总寻道长度
			now = array[i];
		}     
		else//不符合属于当前顺序     
		{         
			temp = array[i];//暂存不在当前顺序的数据的最后一个
			j = i;//记录最后一个不符合的位置
		}   
	}   
	for(i = j; i >= 0; i--) //从最后一个不符合的位置往前查找
	{      
		cout << array[i] << " ";
		sum = now - array[i] + sum;//计算总寻道长度
		now = array[i];
	}  
	avg = (float)sum / m;;
	cout << endl << "移动的总道数： " << sum << endl;
	cout << "平均寻道长度： " << avg << endl;
}

void test()
{
	int cidao[MAX];//定义磁道号数组
	int num;//定义磁道数量
	cout << "请求数量： ";
	cin >> num;
	cout << "磁道请求序列： ";
	for (int i = 0; i < num; i++)
	{
		cin >> cidao[i];
	}
	SCAN(cidao, num);//调用电梯调度算法
}

int main()
{
	test();
	return 0;
}