#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
/*��������*/
//ʱ�䣺O(N^2)
//�ռ䣺O(1)
//�ȶ��ԣ��ȶ�
void InsertSort(float* a, int n)
{
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
//ʱ��:O(n^1.3 - n^2)
//�ռ䣺O(1)
//�ȶ��ԣ����ȶ�
void ShellSort(float* a, int n)
{
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
//�ռ䣺O(1)
//�ȶ��ԣ��ȶ�
void SelectSort(float* a, int n)
{
	int begin = 0, end = n - 1;
	//ÿ��ѡһ�����ĺ���С�ģ��ŵ���Ӧ��λ��
	while (begin < end)
	{
		int i, max, min;
		max = min = begin;
		for (i = begin; i <= end; ++i)
		{
			if (a[i] < a[min])
				min = i;
			if (a[i] >= a[min])//if (a[i] > a[min]) �޸��������ȶ�
				max = i;
		}
		Swap(&a[begin], &a[min]);
		if (max == begin)
			max = min;
		Swap(&a[end], &a[max]);
		begin++;
		--end;
	}
}

/*������*/
//ʱ�䣺O(n * log(n))
//�ռ䣺O(1)
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
//ʱ�䣺O(n^2)
//�ռ䣺O(1)
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
//ʱ�䣺N * logN
//�ռ䣺logN �ռ���Ը��ã����ĵݹ������
//�ȶ��ԣ�
//����ȡ��
int getMid(float* a, int left, int right)
{
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

//�ڿӷ�
int PartSort2(float* a, int left, int right)
{
	int mid = getMid(a, left, right);
	Swap(&a[mid], &a[left]);

	float key = a[left];
	while (left < right)
	{
		while (left < right && a[right] >= key)
			--right;
		a[left] = a[right];
		while (left < right && a[right] <= key)
			++left;
		a[right] = a[left];
	}
	a[left] = key;
	return left;
}

//ǰ��ָ�뷨
int PartSort3(float* a, int left, int right)
{
	int mid = getMid(a, left, right);
	Swap(&a[mid], &a[left]);

	float key = a[left];
	int prev = left; //���һ��С��key��λ��
	int cur = left + 1;//��һ��С��key��λ��
	//�����һ��С��key��λ������һ��С��key��λ�ò�����
	//˵���м��д���key��ֵ�����н�������������ƶ���С����ǰ�ƶ�
	while (left <= right)
	{
		if (a[cur] < key && ++prev != cur)
			Swap(&a[prev], &a[cur]);
		++cur;
	}
	Swap(&a[left], &a[prev]);
	return left;
}

//�ݹ�
void QuickSort(float* a, int left, int right)
{
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

////�ǵݹ�
////����ջ ����ȳ�
//void QuickSort2(int* a, int left, int right)
//{
//	Stack st;
//	StackInit(&st);
//	if (left < right)
//	{
//		StackPush(&st, right);
//		StackPush(&st, left);
//	}
//	while (StackEmpty(&st) == 0)
//	{
//		int begin = StackTop(&st);
//		StackPop(&st);
//		int end = StackTop(&st);
//		StackPop(&st);
//		//���ֵ�ǰ����
//		int mid = PartSort(a, begin, end);
//		//��������������
//		if (begin < mid - 1)
//		{
//			StackPush(&st, mid - 1);
//			StackPush(&st, begin);
//		}
//		if (mid + 1 < end)
//		{
//			StackPush(&st, end);
//			StackPush(&st, mid + 1);
//		}
//	}
//}

/*�ϲ�����*/
//ʱ�䣺O(N * logN)
//�ռ䣺T(N)
//�ȶ��ԣ��ȶ�
void Merge(float* a, int left, int mid, int right)
{
	float* b = (float*)malloc((right - left + 1) * sizeof(float));
	for (int i = left; i < right - left + 1; i++)
	{
		b[i] = a[i];
	}
	int i = left, j = mid + 1, k = 0;
	while (i <= mid && j <= right)
	{
		if (a[i] <= a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	while (i <= mid)
		b[k++] = a[i++];
	while (j <= right)
		b[k++] = a[j++];
	for (int i = left; i < right - left + 1; i++)
	{
		a[i] = b[i];
	}
}

void MergeSort(float* a, int left, int right)
{
	if (left >= right)
		return;
	else
	{
		int i = (right - left) / 2 + left;
		MergeSort(a, left, i);
		MergeSort(a, i + 1, right);
		Merge(a, left, i, right);
	}
}

void ArrayPrint(float* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%0.2f ", a[i]);
	}
	printf("\n");
}

void testSort()
{
	float a[] = { 10.123, 2.123, 3.123, 8.123, 9.123, 7.123, 6.123, 1.123, 5.123, 4.123 };
	printf("ԭ����Ϊ��  ");
	ArrayPrint(a, sizeof(a) / sizeof(float));

	InsertSort(a, sizeof(a) / sizeof(float));
	printf("���������Ϊ��  ");
	ArrayPrint(a, sizeof(a) / sizeof(float));

	ShellSort(a, sizeof(a) / sizeof(float));
	printf("ϣ�������Ϊ��  ");
	ArrayPrint(a, sizeof(a) / sizeof(float));

	SelectSort(a, sizeof(a) / sizeof(float));
	printf("ѡ�������Ϊ��  ");
	ArrayPrint(a, sizeof(a) / sizeof(float));

	HeapSort(a, sizeof(a) / sizeof(float));
	printf("�������Ϊ��    ");
	ArrayPrint(a, sizeof(a) / sizeof(float));

	BubbleSort(a, sizeof(a) / sizeof(float));
	printf("ð�������Ϊ��  ");
	ArrayPrint(a, sizeof(a) / sizeof(float));

	QuickSort(a, 0, sizeof(a) / sizeof(float)-1);
	printf("���������Ϊ��  ");
	ArrayPrint(a, sizeof(a) / sizeof(float));

	MergeSort(a, 0, sizeof(a) / sizeof(float)-1);
	printf("�ϲ������Ϊ��  ");
	ArrayPrint(a, sizeof(a) / sizeof(float));
}

void testTime()
{
	int num;
	scanf("%d", &num);
	float* a2 = (float*)malloc(num * sizeof(float));
	for (int i = 0; i < num; i++)
	{
		int random_num1 = rand();
		int random_num2 = rand() % 100;
		float random = random_num1 + 0.01 * random_num2;
		a2[i] = random;
		printf("%.2f ", a2[i]);
	}
	printf("\n");

	clock_t start1 = clock();
	InsertSort(a2, sizeof(a2) / sizeof(float));
	clock_t end1 = clock();
	double time1 = ((double)end1 - (double)start1) / CLOCKS_PER_SEC;
	printf("������������ʱ�䣺%.3lf s\n", time1);

	clock_t start2 = clock();
	ShellSort(a2, sizeof(a2) / sizeof(float));
	clock_t end2 = clock();
	double time2 = ((double)end2 - (double)start2) / CLOCKS_PER_SEC;
	printf("ϣ����������ʱ�䣺%.3lf s\n", time2);

	clock_t start3 = clock();
	SelectSort(a2, sizeof(a2) / sizeof(float));
	clock_t end3 = clock();
	double time3 = ((double)end3 - (double)start3) / CLOCKS_PER_SEC;
	printf("ѡ����������ʱ�䣺%.3lf s\n", time3);

	clock_t start4 = clock();
	HeapSort(a2, sizeof(a2) / sizeof(float));
	clock_t end4 = clock();
	double time4 = ((double)end4 - (double)start4) / CLOCKS_PER_SEC;
	printf("����������ʱ�䣺%.3lf s\n", time4);

	clock_t start5 = clock();
	BubbleSort(a2, sizeof(a2) / sizeof(float));
	clock_t end5 = clock();
	double time5 = ((double)end5 - (double)start5) / CLOCKS_PER_SEC;
	printf("ð����������ʱ�䣺%.3lf s\n", time5);

	clock_t start6 = clock();
	QuickSort(a2, 0, sizeof(a2) / sizeof(float)-1);
	clock_t end6 = clock();
	double time6 = ((double)end6 - (double)start6) / CLOCKS_PER_SEC;
	printf("������������ʱ�䣺%.3lf s\n", time6);

	clock_t start7 = clock();
	MergeSort(a2, 0, sizeof(a2) / sizeof(float)-1);
	clock_t end7 = clock();
	double time7 = ((double)end7 - (double)start7) / CLOCKS_PER_SEC;
	printf("�ϲ���������ʱ�䣺%.3lf s\n", time7);
}

int main()
{
	testSort();
	testTime();
	return 0;
}