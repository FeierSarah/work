#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
/*顺序查找*/
int _Search(double *a, double x, int length) /*被调用的函数search()*/
{
	assert(&a);
	for (int i = 0; i < length; i++)
	{
		if (x == a[i])//查找到所需的元素，跳出循环
		{
			return i;
			break;
		}
	}
	return -1;
}

/*二分查找*/
void ShellSort(double* a, int length)
{
	assert(a);
	int gap = length;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < length - gap; i++)
		{
			int end = i;
			double tmp = a[end + gap];
			while (end >= 0 && a[end] > tmp)
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}
int BinarySearch(double* a, double x, int length)
{
	assert(a);
	ShellSort(a, length);
	int left = 0, right = length - 1;
	int mid;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (x < a[mid])
		{
			right = mid - 1;
		}
		else if (x > a[mid])
		{
			left = mid + 1;
		} 
		else
		{
			return mid;
		}
	}
	return - 1;
}

/*二叉查找树*/
typedef struct BinaryTreeNode{
	double data;
	struct BinaryTreeNode* lchild; 
	struct BinaryTreeNode* rchild; 
}BSTnode, *PBSTnode;


PBSTnode BinaryTreeInsert(double data, PBSTnode *root)
{
	assert(root);
	if (*root == NULL)
	{
		*root = (PBSTnode)malloc(sizeof(BSTnode));
		(*root)->data = data;
		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
		return *root;
	}
	if (data<(*root)->data)
		(*root)->lchild = BinaryTreeInsert(data, &((*root)->lchild));
	else if (data>(*root)->data)
		(*root)->rchild = BinaryTreeInsert(data, &((*root)->rchild));
	return *root;
}

PBSTnode BinaryTreeCreate(double* a, int length, PBSTnode root)
{
	assert(&root && a);
	for (int i = 0; i < length; i++)
	{
		BinaryTreeInsert(a[i], &root);
	}
	return root;
}

PBSTnode BinaryTreeSearch(double* a, double x, int length, PBSTnode root)
{
	assert(&root && a);
	BinaryTreeCreate(a, length, root);
	while (root != NULL)
	{
		if (x > root->data)
			root = root->rchild;
		else if (x < root->data)
			root = root->lchild;
		else if (x == root->data)
			return root;
	}
	return -1;
}

void testTime()
{
	int num;
	int k = 20;
	double time1 = 0, time2 = 0, time3 = 0;
	scanf("%d", &num);
	while (k--)
	{
		double* b = (double*)malloc(num * sizeof(double));
		for (int i = 0; i < num; i++)
		{
			int random_num1 = rand();
			int random_num2 = rand() % 100;
			double random = random_num1 + 0.01 * random_num2;
			b[i] = random;
			/*printf("%.2f ", b[i]);*/
		}
		/*printf("\n");*/

		double* b1 = (double*)malloc(num * sizeof(double));
		double* b2 = (double*)malloc(num * sizeof(double));
		double* b3 = (double*)malloc(num * sizeof(double));


		memcpy(b1, b, sizeof(double)* num);
		memcpy(b2, b, sizeof(double)* num);
		memcpy(b3, b, sizeof(double)* num);

		clock_t start1, end1, start2, end2, start3, end3;
		start1 = clock();
		printf("%d", _Search(b1, 999.99, num));
		end1 = clock();
		time1 += ((double)end1 - (double)start1);
		
		start2 = clock();
		printf("%d", BinarySearch(b2, 999.99, num));
		end2 = clock();
		time2 += ((double)end2 - (double)start2);
		
		PBSTnode root = NULL;
		start3 = clock();
		printf("%d", BinaryTreeSearch(b3, 999.99, num, root));
		end3 = clock();
		time3 += ((double)end3 - (double)start3);
	}
	double ave1 = time1 * 50;
	double ave2 = time2 * 50;
	double ave3 = time3 * 50;
	printf("顺序查找运行时间：%.1lf us\n", ave1);
	printf("二分查找运行时间：%.1lf us\n", ave2);
	printf("二叉树查找运行时间：%.1lf us\n", ave3);

}

int main()
{
	testTime();
	return 0;
}