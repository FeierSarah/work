#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
/*插入排序*/
//时间：O(N^2)
//空间：T(1)
//稳定性：稳定
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

/*希尔排序*/
//时间:O(N^1.3 - N^2)
//空间：T(1)
//稳定性：不稳定
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

/*选择排序*/
//时间：O(N^2)
//空间：T(1)
//稳定性：稳定
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

/*堆排序*/
//时间：O(N * logN)
//空间：T(1)
//稳定性：
void ShiftDown(float* a, int n, int root)
{
	assert(a);
	int parent = root;
	int child = 2 * parent + 1;
	//当前节点是否有孩子
	while (child < n)
	{
		//是否有右孩子，有则进行比较
		if (child + 1 < n && a[child + 1] > a[child])
			++child;
		//孩子是否大于父亲，大则进行交换
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			//更新下一次调整的位置
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			//以父亲为根的子树已经是一个大堆，结束调整
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

/*冒泡排序*/
//时间：O(N^2)
//空间：T(1)
//稳定性：稳定
void BubbleSort(float* a, int n)
{
	assert(a);
	for (int i = n; i > 0; i--)
	{
		int flag = 0;
		for (int j = 0; j < i - 1; j++)
		{
			//标记一次的冒泡过程是否发生元素交换
			flag = 1;
			if (a[j] > a[j + 1])
				Swap(&a[j], &a[j + 1]);
		}
		if (flag == 0)//如果没有发生元素交换，提前结束
			break;
	}
}

/*快速排序*/
//时间：O(N * logN)
//空间：T(logN) 空间可以复用，最大的递归调用链
//稳定性：不稳定
//三数取中
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

//递归写法，非递归写法要用栈
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

/*合并排序*/
//时间：O(N * logN)
//空间：T(N)
//稳定性：稳定
void _MergeSort(float* a, int left, int right, float* tmp)
{
	assert(a);
	//区间只剩一个元素，无需分解和归并
	if (left >= right)
		return;
	//分解
	int mid = (right - left) / 2 + left;
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);
	//合并
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
	printf("插入排序运行时间：%.1lf us\n", ave1);
	printf("希尔排序运行时间：%.1lf us\n", ave2);
	printf("选择排序运行时间：%.1lf us\n", ave3);
	printf("堆排序运行时间：%.1lf us\n", ave4);
	printf("冒泡排序运行时间：%.1lf us\n", ave5);
	printf("快速排序运行时间：%.1lf us\n", ave6);
	printf("合并排序运行时间：%.1lf us\n", ave7);
}

int main()
{
	testTime();
	return 0;
}