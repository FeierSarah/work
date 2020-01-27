#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
/*��������*/
//ʱ�䣺O(N^2)
//�ռ䣺T(1)
//�ȶ��ԣ��ȶ�
void InsertSort(float* a, int n)
{
	assert(a);
	int i;
	for (i = 0; i < n - 1; ++i)
	{
		int end = i;
		float tmp = a[end + 1];
		while (end >= 0 && a[end] > tmp)
		{
			a[end + 1] = a[end];
			end--;
		}
		a[end + 1] = tmp;
	}
}

/*ϣ������*/
//ʱ��:O(N^1.3 - N^2)
//�ռ䣺T(1)
//�ȶ��ԣ����ȶ�
void ShellSort(float* a, int n)
{
	assert(a);
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			float tmp = a[end + gap];
			while (end >= 0 && a[end] > tmp)
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}

void Swap(float* a, float* b)
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*ѡ������*/
//ʱ�䣺O(N^2)
//�ռ䣺T(1)
//�ȶ��ԣ��ȶ�
void SelectSort(float* a, int n)
{
	assert(a);
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		int i, min;
		min = begin;
		for (i = begin; i <= end; ++i)
		{
			if (a[i] < a[min])
				min = i;
		}
		Swap(&a[begin], &a[min]);
		begin++;
	}
}

/*������*/
//ʱ�䣺O(N * logN)
//�ռ䣺T(1)
//�ȶ��ԣ�
void ShiftDown(float* a, int n, int root)
{
	assert(a);
	int parent = root;
	int child = 2 * parent + 1;
	//��ǰ�ڵ��Ƿ��к���
	while (child < n)
	{
		//�Ƿ����Һ��ӣ�������бȽ�
		if (child + 1 < n && a[child + 1] > a[child])
			++child;
		//�����Ƿ���ڸ��ף�������н���
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			//������һ�ε�����λ��
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			//�Ը���Ϊ���������Ѿ���һ����ѣ���������
			break;
		}
	}
}

void HeapSort(float* a, int n)
{
	assert(a);
	int i;
	for (i = (n - 2) / 2; i >= 0; i--)
	{
		ShiftDown(a, n, i);
	}
	while (n > 1)
	{
		Swap(&a[0], &a[n - 1]);
		ShiftDown(a, n - 1, 0);
		n--;
	}
}

/*ð������*/
//ʱ�䣺O(N^2)
//�ռ䣺T(1)
//�ȶ��ԣ��ȶ�
void BubbleSort(float* a, int n)
{
	assert(a);
	for (int i = n; i > 0; i--)
	{
		int flag = 0;
		for (int j = 0; j < i - 1; j++)
		{
			//���һ�ε�ð�ݹ����Ƿ���Ԫ�ؽ���
			flag = 1;
			if (a[j] > a[j + 1])
				Swap(&a[j], &a[j + 1]);
		}
		if (flag == 0)//���û�з���Ԫ�ؽ�������ǰ����
			break;
	}
}

/*��������*/
//ʱ�䣺O(N * logN)
//�ռ䣺T(logN) �ռ���Ը��ã����ĵݹ������
//�ȶ��ԣ����ȶ�
//����ȡ��
int getMid(float* a, int left, int right)
{
	assert(a);
	int mid = left + (right - left) / 2;
	while (left <right)
	{
		if (a[mid] > a[left])
		{
			if (a[mid] < a[right])
				return mid;
			else
			{
				if (a[left] > a[right])
					return left;
				else
					return right;
			}
		}
		else
		{
			if (a[left] < a[right])
				return left;
			else
			{
				if (a[mid] > a[right])
					return mid;
				else
					return right;
			}
		}
	}
}

int PartSort(float* a, int left, int right)
{
	assert(a);
	int mid = getMid(a, left, right);
	Swap(&a[mid], &a[left]);

	float key = a[left];
	int start = left;
	while (left < right)
	{
		while (left < right && a[right] >= key)
			--right;
		while (left < right && a[right] <= key)
			++left;
		Swap(&a[left], &a[right]);
	}
	Swap(&a[start], &a[left]);
	return left;
}

//�ݹ�д�����ǵݹ�д��Ҫ��ջ
void QuickSort(float* a, int left, int right)
{
	assert(a);
	if (left >= right)
		return;
	else if (right - left + 1 < 5)
	{
		InsertSort(a + left, right - left + 1);
	}
	else
	{
		int mid = PartSort(a, left, right);
		QuickSort(a, left, mid - 1);
		QuickSort(a, mid + 1, right);
	}
}

/*�ϲ�����*/
//ʱ�䣺O(N * logN)
//�ռ䣺T(N)
//�ȶ��ԣ��ȶ�
void _MergeSort(float* a, int left, int right, float* tmp)
{
	assert(a);
	//����ֻʣһ��Ԫ�أ�����ֽ�͹鲢
	if (left >= right)
		return;
	//�ֽ�
	int mid = (right - left) / 2 + left;
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);
	//�ϲ�
	int begin1 = left, end1 = mid, begin2 = mid + 1, end2 = right;
	int tmpindex = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] <= a[begin2])
		{
			tmp[tmpindex++] = a[begin1++];
		}
		else
		{
			tmp[tmpindex++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[tmpindex++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[tmpindex++] = a[begin2++];
	}
}

void MergeSort(float* a, int n)
{
	assert(a);
	float *tmp = (float*)malloc(n * sizeof(int));
	_MergeSort(a, 0, n - 1, tmp);
	free(tmp);
}

void ArrayPrint(float* a, int n)
{
	assert(a);
	for (int i = 0; i < n; i++)
	{
		printf("%0.2f ", a[i]);
	}
	printf("\n");
}

void testTime()
{
	int i = 20;
	double time1 = 0, time2 = 0, time3 = 0, time4 = 0, time5 = 0, time6 = 0, time7 = 0;
	int num;
	scanf("%d", &num);
	while (i--)
	{
		float* b = (float*)malloc(num * sizeof(float));
		for (int i = 0; i < num; i++)
		{
			int random_num1 = rand();
			int random_num2 = rand() % 100;
			float random = random_num1 + 0.01 * random_num2;
			b[i] = random;
			//printf("%.2f ", b[i]);
		}

		float* b1 = (float*)malloc(num * sizeof(float));
		float* b2 = (float*)malloc(num * sizeof(float));
		float* b3 = (float*)malloc(num * sizeof(float));
		float* b4 = (float*)malloc(num * sizeof(float));
		float* b5 = (float*)malloc(num * sizeof(float));
		float* b6 = (float*)malloc(num * sizeof(float));
		float* b7 = (float*)malloc(num * sizeof(float));

		memcpy(b1, b, sizeof(float)* num);
		memcpy(b2, b, sizeof(float)* num);
		memcpy(b3, b, sizeof(float)* num);
		memcpy(b4, b, sizeof(float)* num);
		memcpy(b5, b, sizeof(float)* num);
		memcpy(b6, b, sizeof(float)* num);
		memcpy(b7, b, sizeof(float)* num);

		clock_t start1, end1, start2, end2, start3, end3, start4, end4, start5, end5, start6, end6, start7, end7;
		start1 = clock();
		InsertSort(b1, num);
		end1 = clock();
		time1 += (((double)end1 - (double)start1) / CLOCKS_PER_SEC);

		start2 = clock();
		ShellSort(b2, num);
		end2 = clock();
		time2 += (((double)end2 - (double)start2) / CLOCKS_PER_SEC);

		start3 = clock();
		SelectSort(b3, num);
		end3 = clock();
		time3 += (((double)end3 - (double)start3) / CLOCKS_PER_SEC);

		start4 = clock();
		HeapSort(b4, num);
		end4 = clock();
		time4 += (((double)end4 - (double)start4) / CLOCKS_PER_SEC);

		start5 = clock();
		BubbleSort(b5, num);
		end5 = clock();
		time5 += (((double)end5 - (double)start5) / CLOCKS_PER_SEC);

		start6 = clock();
		QuickSort(b6, 0, num);
		end6 = clock();
		time6 += (((double)end6 - (double)start6) / CLOCKS_PER_SEC);

		start7 = clock();
		MergeSort(b7, num);
		end7 = clock();
		time7 += (((double)end7 - (double)start7) / CLOCKS_PER_SEC);
	}
	double ave1 = time1 * 50000;
	double ave2 = time2 * 50000;
	double ave3 = time3 * 50000;
	double ave4 = time4 * 50000;
	double ave5 = time5 * 50000;
	double ave6 = time6 * 50000;
	double ave7 = time7 * 50000;
	printf("������������ʱ�䣺%.1lf us\n", ave1);
	printf("ϣ����������ʱ�䣺%.1lf us\n", ave2);
	printf("ѡ����������ʱ�䣺%.1lf us\n", ave3);
	printf("����������ʱ�䣺%.1lf us\n", ave4);
	printf("ð����������ʱ�䣺%.1lf us\n", ave5);
	printf("������������ʱ�䣺%.1lf us\n", ave6);
	printf("�ϲ���������ʱ�䣺%.1lf us\n", ave7);
}

int main()
{
	testTime();
	return 0;
}