//#define _CRT_SECURE_NO_WARNINGS //ѹ���ϰ汾C���о���ĺ���
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//#include<WinSock2.h>  //windowsͨ��Э��
//#include<Windows.h>
//#include "C:\Program Files\MySQL\MySQL Server 5.7\include\mysql.h"
//#include<conio.h>
//#include<process.h>
//#pragma comment(lib,"libmysql.lib")  //mysql�Ķ�̬���ӿ�
//#include<WinSock2.h>  //windowsͨ��Э��
//#include<Windows.h>
//
#define false 0
#define true 1
////��Ҫ����
//MYSQL mysql, *sock;
//const char *host = "127.0.0.1";
//const char *user = "root";
//const char *pass = "111111";   //�����Լ���������޸�
//const char *db = "hotel";    //�����Լ����ݿ�����޸�
//const int port = 3306;       //Ĭ�϶˿ں�3306
//const char *win_socket = NULL;
//int xianshitiaoshu;   //��ҳ��ѯ��ÿҳ��ʾ������
//const long flag = 0;  //ͨ��Ϊ0
//const char* query;  //�����ѯ�����
//MYSQL_RES* result; //�����ָ��
//MYSQL_ROW row;
//��Ҫ����

#include"waiter.h"

//����Ա����
//char *admin = (char*)malloc(100);
//char *adminpassword = (char *)malloc(100);
//����Ա����

int SingleAdminSelect(char Wid[]){
	
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from waiter where Wid = '%s'", Wid);
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	if ((row = mysql_fetch_row(result)) == NULL){   //�����ѯ����ֵΪ�գ�����������ݿ��ﲻ�������Ա��������false
		printf("��Ϣ������");
		return false;
	}
	printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
	
	return true;
}

void Adminmenu();
//����Ա��¼ҳ��

void Admin()
{
	char admin[20];
	char adminpassword[20];

	printf("�������û�����");
	scanf("%s", admin);
	printf("���������룺");
	scanf("%s", adminpassword);
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from admin where Aid = '%s'", admin);
	if (mysql_query(&mysql, sql) != 0){    //����ֵ ��ѯ�ɹ���0,������ѯΪ��
		printf("δ��ɲ�ѯ");
		exit(1);
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("�޽��,�����޷��洢�����");
		}
		else{
			row = mysql_fetch_row(result);        //����Ѿ��ж�����Ϊ����ֻ��һ��������ֱ�Ӹ�ֵ����
			if (row == NULL){ 
				printf("�û�������,����������");
				Sleep(600);
				return; 
			}
			if (strcmp(row[1], adminpassword) == 0){   //������бȶ��Ƿ���ȷ
				printf("��¼�ɹ�\n");    //Ȼ������¼����
				for (int a = 0; a<5; a++)
				{
					printf(".");
					Sleep(600);
				}
				system("cls");                     //����
				mysql_free_result(result);        //�ͷŽ����
				//��¼����
				Adminmenu();

				//�ͷŽ����
			}
			else{
				printf("�������\n");
				Sleep(600);
			}
		}
	}
}

void AdminSelectAll(int page)
{
	if (page == 1){
		printf("������ÿҳ��ʾ����:");
		scanf("%d", &xianshitiaoshu);      //ÿҳ��ʾ����Ա�ĸ���
	}
	if (page == -1){
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from waiter limit %d,%d", index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0){    //����ֵ ��ѯ�ɹ���0
		printf("��ѯʧ��");
		exit(1);
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("�޽��,�����޷��洢�����");
		}
		else{
			printf("\t\t\t\t\t��%dҳ\n", page);
			while ((row = mysql_fetch_row(result)) != NULL){
				printf("%s\t%s\t%s\t%s\t%s\t\n", row[0], row[1], row[2], row[3],row[4]);
			}
		}
	}
	//�ͷŽ����
	mysql_free_result(result);
	printf("��һҳ������-1�˳�)");
	int cho;  //���������ҳ��
	printf("��ѡ��:");
	scanf("%d", &cho);
	system("cls");
	AdminSelectAll(cho);
}

//����Ա�޸�����
void AdminUpdate()
{
	char Wid[20];   //�洢ID
	char Wrole[20];    //�洢ְλ
	printf("������Ҫ�޸�ְλ�ķ���ԱID��");
	scanf("%s", Wid);
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from waiter where Wid = '%s'", Wid);
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	while ((row = mysql_fetch_row(result)) == NULL){    //����ֵ ��ѯ�ɹ���0
		printf("�޴�ID,���������룺");
		scanf("%s", Wid);
		sprintf(sql, "select * from waiter where Wid = '%s'", Wid);
		mysql_free_result(result);     //ÿ��ִ��ǰ���ͷŽ����
		mysql_query(&mysql, sql);
		result = mysql_store_result(&mysql);
	}
	system("cls");
	printf("���ҳɹ�����ID��ϢΪ\n");
	printf("%s\t%s\t%s\t%s\t%s\t\n", row[0], row[1], row[2], row[3],row[4]);
	printf("������Ա���޸ĺ��ְλ(ǰ̨����Ա/����/����Ա/����Ա����");
	int flag = 1;   //����ְλ�ɹ����Ϊ0
	while (flag){
		scanf("%s", Wrole);
		if (strcmp(Wrole, "ǰ̨����Ա") == 0){
			flag = 0;
			sprintf(sql, "update waiter set Wrole = '%s',Wpriority='��ס' where Wid = '%s'", Wrole, Wid);
		}
		else if (strcmp(Wrole, "����") == 0){
			flag = 0;
			sprintf(sql, "update waiter set Wrole = '%s',Wpriority='��ס' where Wid = '%s'", Wrole, Wid);
		}
		else if (strcmp(Wrole, "����Ա") == 0){
			flag = 0;
			sprintf(sql, "update waiter set Wrole = '%s',Wpriority='��Ȩ��' where Wid = '%s'", Wrole, Wid);
		}
		else if (strcmp(Wrole, "����Ա") == 0){
			flag = 0;
			sprintf(sql, "update waiter set Wrole = '%s',Wpriority='����' where Wid = '%s'", Wrole, Wid);
		}
		else{
			printf("����Ӧְλ,����������\n");
		}
	}
	if (mysql_query(&mysql, sql) != 0){    //����ֵ ��ѯ�ɹ���0
		printf("�޸�ʧ��");
		exit(1);
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("�ɹ���Ӱ����%d��", mysql_affected_rows(&mysql));
		}
		else{
			printf("ʧ��");
		}
	}
}

//����Ա��������
void AdminAdd()
{
	char Wid[20];
	char Wpassword[20];
	char Wrole[20];
	char Wname[20];
	printf("������Ҫ���ӵ�Ա����ţ�Ա�����������룬����ְλ:\n");
	scanf("%s%s%s%s", Wid, Wname,Wpassword,Wrole);
	char* sql = (char*)malloc(100);
	if (strcmp(Wrole, "ǰ̨����Ա") == 0){
		sprintf(sql, "insert  into waiter  values('%s','%s','%s','%s','��ס')", Wid, Wname, Wpassword, Wrole);
	}
	else if (strcmp(Wrole, "����") == 0){
		sprintf(sql, "insert  into waiter  values('%s','%s','%s','%s','���й���')", Wid, Wname, Wpassword, Wrole);
	}
	else if (strcmp(Wrole, "����Ա") == 0){
		sprintf(sql, "insert  into waiter  values('%s','%s','%s','%s','��Ȩ��')", Wid, Wname, Wpassword, Wrole);
	}
	else if (strcmp(Wrole, "����Ա") == 0){
		sprintf(sql, "insert  into waiter  values('%s','%s','%s','%s','����')", Wid, Wname, Wpassword, Wrole);
	}

	if (mysql_query(&mysql, sql) != 0){    //����ֵ �ɹ���0
		printf("����ʧ��");
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("�ɹ���Ӱ����%d��\n", mysql_affected_rows(&mysql));
			SingleAdminSelect(Wid);
		}
		else{
			printf("ʧ��");
		}
	}
}

//����Աɾ��Ա������
void AdminDeleteData()
{
	char* sql2 = (char*)malloc(100);
	char Wid[20];
	printf("Ҫɾ����ְ���ţ�");
	scanf("%s", Wid);
	while (SingleAdminSelect(Wid) == false){
		printf("��������ȷ��Ա����: ");
		scanf("%s", Wid);
	}
	query = "delete from waiter where Wid='%s'";
	sprintf(sql2, query, Wid);
	mysql_query(&mysql, sql2);
	printf("\n��ɾ����Ա��\n");
}

int Login()
{
	char *admin = (char*)malloc(100);
	char *adminpassword = (char *)malloc(100);
	printf("�������û�����");
	scanf("%s", admin);
	printf("���������룺");
	scanf("%s", adminpassword);
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from waiter where Wid = '%s'", admin);
	if (mysql_query(&mysql, sql) != 0){    //����ֵ ��ѯ�ɹ���0
		printf("�û�������ȷ");
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("�޽��,�����޷��洢�����");
		}
		else{
			row = mysql_fetch_row(result);        //����Ѿ��ж�����Ϊ����ֻ��һ��������ֱ�Ӹ�ֵ����

			if (row == NULL){
				printf("�û�������,����������");
				Sleep(600);
				return;
			}

			if (strcmp(row[2], adminpassword) == 0){   //������бȶ��Ƿ���ȷ
				printf("��¼�ɹ�\n");    //Ȼ������¼����
				for (int a = 0; a<5; a++)
				{
					printf(".");
					Sleep(600);
				}
				system("cls");                     //����
				//mysql_free_result(result);        //�ͷŽ����
				//��¼����
				printf("%s\n", row[3]);
				if (strcmp(row[3], "ǰ̨����Ա") == 0){
					Waitermenu();
				}
				else if (strcmp(row[3], "����") == 0){
					Bossmenu();
				}
				else if (strcmp(row[3], "����Ա") == 0){
					Cleanermenu();
				}
				else if (strcmp(row[3], "����Ա") == 0){
					Moneymenu();
				}
				else
				{
					printf("��ݴ���");
				}

				//�ͷŽ����
				mysql_free_result(result);
			}
			else{
				printf("�������\n");
				Sleep(600);
			}
		}
	}
	return;
}

void mainWindow()
{
	while (1)
	{
		head();
		printf("\t\t\t*          *            ��ӭ�����Ƶ��̨����ϵͳ             *            *\n");
		printf("\t\t\t*          *            ��ѡ���¼����ע��                   *            *\n");
		printf("\t\t\t*          *            1.��̨����Ա��¼                     *            *\n");
		printf("\t\t\t*          *            2.Ա����¼                           *            *\n");
		printf("\t\t\t*          *            3.�˳�                               *            *\n");
		int n;
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			Admin();
			break;
		case 2:
			Login();
			break;
		case 3:
			exit(0);
		default:
			printf("�����������������:\n");
			break;
		}
		system("cls");
	}
}

void Adminmenu()
{
	int flag = 1;
	while (flag)
	{
		head();
		printf("\t\t\t*          *                   ����Ա����                    *            *\n");
		printf("\t\t\t*          *               ������Ҫʵ�ֵĹ���                *            *\n");
		printf("\t\t\t*          *               1.��ѯ����Ա����Ϣ                *            *\n");
		printf("\t\t\t*          *               2.��ѯ����Ա����Ϣ                *            *\n");
		printf("\t\t\t*          *               3.���Ա������                    *            *\n");
		printf("\t\t\t*          *               4.ɾ��Ա������                    *            *\n");
		printf("\t\t\t*          *               5.�޸�Ա������                    *            *\n");
		printf("\t\t\t*          *               6.���ػ�ӭ����                    *            *\n");
		int n;
		scanf("%d", &n);
		switch (n)
		{
		int index;                 //��������Ļ����ʾʱ�䣬��-1�˳�
		case 1:
			
			AdminSelectAll(1);      //��ѯ����Ա����Ϣ
			break;
		case 2:
			printf("������Ա���ţ�");    //��ѯ����Ա����Ϣ 
			char Wid[20];
			scanf("%s", Wid);
			SingleAdminSelect(Wid);
			printf("�����������˳���");
			scanf("%d", &index);
			break;
		case 3:
			AdminAdd();            //����Ա����Ϣ
			printf("�����������˳���");
			scanf("%d", &index);
			break;
		case 4:
			AdminDeleteData();    //ɾ��Ա����Ϣ
			printf("�����������˳���");
			scanf("%d", &index);
			break;
		case 5:
			AdminUpdate();    //�޸�Ա����Ϣ
			printf("�����������˳���");
			scanf("%d", &index);
			break;
		case 6:
			
			flag = 0;        //����������-------------------------------------------------------------------
			break;
		default:
			printf("�����������������:\n");
			break;
		}
		system("cls");
	}
}
int main(){
	system("color bc");
	Connect();
	mainWindow();
	return 0;
}

