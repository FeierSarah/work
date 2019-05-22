#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef struct node //定义结构体
{
	int num; //学号
	char name[15];//姓名
	char sex[5];
	int english; //英语成绩
	int math; //数学成绩
	int chinese;//语文成绩
	int science;
	int result;//语、数、英、理综 三成绩总和 
	struct node *next; //链表指针域
	struct tree *left, *right;
}student_info;
typedef struct tree
{
	student_info* data;
	struct tree *left, *right;
}tree;

//学生信息链表
student_info* student_list;  //全局变量声明


//初始化函数声明
//初始化学生信息链表
void init_student_info_list();
//判断学生信息链表是否为空
int student_list_empty();

//操作函数声明
//向学校信息表中添加学生信息记录
int add_student_info();
//根据学号删除学生信息
int delete_student_info(int num);
//根据学号修改学生信息
int modify_student_info(int num);
//根据学号查找学生信息
student_info* search_student_info(int num);
//显示所有学生信息
void display_student_info();
//将学生信息保存到文件
int save_file();
//从文件中读取学生信息
int read_file();


//初始化学生信息链表
void init_student_info_list()
{
	//学生信息链表头结点
	student_list = (student_info*)malloc(sizeof(student_info));
	student_list->next = NULL;
}
//判断学生信息链表是否为空
int student_list_empty()
{
	return student_list->next == NULL;
}
//操作函数实现
//向学校信息表中添加学生信息记录
int add_student_info()
{
	int n;
	student_info *pstu = (student_info*)malloc(sizeof(student_info));
	if (pstu == NULL)
	{
		printf("内存分配失败.\n");
		return 0;
	}
	printf("1.从文件中查找学生信息\n2.从键盘中添加学生信息");
	scanf("%d", &n);
	if (n == 2)
	{
		printf("请按要求一次输入学生的信息.\n");
		printf("请输入学号: ");
		scanf("%d", &pstu->num);
		//判断该学号是否已经存在
		if (search_student_info(pstu->num) != NULL)
		{
			printf("该学号已经存在学生信息表中.\n");
			return 0;
		}
		printf("请输入姓名: ");
		getchar();
		scanf("%s", pstu->name);
		printf("请输入姓别: ");
		getchar();
		scanf("%s", pstu->sex);
		printf("请输入英语成绩: ");
		scanf("%d", &pstu->english);
		printf("请输入数学成绩: ");
		scanf("%d", &pstu->math);
		printf("请输入语文成绩: ");
		scanf("%d", &pstu->chinese);
		printf("请输入理综成绩: ");
		scanf("%d", &pstu->science);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		//每次从学生信息链表的头部插入;
		pstu->next = student_list->next;
		student_list->next = pstu;
		save_file();
		return 1;
	}
	else
		read_file();
}
//根据学号删除学生信息
int delete_student_info(int num)
{
	student_info *pstu;
	student_info *qstu;
	if (search_student_info(num) == NULL)
	{
		printf("不存在该学号为%d的学生信息\n", num);
		return 0;
	}
	pstu = student_list->next;
	qstu = student_list;
	while (pstu->num != num)
	{
		qstu = pstu;
		pstu = pstu->next;
	}
	qstu->next = pstu->next;
	free(pstu);
	return 1;
}
//根据学号修改学生信息
int modify_student_info(int num)
{
	int choice;
	student_info *pstu = search_student_info(num);
	if (pstu == NULL)
	{
		printf("不存在该学号为%d的学生信息.\n", num);
		return 0;
	}
	printf("1.姓名 2.性别 3.英语成绩 4.数学成绩 5.语文成绩 6.理综成绩\n");
	printf("请选择修改的信息: ");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("请输入新的姓名: ");
		getchar();
		scanf("%s", pstu->name);
		break;
	case 2:
		printf("请输入新的性别: ");
		getchar();
		scanf("%s", pstu->sex);
		break;
	case 3:
		printf("请输入新的英语成绩: ");
		scanf("%d", &pstu->english);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		break;
	case 4:
		printf("请输入新的数学成绩: ");
		scanf("%d", &pstu->math);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		break;
	case 5:
		printf("请输入新的语文成绩: ");
		scanf("%d", &pstu->chinese);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		break;
	case 6:
		printf("请输入新的理综成绩: ");
		scanf("%d", &pstu->science);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		break;
	default:
		printf("请按提示要求操作.\n");
	}
	return 1;
}
//根据学号查找学生信息
student_info* search_student_info(int num)
{
	student_info *pstu;
	pstu = student_list->next;
	while (pstu  && pstu->num != num)
	{
		pstu = pstu->next;
	}
	return pstu;
}
//求学生信息个数 
int  count_student_info()
{
	student_info *pstu;
	pstu = student_list->next;
	int count = 0;
	while (pstu)
	{
		pstu = pstu->next;
		count++;
	}
	return count;
	printf("%d", count);
}
//找到第k个信息
student_info*select_k(int k)
{
	student_info *pstu;
	pstu = student_list->next;
	for (; k > 0; k--)
	{
		pstu = pstu->next;
	}
	return pstu;
}
//根据学号折半查找学生信息
student_info* search_student_info_zheban(int num)
{
	student_info *pstu;
	pstu = student_list->next;
	int i = count_student_info();
	int left = 1, right = i, mid;
	while (left <= right)
	{
		student_info* result = NULL;
		mid = left + ((right - left) >> 1);
		result = select_k(mid);
		if (result->num < num)
			left = mid + 1;
		else if (result->num > num)
			right = mid - 1;
		else
			return result;
	}
	printf("查无此人");
}
//在第i个到最后一个信息中求最大理综成绩所在位置 
int selectmaxkey(int i)
{
	int k=0;
	int count=i;
	student_info *pstu;
	pstu = select_k(i);
	student_info *pstv;
	pstv = select_k(i + 1);
	printf("%s", select_k(i)->name);
	printf("%s", select_k(i+1)->name);
	while (select_k(count + 1)!=NULL)
	{
		if (pstu->science > pstv->science)
		{
			k = i;
			i++;
		}
		else
		{
			k = i + 1;
			i++;
		}
		count++;
		pstu = select_k(count);
		pstv = select_k(count+1);
	}
	return k;
}
//交换整数型 
void swap_int(int * p1, int *p2)
{
	int tmp;
	tmp = (*p1);
	*(p1) = (*p2);
	*(p2) = tmp;
}
//交换字符串型 
void swap_char(char * p1, char *p2)
{
	char tmp;
	tmp = (*p1);
	*(p1) = (*p2);
	*(p2) = tmp;
}
//交换结点 
void swap_node(student_info *p1, student_info *p2)
{
	int i;
	swap_int(&(p1->num), &(p2->num));
	swap_int(&(p1->english), &(p2->english));
	swap_int(&(p1->math), &(p2->math));
	swap_int(&(p1->chinese), &(p2->chinese));
	swap_int(&(p1->science), &(p2->science));
	swap_int(&(p1->result), &(p2->result));
	for (i = 0; i < 5; i++)
	{
		swap_char(&(p1->sex[i]), &(p2->sex[i]));
	}
	for (i = 0; i < 15; i++)
	{
		swap_char(&(p1->name[i]), &(p2->name[i]));
	}
}
//理综成绩按从大到小简单选择排序
void arrange_science_jiandanxuanze()
{
	int i, j;
	for (i = 0; i < (count_student_info()-1); i++)
	{
		j = selectmaxkey(i);
		if (i != j)
		{
			swap_node(select_k(i), select_k(j));
		}
	}
}
//学号按从小到大冒泡排序 
void arrange_num_maopao()
{
	student_info*pstu;
	student_info*teil = NULL;
	pstu = student_list->next;
	while (pstu != teil)
	{
		while (pstu->next != teil)
		{
			if (pstu->num > pstu->next->num)
			{
				swap_node(pstu, pstu->next);
			}
			pstu = pstu->next;
		}
		teil = pstu;
		pstu = student_list->next;
	}
	return;
}
//交换表中low和high的记录，枢纽记录到位，返回其所在位置 ；在它之前（后）的记录均不大（小）于它 
int partition(int left, int right)
{
	student_info *p_key = select_k(right);
	student_info *p_left = select_k(left);
	student_info *p_right = select_k(right);
	int key = p_key->result;
	while (left < right)
	{
		while (left < right&&p_left->result >= key)
		{
			left++;
			p_left = select_k(left);
		}
		while (left < right&&p_right->result < key)
		{
			right--;
			p_right = select_k(right);
		}
		swap_node(select_k(left), select_k(right));
	}
	swap_node(select_k(left), p_key);
	return left;
}
//总成绩按从大到小快速排序
void arrange_result_kuaipai(int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int key = partition(left, right);
	arrange_result_kuaipai(left, key - 1);
	arrange_result_kuaipai(key + 1, right);
}
//显示所有学生信息
void display_student_info()
{
	student_info *pstu;
	pstu = student_list->next;
	printf("所有学生信息如下所示.\n");
	printf("序号\t学号\t姓名\t性别\t英语\t数学\t语文\t理综\t总成绩\t.\n");
	for (int i = 1; i <= count_student_info(); i++)
	{
		printf("%d\t", i);
		printf("%d\t", pstu->num);
		printf("%s\t", pstu->name);
		printf("%s\t", pstu->sex);
		printf("%d\t", pstu->english);
		printf("%d\t", pstu->math);
		printf("%d\t", pstu->chinese);
		printf("%d\t", pstu->science);
		printf("%d\t", pstu->result);
		printf("\n");
		pstu = pstu->next;
	}
}
//插入结点 
void InsertBST(tree **bt, student_info *elem)
{
	if ((*bt) == NULL)
	{
		*bt = (tree*)malloc(sizeof(tree));
		(*bt)->data = elem;
		(*bt)->right = (*bt)->left = NULL;
	}
	else if (elem->result < (*bt)->data->result)
	{
		InsertBST(&((*bt)->left), elem);//插入到左子树 
	}
	else
	{
		InsertBST(&((*bt)->right), elem);//插入到右子树 
	}
}
//构造二叉排序树 
tree **CreatBST()
{
	int n = count_student_info();
	tree **bt = NULL;
	for (int i = 1; i <= n; i++)
	{
		InsertBST(bt, select_k(i));
	}
	return bt;
}
int n = 1;
//二叉排序树的查找 
int Search(tree *bt, int elem)
{
	if (bt == NULL)//如结点部存在插找失败 
	{
		return -1;
	}
	else if (elem == bt->data->result)
	{
		return n;
	}
	n++;
	if (elem < bt->data->result)
	{
		return Search(bt->left, elem);
	}
	else
	{
		return Search(bt->right, elem);
	}
}

//将学生信息保存到文件
int save_file()
{
	FILE *pfile;
	student_info *pstu;
	pfile = fopen("student.txt", "w");
	if (pfile == NULL)
	{
		printf("打开文件失败.\n");
		return 0;
	}
	pstu = student_list->next;
	while (pstu)
	{
		fprintf(pfile, "%5d%15s%5s%4d%4d%4d%4d%4d", pstu->num, pstu->name,
			pstu->sex, pstu->english, pstu->math, pstu->chinese,pstu->science,pstu->result);
		pstu = pstu->next;
	}
	fclose(pfile);
	return 1;
}

//从文件中读取学生信息
int read_file()
{
	FILE *pfile;
	student_info *pstu;
	pfile = fopen("student.txt", "r");
	if (pfile == NULL)
	{
		printf("打开文件失败.\n");
		return 0;
	}
	while (!feof(pfile))
	{
		pstu = (student_info*)malloc(sizeof(student_info));
		fscanf(pfile, "%5d%15s%5s%4d%4d%4d%4d%4d", &(pstu->num), pstu->name,
			pstu->sex, &(pstu->english), &(pstu->math), &(pstu->chinese), &(pstu->science), &(pstu->result));
		//每次从学生信息链表的头部插入;
		pstu->next = student_list->next;
		student_list->next = pstu;
	}
	fclose(pfile);
	return 1;
}

void menu();

//用户可以选择1-7可以分别进行学生信息的查看、添加、删除，修改，计算平均成绩，保存，退出系统操作。
int main()
{
	int choice;
	int num;
	tree* root = NULL;

	init_student_info_list();
	int left = 0;
	int right;

	while (1)
	{
		system("cls");
		printf("**************************\n");
		printf("欢迎使用学生信息管理系统\n");
		printf("**************************\n");
		printf("-----------------------------\n");
		menu();
		printf("请选择操作: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			if (student_list_empty())
				printf("学生信息表为空，请先添加学生信息.\n");
			else
				display_student_info();
			break;
		case 2:
			if (add_student_info())
				printf("添加学生信息成功.\n");
			else
				printf("添加学生信息失败.\n");
			break;
		case 3:
			if (student_list_empty())
				printf("学生信息表为空，请先添加学生信息.\n");
			else
			{
				printf("请输入要删除学生信息的学号: ");
				scanf("%d", &num);
				if (delete_student_info(num))
					printf("成功删除该学号对应的学生信息.\n");
				else
					printf("删除失败.\n");
			}
			break;
		case 4:
			if (student_list_empty())
				printf("学生信息表为空，请先添加学生信息.\n");
			else
			{
				printf("请输入要修改学生信息的学号: ");
				scanf("%d", &num);
				if (modify_student_info(num))
					printf("成功修改该学号对应的学生信息.\n");
				else
					printf("修改失败.\n");
			}
			break;
		case 5:
			if (student_list_empty())
				printf("学生信息表为空，请先添加学生信息.\n");
			else
			{
				printf("请输入要查询学生信息的学号: ");
				scanf("%d", &num);
				printf("\t%d\t", search_student_info_zheban(num)->num);
				printf("%s\t", search_student_info_zheban(num)->name);
				printf("%s\t", search_student_info_zheban(num)->sex);
				printf("%d\t", search_student_info_zheban(num)->english);
				printf("%d\t", search_student_info_zheban(num)->math);
				printf("%d\t", search_student_info_zheban(num)->chinese);
				printf("%d\t", search_student_info_zheban(num)->science);
				printf("%d\t", search_student_info_zheban(num)->result);
			}
			break;
		case 6:
			if (add_student_info())
				printf("创建学生信息成功.\n");
			else
				printf("创建学生信息失败.\n");
			break;
		case 7:
			if (student_list_empty())
				printf("学生信息表为空，请先添加学生信息.\n");
			else
			{
				printf("请输入要查询学生信息的总成绩: ");
				scanf("%d", &num);
				printf("\t%d\t", select_k(Search(root, num))->num);
				printf("%s\t", select_k(Search(root, num))->name);
				printf("%s\t", select_k(Search(root, num))->sex);
				printf("%d\t", select_k(Search(root, num))->english);
				printf("%d\t", select_k(Search(root, num))->math);
				printf("%d\t", select_k(Search(root, num))->chinese);
				printf("%d\t", select_k(Search(root, num))->science);
				printf("%d\t", select_k(Search(root, num))->result);
			}
			break;
		case 8:
			if (student_list_empty())
				printf("学生信息表为空，请先添加学生信息.\n");
			else
				arrange_num_maopao();
				display_student_info();
			break;
		case 9:
			if (student_list_empty())
				printf("学生信息表为空，请先添加学生信息.\n");
			else
				arrange_science_jiandanxuanze();
			display_student_info();
			break;
		case 10:
			right = count_student_info() ;
			if (student_list_empty())
				printf("学生信息表为空，请先添加学生信息.\n");
			else
				arrange_result_kuaipai(left, right-1);
				display_student_info();
			break;
		case 0:
			printf("欢迎下次使用,再见.\n");
			system("pause");
			exit(0);
			break;
		default:
			printf("输入错误，请重新选择操作.\n");
		}
		system("pause");
	}
	system("pause");
	return 0;
}

void menu()
{
	printf("1.查看学生信息.\n");
	printf("2.添加学生信息.\n");
	printf("3.删除学生信息.\n");
	printf("4.修改学生信息.\n");
	printf("5.按学号查找学生信息.\n");
	printf("6.创建学生信息.\n");
	printf("7.按总成绩查找学生信息.\n");
	printf("8.学号按从小到大排序.\n");
	printf("9.理综成绩排名.\n");
	printf("10.总成绩排名.\n");
	printf("0.退出系统操作.\n");
}
