#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<malloc.h>
#define NAME_SIZE 30
#define SEX_SIZE 5
#define TEL_SIZE 12
#define ADDR_SIZE 20
#define MAX 100
enum menu
{
	EXIT,
	ADD,
	DEL,
	MODITY,
	SEARCH,
	SORT,
	EMPTY,
	SHOW
};
typedef struct student
{
	char name[NAME_SIZE];
	char sex[SEX_SIZE];
	short int age;
	char addr[ADDR_SIZE];
	char tel[TEL_SIZE];
}Student;
typedef struct MailList
{
	//Student data[MAX];
	Student *data;
	int capacity;
	int size;
}MailList;
void menu()
{
	printf("***********************************************\n");
	printf("******1.add             2.del            ******\n");
	printf("******3.modity          4.search         ******\n");
	printf("******5.sort            6.empty          ******\n");
	printf("******7.show            0.exit           ******\n");
	printf("***********************************************\n");
}
void InitMailList(MailList *ml)
{
	assert(ml != NULL);
	ml->capacity = MAX;
	ml->size = 0;
	//ml.data(����������ֱ�Ӹ�ֵ��
	ml->data = (Student*)malloc(sizeof(Student)*ml->capacity);
	memset(ml->data, 0, MAX*sizeof(Student));
}
int IncCapacity(MailList *ml)
{
	Student*temp = NULL;
	assert(ml != NULL);
	ml->capacity = ml->capacity + MAX;
	temp = (Student*)realloc(ml->data, sizeof(Student)*ml->capacity);
	if (temp != NULL)
	{
		ml->data = temp;
		return 1;
	}
	else
		return 0;
}
void Add(MailList *ml)
{
	assert(ml != NULL);
	if (ml->size >= ml->capacity&&IncCapacity(ml))
	{
		printf("����");
		return;
	}
	printf("�����������Ա����䣬סַ���绰��\n");
	scanf("%s", ml->data[ml->size].name);
	scanf("%s", ml->data[ml->size].sex);
	scanf("%d", &ml->data[ml->size].age);//���鸳��ַ
	scanf("%s", ml->data[ml->size].addr);
	scanf("%s", ml->data[ml->size].tel);
	++ml->size;
}
void Show(MailList *ml)
{
	assert(ml != NULL);
	int i;
	printf("%15s %5s %5s %10s %12s\n", "����", "�Ա�", "����", "סַ", "�绰");
	for (i = 0; i < ml->size; i++)
	{
		printf("%15s %5s %5d %10s %12s\n", ml->data[i].name, ml->data[i].sex, ml->data[i].age, ml->data[i].addr, ml->data[i].tel);
	}
}
void Sort(MailList *ml)
{
	int i, j;//ð��
	Student temp;
	assert(ml != NULL);
	for (i = 0; i < ml->size - 1 - i; i++)
	{
		for (j = 0; j < ml->size - 1 - i; j++)
		{
			if (strcmp(ml->data[j].name, ml->data[j + 1].name)>0)
			{
				temp = ml->data[j];
				ml->data[j] = ml->data[j + 1];
				ml->data[j + 1] = temp;
			}
		}
	}

}
int FindName(MailList *ml, char*name)
{
	int i;
	for (i = 0; i < ml->size; i++)
	{
		if (strcmp(ml->data[i].name, name)==0)
			return i;
	}
	return -1;
}
int IsEmpty(MailList *ml)
{
	return ml->size == 0 ? 1 : 0;
}
void Del(MailList *ml)
{
	char name[NAME_SIZE];
	int i, n;
	assert(ml != NULL);
	if (IsEmpty(ml))
	{
		printf("ͨѶ¼Ϊ��\n");
		return;
	}
	printf("��������Ҫɾ������Ϣ��������\n");
	scanf("%s", name);
	n = FindName(ml, name);
	if (n == -1)
	{
		return;
	}//�ƶ�ͨѶ¼
	for (i = n; i <= ml->size - 1; i++)
	{
		ml->data[i] = ml->data[i + 1];
	}
	ml->size--;
}
void Search(MailList *ml)
{
	char name[NAME_SIZE];
	printf("������������\n");
	scanf("%s", name);
	int i;
	for (i = 0; i < ml->size; i++)
	{
		if (strcmp(ml->data[i].name, name) == 0)
		{
			printf("%15s %5s %5s %10s %12s\n", "����", "�Ա�", "����", "סַ", "�绰");
			printf("%15s %5s %5d %10s %12s\n", ml->data[i].name, ml->data[i].sex, ml->data[i].age, ml->data[i].addr, ml->data[i].tel);
		}	
	}
		printf("�Ҳ���/n");
}
void Modify(MailList *ml)
{
	char name[NAME_SIZE];
	int n;
	assert(ml != NULL);
	printf("��������Ҫ�޸ĵ���Ϣ��������\n");
	scanf("%s", name);
	n = FindName(ml, name);
	if (n == -1)
	{
		printf("�޸�����Ϣ��\n");
	}
	else
	{
		printf("��������Ҫ�޸ĵ���Ϣ��\n");
		scanf("%s %s %d %s %s\n", ml->data[n].name, ml->data[n].sex, &ml->data[n].age, ml->data[n].addr, ml->data[n].tel);
	}
}
void Test()
{
	int input;
	MailList ml;
	InitMailList(&ml);
	menu();
	do
	{
		printf("������ʵ�ֹ��ܣ�\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			Add(&ml);
			break;
		case 2:
			Del(&ml);
			break;
		case 3:
			Modify(&ml);
			break;
		case 4:
			Search(&ml);
			break;
		case 5:
			Sort(&ml);
			break;
		case 6:
			break;
		case 7:
			Show(&ml);
			break;
		case 0:
			printf("��������\n");
			break;
		}
	} while (input);
}
int main()
{
	Test();
	return 0;
}