#include <iostream>
using namespace std;
#define MAX 20 
//���ݵ����㷨
void SCAN(int array[], int m)
{
	int now;  //��ǰ��ͷλ��
	int temp;  //ð�������ǣ����ݵ��ȴ洢���һλ������λ�ñ��
	int i, j;  
	int sum = 0;  //��Ѱ������ 
	float avg;  //ƽ��Ѱ������
	//�Դŵ������н��д�С��������
	for (i = 0; i < m; i++)
	{
		for (j = i + 1; j < m; j++) //�Դŵ������н��д�С��������       
		{
			if (array[i] > array[j])//���ŵ���֮��Ƚ�      
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	cout << "��������Ĵŵ������飺 ";
	for (i = 0; i < m; i++)     
	{
		cout << array[i] << " ";
	}
	cout << endl << "���뵱ǰ�Ĵŵ��ţ� ";
	cin >> now;
	cout << "�ŵ�������ŵ������ӵķ������ƶ�" << endl;
	cout << "SCAN���Ƚ��:  ";
	for (i = 0; i < m; i++)
	{      
		if (now <= array[i])//�������ڵ�ǰ˳��
		{    
			cout << array[i] << " ";
			sum = array[i] - now + sum;//������Ѱ������
			now = array[i];
		}     
		else//���������ڵ�ǰ˳��     
		{         
			temp = array[i];//�ݴ治�ڵ�ǰ˳������ݵ����һ��
			j = i;//��¼���һ�������ϵ�λ��
		}   
	}   
	for(i = j; i >= 0; i--) //�����һ�������ϵ�λ����ǰ����
	{      
		cout << array[i] << " ";
		sum = now - array[i] + sum;//������Ѱ������
		now = array[i];
	}  
	avg = (float)sum / m;;
	cout << endl << "�ƶ����ܵ����� " << sum << endl;
	cout << "ƽ��Ѱ�����ȣ� " << avg << endl;
}

void test()
{
	int cidao[MAX];//����ŵ�������
	int num;//����ŵ�����
	cout << "���������� ";
	cin >> num;
	cout << "�ŵ��������У� ";
	for (int i = 0; i < num; i++)
	{
		cin >> cidao[i];
	}
	SCAN(cidao, num);//���õ��ݵ����㷨
}

int main()
{
	test();
	return 0;
}