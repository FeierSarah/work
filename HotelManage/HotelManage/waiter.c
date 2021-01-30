#include "waiter.h"

MYSQL_RES* result; //�����ָ��
MYSQL_ROW row;
int xianshitiaoshu;
const char* query;

void SelectFullRoomByno(char* no)
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room,client where room.Rno = '%s' and room.Rno = client.Rno", no);
	if (mysql_query(&mysql, sql) != 0)
	{
		printf("�÷�������ס��Ϣ\n");
	}
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);
	
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10]);
	
	mysql_free_result(result);
}

void SelectRoomByno(char* no)
{
	int page = 1;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room where Rno = '%s'", no);
	if (mysql_query(&mysql, sql) != 0) 
	{    //����ֵ ��ѯ�ɹ���0
		printf("��ѯʧ��\n");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL)
		{
			printf("��ѯ�����ÿͷ�\n");
		}
		else
		{
			row = mysql_fetch_row(result);
			if (strcmp(row[2], "��") == 0)
			{
				mysql_free_result(result);
				printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
				printf("��0���ز˵�");
				int tmp;
				scanf("%d", &tmp);
				return;
			}
			else if (strcmp(row[2], "��") == 0)
			{
				mysql_free_result(result);
				SelectFullRoomByno(no);
				printf("��0���ز˵�");
				int tmp;
				scanf("%d", &tmp);
				return;
			}
		}
	}
	//�ͷŽ����

	
}
void PayRoom(char* no)
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select Cday*Rprice from client,room_type where client.Rno = '%s' and room_type.Rtype =(select Rtype from room where Rno='%s');", no, no);
	if (mysql_query(&mysql, sql) != 0)
	{    //����ֵ ��ѯ�ɹ���0
		printf("��ѯʧ��\n");
		exit(1);
	}
	else 
	{
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("�÷���δ��ס�˿�\n");
		}
		else 
		{
			row = mysql_fetch_row(result);
			printf("��֧��%s����\n", row[0]);
		}
	}
	//�ͷŽ����
	mysql_free_result(result);

	char* sql3 = (char*)malloc(100);
	sprintf(sql3, "update room set Rclean = '��' where Rno = '%s'", no);
	mysql_query(&mysql, sql3);

	char* sql4 = (char*)malloc(100);
	sprintf(sql4, "update room_type set Rrest = Rrest+1 where Rtype=(select Rtype from room where Rno = '%s')", no);
	mysql_query(&mysql, sql4);

	char* sql5 = (char*)malloc(100);
	sprintf(sql5, "update room set Rstate = '��' where Rno = '%s'", no);
	mysql_query(&mysql, sql5);

	clientdelete(no);
	int tmp;
	printf("��0���ز˵�\n");
	scanf("%d", &tmp);
}
void SelectRoomByty(char* type, int page)
{
	if (page == 1) {
		printf("������ÿҳ��ʾ����:");
		scanf("%d", &xianshitiaoshu);      //ÿҳ��ʾ����Ա�ĸ���
	}
	if (page == -1) {
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room where Rtype='%s' and Rstate='��' limit %d,%d", type, index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0) {    //����ֵ ��ѯ�ɹ���0
		printf("��ѯʧ��");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("�޽��,�����޷��洢�����");
		}
		else {
			printf("\t\t\t\t\t��%dҳ\n", page);
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("%s\t%s\n", row[0], row[1]);
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
	SelectRoomByty(type, cho);
}

void clientdelete(char* no)
{
	char* sql2 = (char*)malloc(100);
	query = "delete from client where Rno='%s'";
	sprintf(sql2, query, no);

	if (mysql_query(&mysql, sql2) != 0) {    //����ֵ ��ѯ�ɹ���0
		printf("ɾ��ʧ��\n");
		exit(1);
	}
	else 
	{
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("�ͻ���Ϣɾ���ɹ���Ӱ����%d��\n", mysql_affected_rows(&mysql));
		}
		else
		{
			printf("�ͻ���Ϣɾ��ʧ��\n");
		}
	}
}

void clientadd(char* no)
{
	char Cname[20];
	char Cno[20];
	char Ctele[20];
	int Cday;
	char Cin[20];
	char Cout[20];
	printf("������Ҫ���ӵ�ס�����������֤�ţ�ס���绰����ס��������סʱ�䣬����ʱ��:\n");
	scanf("%s%s%s%d%s%s", Cname, Cno, Ctele, &Cday, Cin, Cout);
	char* sql2 = (char*)malloc(100);
	sprintf(sql2, "insert into client values('%s','%s','%s','%s','%d','%s','%s')", no, Cname, Cno, Ctele, Cday, Cin, Cout);

	if (mysql_query(&mysql, sql2) != 0)
	{    //����ֵ ��ѯ�ɹ���0
		printf("�˿���Ϣ¼��ʧ��");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL)
		{
			printf("�˿���Ϣ¼��ɹ���Ӱ����%d��\n", mysql_affected_rows(&mysql));
		}
		else
		{
			printf("�˿���Ϣ¼��ʧ��\n");
		}
	}
}

void CheckRoomByno(char* no)
{
	int n;
	
	printf("��������ס������");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		printf("�������%d��ס����Ϣ��\n", i);
		clientadd(no);
	}
	int clean;
	printf("�Ƿ���Ҫ�Է��������ɨ��1.��  2.��\n");
	scanf("%d", &clean);
	if (clean == 1)
	{
		char* sql3 = (char*)malloc(100);
		sprintf(sql3, "update room set Rclean = '��' where Rno = '%s'", no);
		if (mysql_query(&mysql, sql3) != 0) {    //����ֵ ��ѯ�ɹ���0
			printf("������ɨ����ʧ��\n");
			exit(1);
		}
		else
		{
			printf("������ɨ���óɹ�\n");
		}
	}
	char* sql2 = (char*)malloc(100);
	sprintf(sql2, "update room set Rstate = '��' where Rno = '%s'", no);
	char* sql4 = (char*)malloc(100);
	sprintf(sql4, "update room_type set Rrest = Rrest-1 where Rtype=(select Rtype from room where Rno = '%s')", no);
	if ((mysql_query(&mysql, sql2) == 0) && (mysql_query(&mysql, sql4) == 0)) 
	{    //����ֵ ��ѯ�ɹ���0
		printf("��ס����ɹ�\n");
		int tmp;
		printf("��0���ز˵�\n");
		scanf("%d", &tmp);
	}
	else
	{
		printf("��ס����ʧ��\n");
		exit(1);
	}
}

void PrintEmpty(int page)
{
	if (page == 1)
	{
		printf("������ÿҳ��ʾ����:");
		scanf("%d", &xianshitiaoshu);
	}
	if (page == -1) {
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room where Rstate='��' limit %d,%d", index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0) {    //����ֵ ��ѯ�ɹ���0
		printf("��ѯʧ��\n");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("�޽��,�����޷��洢�����\n");
		}
		else {
			printf("\t\t\t\t\t��%dҳ\n", page);
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("%s\t%s\t%s\t\n", row[0], row[1], row[2]);
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

	PrintEmpty(cho);
}

void PrintFull(int page)
{
	if (page == 1) {
		printf("������ÿҳ��ʾ����:");
		scanf("%d", &xianshitiaoshu);
	}
	if (page == -1) {
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select client.Rno,Rtype,Rstate,count(Cno),Cday from room,client where room.Rstate='��' and room.Rno = client.Rno group by client.Rno limit %d,%d", index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0) {    //����ֵ ��ѯ�ɹ���0
		printf("��ѯʧ��\n");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("�޽��,�����޷��洢�����");
		}
		else {
			printf("\t\t\t\t\t��%dҳ\n", page);
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("%s\t%s\t%s\t%s\t%s\t\n", row[0], row[1], row[2], row[3], row[4]);
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
	PrintFull(cho);
}

void PrintAllRoom(int page)//��ӡ����ţ��������ͣ���ס��������ס�������Ƿ�Ϊ��
{
	while (1)
	{
		printf("�������ѯ�շ��仹��������: \n");
		printf("1.�շ���\n");
		printf("2.������\n");
		int n;
		scanf("%d", &n);
		if (n == 1)
		{
			printf("1.�շ���:\n");
			PrintEmpty(1);
			break;
		}
		else if (n == 2)
		{
			printf("1.������:\n");
			PrintFull(1);
			break;
		}
		else
		{
			printf("ѡ�������������");
		}
	}
}
void CountAllPerson()//ͳ����������
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select count(Cno) from client");
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);
	printf("��ǰ��ס������%s\n", row[0]);
	mysql_free_result(result);
}

void CountAllRoom()
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select count(Rno) from room");
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);

	printf("/%s\n", row[0]);
	mysql_free_result(result);
}

void CountUnRoomrate()//ͳ��δ��ס��
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select count(Rno) from room where Rstate = '��' ");
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);

	printf("��ǰ�շ�����%s\n", row[0]);
	printf("��ǰδ��ס�ʣ�%s", row[0]);
	CountAllRoom();
}
void CountRoomrate()//ͳ����ס��
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select count(Rno) from room where Rstate = '��' ");
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);

	printf("��ǰ��������%s\n", row[0]);
	printf("��ǰ��ס�ʣ�%s", row[0]);
	CountAllRoom();
}
void PrintHotel()
{
	CountAllPerson();//ͳ����������
	CountUnRoomrate();//ͳ��δ��ס��
	CountRoomrate();//ͳ����ס��
	int tmp;
	printf("��0���ز˵�");
	scanf("%d", &tmp);
}
void RoomClean(int page)
{
	if (page == 1)
	{
		printf("������ÿҳ��ʾ����:");
		scanf("%d", &xianshitiaoshu);
	}
	if (page == -1) {
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room where Rclean='��' limit %d,%d", index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0) {    //����ֵ ��ѯ�ɹ���0
		printf("��ѯʧ��\n");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("�޽��,�����޷��洢�����\n");
		}
		else {
			printf("\t\t\t\t\t��%dҳ\n", page);
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
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
	RoomClean(cho);
}
void Bossmenu()
{
	while (1)
	{
		head();
		printf("\t\t\t*          *                    �ϰ����                     *            *\n");
		printf("\t\t\t*          *               ������Ҫʵ�ֵĹ���                *            *\n");
		printf("\t\t\t*          *                   1.�Ǽ���ס                    *            *\n");
		printf("\t\t\t*          *                   2.�������                    *            *\n");
		printf("\t\t\t*          *                   3.��ѯ�ͷ�                    *            *\n");
		printf("\t\t\t*          *                   4.��ѯ����                    *            *\n");
		printf("\t\t\t*          *                   5.��ӡ�ͷ�                    *            *\n");
		printf("\t\t\t*          *                   6.�ͷ�ͳ��                    *            *\n");
		printf("\t\t\t*          *                     7.�˳�                      *            *\n");
		int n;
		scanf("%d", &n);
		switch (n)
		{
			char no[20];
			char type[20];
		case 1:
			printf("������Ǽ���ס�ķ���ţ�");
			scanf("%s", no);
			CheckRoomByno(no);
			break;
		case 2:
			printf("�����������˵ķ���ţ�");
			scanf("%s", no);
			PayRoom(no);
			break;
		case 3:
			printf("������Ҫ��ѯ�ķ���ţ�");
			scanf("%s", no);
			SelectRoomByno(no);
			break;
		case 4:
			printf("������Ҫ��ѯ�ķ������ͣ�");
			scanf("%s", type);
			SelectRoomByty(type, 1);
			break;
		case 5:
			PrintAllRoom(1);
			break;
		case 6:
			PrintHotel();
			break;
		case 7:
			exit(0);
			break;
		}
		system("cls");
	}
}
void Cleanermenu()
{
	while (1)
	{
		head();
		printf("\t\t\t*          *                    �������                     *            *\n");
		printf("\t\t\t*          *               ������Ҫʵ�ֵĹ���                *            *\n");
		printf("\t\t\t*          *                   1.�Ǽ���ס                    *            *\n");
		printf("\t\t\t*          *                   2.�������                    *            *\n");
		printf("\t\t\t*          *                   3.��ѯ�ͷ�                    *            *\n");
		printf("\t\t\t*          *                   4.��ѯ����                    *            *\n");
		printf("\t\t\t*          *                   5.��ӡ�ͷ�                    *            *\n");
		printf("\t\t\t*          *                   6.��ɨ����                    *            *\n");
		printf("\t\t\t*          *                     7.�˳�                      *            *\n");
		int n;
		int flag;
		scanf("%d", &n);
		switch (n)
		{
			char no[20];
		case 1:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 2:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 3:
			printf("�������ѯ�ķ���ţ�");
			scanf("%s", no);
			SelectRoomByno(no);
			break;
		case 4:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 5:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 6:
			RoomClean(1);
			break;
		case 7:
			exit(0);
			break;
		}
		system("cls");
	}
}
void Moneymenu()
{
	while (1)
	{
		head();
		printf("\t\t\t*          *                    ��̨����                     *            *\n");
		printf("\t\t\t*          *               ������Ҫʵ�ֵĹ���                *            *\n");
		printf("\t\t\t*          *                   1.�Ǽ���ס                    *            *\n");
		printf("\t\t\t*          *                   2.�������                    *            *\n");
		printf("\t\t\t*          *                   3.��ѯ�ͷ�                    *            *\n");
		printf("\t\t\t*          *                   4.��ѯ����                    *            *\n");
		printf("\t\t\t*          *                   5.��ӡ�ͷ�                    *            *\n");
		printf("\t\t\t*          *                   6.�ͷ�ͳ��                    *            *\n");
		printf("\t\t\t*          *                     7.�˳�                      *            *\n");		int n, flag;
		scanf("%d", &n);
		switch (n)
		{
			char no[20];
			char type[20];
		case 1:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 2:
			printf("������Ǽ���ס�ķ���ţ�");
			scanf("%s", no);
			PayRoom(no);
			break;
		case 3:
			printf("�������ѯ�ķ���ţ�");
			scanf("%s", no);
			SelectRoomByno(no);
			break;
		case 4:
			printf("�������ѯ�ķ������ͣ�");
			scanf("%s", type);
			SelectRoomByty(type, 1);
			break;
		case 5:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 6:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 7:
			exit(0);
			break;
		}
		system("cls");
	}
}
void Waitermenu()
{
	while (1)
	{
		head();
		printf("\t\t\t*          *                    ǰ̨����                     *            *\n");
		printf("\t\t\t*          *               ������Ҫʵ�ֵĹ���                *            *\n");
		printf("\t\t\t*          *                   1.�Ǽ���ס                    *            *\n");
		printf("\t\t\t*          *                   2.�������                    *            *\n");
		printf("\t\t\t*          *                   3.��ѯ�ͷ�                    *            *\n");
		printf("\t\t\t*          *                   4.��ѯ����                    *            *\n");
		printf("\t\t\t*          *                   5.��ӡ�ͷ�                    *            *\n");
		printf("\t\t\t*          *                   6.�ͷ�ͳ��                    *            *\n");
		printf("\t\t\t*          *                     7.�˳�                      *            *\n");
		int n, flag;
		scanf("%d", &n);
		switch (n)
		{
			char no[20];
			char type[20];
		case 1:
			printf("������Ǽ���ס�ķ���ţ�");
			scanf("%s", no);
			CheckRoomByno(no);
			break;
		case 2:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 3:
			printf("�������ѯ�ķ���ţ�");
			scanf("%s", no);
			SelectRoomByno(no);
			break;
		case 4:
			printf("�������ѯ�ķ������ͣ�");
			scanf("%s", type);
			SelectRoomByty(type, 1);
			break;
		case 5:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 6:
			printf("�Բ������޴���Ȩ�ޣ�\n");
			printf("����0���ز˵���");
			scanf("%d", &flag);
			break;
		case 7:
			exit(0);
			break;
		}
		system("cls");
	}
}