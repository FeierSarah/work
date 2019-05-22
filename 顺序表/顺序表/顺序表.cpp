#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100//初始长度 
#define LISTINCREMENT 10//变量长度 
typedef struct
{
	int *data;
	int length;
	int listsize;
}SqList;                    /*顺序存储的结构体类型*/
SqList a;

/*函数声明*/
void initlist(SqList *L);
void showlist(SqList L);
void insertlist(SqList *L, int i, int e);
int deletelist(SqList *L, int i);
void locatelist(SqList L, int e);
void reverse(SqList *L, int length);

/*主函数*/
int main()
{
	int choice, i, e, length;
	choice = -1;
	do
	{
		printf("\n 5.逆序输出线性表");
		printf("\n 4.删除线性表");
		printf("\n 3.查找线性表");
		printf("\n 2.插入线性表");
		printf("\n 1.建立线性表");
		printf("\n 0.结束程序运行");
		printf("\n====================================");
		printf("\n    请输入您的选择(5,4,3,2,1,0)");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:

			exit(0);
		case 1:
			initlist(&a);
			showlist(a);
			break;
		case 2:      printf("输入位置和元素");
			scanf("%d", &i);
			scanf("%d", &e);
			insertlist(&a, i, e);
			showlist(a);

			break;
		case 3:      printf("输入查找数值");
			scanf("%d", &i);
			locatelist(a, i);

			break;
		case 4:      printf("输入位置");
			scanf("%d", &i);
			deletelist(&a, i - 1);
			showlist(a);
			break;

		case 5:      reverse(&a, length);
			showlist(a);
			break;
		default:
			printf("\n无效选项!");
			break;
		}
	} while (choice != 0);
}


/*建立线性表*/
void initlist(SqList *L)
{
	int i;
	L->data = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if (!L->data) exit(0);
	printf("\n请输入线性表的长度:");
	scanf("%d", &L->length);
	for (i = 0; i <= L->length - 1; i++)
	{
		printf("数据%d/%d=", i + 1, L->length);
		scanf("%d", &(L->data[i]));
	}
}

/*输出线性表*/
void showlist(SqList L)
{
	int i, j = 0;
	for (i = 0; i <= L.length - 1; i++)
	{
		printf("%10d", L.data[i]); j++;
		if (j % 5 == 0)printf("\n");
	}

}
void insertlist(SqList *L, int i, int e)
{
	if (i<1 || i>L->length) exit(0);
	int j;
	for (j = L->length; j>i; j--)
	{
		L->data[j] = L->data[j - 1];
		L->data[i] = e;
		L->length = L->length + 1;
	}
}
int deletelist(SqList *L, int i)
{
	if (i<1 || i>L->length) exit(0);
	for (; i<L->length; i++)
	{
		L->data[i] = L->data[i + 1];

	}L->length - 1;
}
void locatelist(SqList L, int e)
{
	int i = 0;
	for (i = 0; i<L.length; i++)
	{
		if (L.data[i] == e)
			printf("%d", i + 1);
	}
}
void reverse(SqList *L, int length)
{
	int tmp, i;
	int a[100];
	for (int i = 0; i < length / 2; ++i)
	{
		tmp = a[i];
		a[i] = a[length - 1];
		a[length - 1] = tmp;
	}
}