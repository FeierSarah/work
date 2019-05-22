#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100//��ʼ���� 
#define LISTINCREMENT 10//�������� 
typedef struct
{
	int *data;
	int length;
	int listsize;
}SqList;                    /*˳��洢�Ľṹ������*/
SqList a;

/*��������*/
void initlist(SqList *L);
void showlist(SqList L);
void insertlist(SqList *L, int i, int e);
int deletelist(SqList *L, int i);
void locatelist(SqList L, int e);
void reverse(SqList *L, int length);

/*������*/
int main()
{
	int choice, i, e, length;
	choice = -1;
	do
	{
		printf("\n 5.����������Ա�");
		printf("\n 4.ɾ�����Ա�");
		printf("\n 3.�������Ա�");
		printf("\n 2.�������Ա�");
		printf("\n 1.�������Ա�");
		printf("\n 0.������������");
		printf("\n====================================");
		printf("\n    ����������ѡ��(5,4,3,2,1,0)");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:

			exit(0);
		case 1:
			initlist(&a);
			showlist(a);
			break;
		case 2:      printf("����λ�ú�Ԫ��");
			scanf("%d", &i);
			scanf("%d", &e);
			insertlist(&a, i, e);
			showlist(a);

			break;
		case 3:      printf("���������ֵ");
			scanf("%d", &i);
			locatelist(a, i);

			break;
		case 4:      printf("����λ��");
			scanf("%d", &i);
			deletelist(&a, i - 1);
			showlist(a);
			break;

		case 5:      reverse(&a, length);
			showlist(a);
			break;
		default:
			printf("\n��Чѡ��!");
			break;
		}
	} while (choice != 0);
}


/*�������Ա�*/
void initlist(SqList *L)
{
	int i;
	L->data = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if (!L->data) exit(0);
	printf("\n���������Ա�ĳ���:");
	scanf("%d", &L->length);
	for (i = 0; i <= L->length - 1; i++)
	{
		printf("����%d/%d=", i + 1, L->length);
		scanf("%d", &(L->data[i]));
	}
}

/*������Ա�*/
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