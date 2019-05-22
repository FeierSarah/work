#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef struct node //����ṹ��
{
	int num; //ѧ��
	char name[15];//����
	char sex[5];
	int english; //Ӣ��ɼ�
	int math; //��ѧ�ɼ�
	int chinese;//���ĳɼ�
	int science;
	int result;//�����Ӣ������ ���ɼ��ܺ� 
	struct node *next; //����ָ����
	struct tree *left, *right;
}student_info;
typedef struct tree
{
	student_info* data;
	struct tree *left, *right;
}tree;

//ѧ����Ϣ����
student_info* student_list;  //ȫ�ֱ�������


//��ʼ����������
//��ʼ��ѧ����Ϣ����
void init_student_info_list();
//�ж�ѧ����Ϣ�����Ƿ�Ϊ��
int student_list_empty();

//������������
//��ѧУ��Ϣ�������ѧ����Ϣ��¼
int add_student_info();
//����ѧ��ɾ��ѧ����Ϣ
int delete_student_info(int num);
//����ѧ���޸�ѧ����Ϣ
int modify_student_info(int num);
//����ѧ�Ų���ѧ����Ϣ
student_info* search_student_info(int num);
//��ʾ����ѧ����Ϣ
void display_student_info();
//��ѧ����Ϣ���浽�ļ�
int save_file();
//���ļ��ж�ȡѧ����Ϣ
int read_file();


//��ʼ��ѧ����Ϣ����
void init_student_info_list()
{
	//ѧ����Ϣ����ͷ���
	student_list = (student_info*)malloc(sizeof(student_info));
	student_list->next = NULL;
}
//�ж�ѧ����Ϣ�����Ƿ�Ϊ��
int student_list_empty()
{
	return student_list->next == NULL;
}
//��������ʵ��
//��ѧУ��Ϣ�������ѧ����Ϣ��¼
int add_student_info()
{
	int n;
	student_info *pstu = (student_info*)malloc(sizeof(student_info));
	if (pstu == NULL)
	{
		printf("�ڴ����ʧ��.\n");
		return 0;
	}
	printf("1.���ļ��в���ѧ����Ϣ\n2.�Ӽ��������ѧ����Ϣ");
	scanf("%d", &n);
	if (n == 2)
	{
		printf("�밴Ҫ��һ������ѧ������Ϣ.\n");
		printf("������ѧ��: ");
		scanf("%d", &pstu->num);
		//�жϸ�ѧ���Ƿ��Ѿ�����
		if (search_student_info(pstu->num) != NULL)
		{
			printf("��ѧ���Ѿ�����ѧ����Ϣ����.\n");
			return 0;
		}
		printf("����������: ");
		getchar();
		scanf("%s", pstu->name);
		printf("�������ձ�: ");
		getchar();
		scanf("%s", pstu->sex);
		printf("������Ӣ��ɼ�: ");
		scanf("%d", &pstu->english);
		printf("��������ѧ�ɼ�: ");
		scanf("%d", &pstu->math);
		printf("���������ĳɼ�: ");
		scanf("%d", &pstu->chinese);
		printf("���������۳ɼ�: ");
		scanf("%d", &pstu->science);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		//ÿ�δ�ѧ����Ϣ�����ͷ������;
		pstu->next = student_list->next;
		student_list->next = pstu;
		save_file();
		return 1;
	}
	else
		read_file();
}
//����ѧ��ɾ��ѧ����Ϣ
int delete_student_info(int num)
{
	student_info *pstu;
	student_info *qstu;
	if (search_student_info(num) == NULL)
	{
		printf("�����ڸ�ѧ��Ϊ%d��ѧ����Ϣ\n", num);
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
//����ѧ���޸�ѧ����Ϣ
int modify_student_info(int num)
{
	int choice;
	student_info *pstu = search_student_info(num);
	if (pstu == NULL)
	{
		printf("�����ڸ�ѧ��Ϊ%d��ѧ����Ϣ.\n", num);
		return 0;
	}
	printf("1.���� 2.�Ա� 3.Ӣ��ɼ� 4.��ѧ�ɼ� 5.���ĳɼ� 6.���۳ɼ�\n");
	printf("��ѡ���޸ĵ���Ϣ: ");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("�������µ�����: ");
		getchar();
		scanf("%s", pstu->name);
		break;
	case 2:
		printf("�������µ��Ա�: ");
		getchar();
		scanf("%s", pstu->sex);
		break;
	case 3:
		printf("�������µ�Ӣ��ɼ�: ");
		scanf("%d", &pstu->english);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		break;
	case 4:
		printf("�������µ���ѧ�ɼ�: ");
		scanf("%d", &pstu->math);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		break;
	case 5:
		printf("�������µ����ĳɼ�: ");
		scanf("%d", &pstu->chinese);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		break;
	case 6:
		printf("�������µ����۳ɼ�: ");
		scanf("%d", &pstu->science);
		pstu->result = pstu->english + pstu->math + pstu->chinese + pstu->science;
		break;
	default:
		printf("�밴��ʾҪ�����.\n");
	}
	return 1;
}
//����ѧ�Ų���ѧ����Ϣ
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
//��ѧ����Ϣ���� 
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
//�ҵ���k����Ϣ
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
//����ѧ���۰����ѧ����Ϣ
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
	printf("���޴���");
}
//�ڵ�i�������һ����Ϣ����������۳ɼ�����λ�� 
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
//���������� 
void swap_int(int * p1, int *p2)
{
	int tmp;
	tmp = (*p1);
	*(p1) = (*p2);
	*(p2) = tmp;
}
//�����ַ����� 
void swap_char(char * p1, char *p2)
{
	char tmp;
	tmp = (*p1);
	*(p1) = (*p2);
	*(p2) = tmp;
}
//������� 
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
//���۳ɼ����Ӵ�С��ѡ������
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
//ѧ�Ű���С����ð������ 
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
//��������low��high�ļ�¼����Ŧ��¼��λ������������λ�� ������֮ǰ���󣩵ļ�¼������С������ 
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
//�ܳɼ����Ӵ�С��������
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
//��ʾ����ѧ����Ϣ
void display_student_info()
{
	student_info *pstu;
	pstu = student_list->next;
	printf("����ѧ����Ϣ������ʾ.\n");
	printf("���\tѧ��\t����\t�Ա�\tӢ��\t��ѧ\t����\t����\t�ܳɼ�\t.\n");
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
//������ 
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
		InsertBST(&((*bt)->left), elem);//���뵽������ 
	}
	else
	{
		InsertBST(&((*bt)->right), elem);//���뵽������ 
	}
}
//������������� 
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
//�����������Ĳ��� 
int Search(tree *bt, int elem)
{
	if (bt == NULL)//���㲿���ڲ���ʧ�� 
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

//��ѧ����Ϣ���浽�ļ�
int save_file()
{
	FILE *pfile;
	student_info *pstu;
	pfile = fopen("student.txt", "w");
	if (pfile == NULL)
	{
		printf("���ļ�ʧ��.\n");
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

//���ļ��ж�ȡѧ����Ϣ
int read_file()
{
	FILE *pfile;
	student_info *pstu;
	pfile = fopen("student.txt", "r");
	if (pfile == NULL)
	{
		printf("���ļ�ʧ��.\n");
		return 0;
	}
	while (!feof(pfile))
	{
		pstu = (student_info*)malloc(sizeof(student_info));
		fscanf(pfile, "%5d%15s%5s%4d%4d%4d%4d%4d", &(pstu->num), pstu->name,
			pstu->sex, &(pstu->english), &(pstu->math), &(pstu->chinese), &(pstu->science), &(pstu->result));
		//ÿ�δ�ѧ����Ϣ�����ͷ������;
		pstu->next = student_list->next;
		student_list->next = pstu;
	}
	fclose(pfile);
	return 1;
}

void menu();

//�û�����ѡ��1-7���Էֱ����ѧ����Ϣ�Ĳ鿴����ӡ�ɾ�����޸ģ�����ƽ���ɼ������棬�˳�ϵͳ������
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
		printf("��ӭʹ��ѧ����Ϣ����ϵͳ\n");
		printf("**************************\n");
		printf("-----------------------------\n");
		menu();
		printf("��ѡ�����: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			if (student_list_empty())
				printf("ѧ����Ϣ��Ϊ�գ��������ѧ����Ϣ.\n");
			else
				display_student_info();
			break;
		case 2:
			if (add_student_info())
				printf("���ѧ����Ϣ�ɹ�.\n");
			else
				printf("���ѧ����Ϣʧ��.\n");
			break;
		case 3:
			if (student_list_empty())
				printf("ѧ����Ϣ��Ϊ�գ��������ѧ����Ϣ.\n");
			else
			{
				printf("������Ҫɾ��ѧ����Ϣ��ѧ��: ");
				scanf("%d", &num);
				if (delete_student_info(num))
					printf("�ɹ�ɾ����ѧ�Ŷ�Ӧ��ѧ����Ϣ.\n");
				else
					printf("ɾ��ʧ��.\n");
			}
			break;
		case 4:
			if (student_list_empty())
				printf("ѧ����Ϣ��Ϊ�գ��������ѧ����Ϣ.\n");
			else
			{
				printf("������Ҫ�޸�ѧ����Ϣ��ѧ��: ");
				scanf("%d", &num);
				if (modify_student_info(num))
					printf("�ɹ��޸ĸ�ѧ�Ŷ�Ӧ��ѧ����Ϣ.\n");
				else
					printf("�޸�ʧ��.\n");
			}
			break;
		case 5:
			if (student_list_empty())
				printf("ѧ����Ϣ��Ϊ�գ��������ѧ����Ϣ.\n");
			else
			{
				printf("������Ҫ��ѯѧ����Ϣ��ѧ��: ");
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
				printf("����ѧ����Ϣ�ɹ�.\n");
			else
				printf("����ѧ����Ϣʧ��.\n");
			break;
		case 7:
			if (student_list_empty())
				printf("ѧ����Ϣ��Ϊ�գ��������ѧ����Ϣ.\n");
			else
			{
				printf("������Ҫ��ѯѧ����Ϣ���ܳɼ�: ");
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
				printf("ѧ����Ϣ��Ϊ�գ��������ѧ����Ϣ.\n");
			else
				arrange_num_maopao();
				display_student_info();
			break;
		case 9:
			if (student_list_empty())
				printf("ѧ����Ϣ��Ϊ�գ��������ѧ����Ϣ.\n");
			else
				arrange_science_jiandanxuanze();
			display_student_info();
			break;
		case 10:
			right = count_student_info() ;
			if (student_list_empty())
				printf("ѧ����Ϣ��Ϊ�գ��������ѧ����Ϣ.\n");
			else
				arrange_result_kuaipai(left, right-1);
				display_student_info();
			break;
		case 0:
			printf("��ӭ�´�ʹ��,�ټ�.\n");
			system("pause");
			exit(0);
			break;
		default:
			printf("�������������ѡ�����.\n");
		}
		system("pause");
	}
	system("pause");
	return 0;
}

void menu()
{
	printf("1.�鿴ѧ����Ϣ.\n");
	printf("2.���ѧ����Ϣ.\n");
	printf("3.ɾ��ѧ����Ϣ.\n");
	printf("4.�޸�ѧ����Ϣ.\n");
	printf("5.��ѧ�Ų���ѧ����Ϣ.\n");
	printf("6.����ѧ����Ϣ.\n");
	printf("7.���ܳɼ�����ѧ����Ϣ.\n");
	printf("8.ѧ�Ű���С��������.\n");
	printf("9.���۳ɼ�����.\n");
	printf("10.�ܳɼ�����.\n");
	printf("0.�˳�ϵͳ����.\n");
}
