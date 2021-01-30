#include "waiter.h"

MYSQL_RES* result; //结果集指针
MYSQL_ROW row;
int xianshitiaoshu;
const char* query;

void SelectFullRoomByno(char* no)
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room,client where room.Rno = '%s' and room.Rno = client.Rno", no);
	if (mysql_query(&mysql, sql) != 0)
	{
		printf("该房间无入住信息\n");
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
	{    //返回值 查询成功是0
		printf("查询失败\n");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL)
		{
			printf("查询不到该客房\n");
		}
		else
		{
			row = mysql_fetch_row(result);
			if (strcmp(row[2], "空") == 0)
			{
				mysql_free_result(result);
				printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
				printf("按0返回菜单");
				int tmp;
				scanf("%d", &tmp);
				return;
			}
			else if (strcmp(row[2], "满") == 0)
			{
				mysql_free_result(result);
				SelectFullRoomByno(no);
				printf("按0返回菜单");
				int tmp;
				scanf("%d", &tmp);
				return;
			}
		}
	}
	//释放结果集

	
}
void PayRoom(char* no)
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select Cday*Rprice from client,room_type where client.Rno = '%s' and room_type.Rtype =(select Rtype from room where Rno='%s');", no, no);
	if (mysql_query(&mysql, sql) != 0)
	{    //返回值 查询成功是0
		printf("查询失败\n");
		exit(1);
	}
	else 
	{
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("该房间未入住顾客\n");
		}
		else 
		{
			row = mysql_fetch_row(result);
			printf("请支付%s房费\n", row[0]);
		}
	}
	//释放结果集
	mysql_free_result(result);

	char* sql3 = (char*)malloc(100);
	sprintf(sql3, "update room set Rclean = '否' where Rno = '%s'", no);
	mysql_query(&mysql, sql3);

	char* sql4 = (char*)malloc(100);
	sprintf(sql4, "update room_type set Rrest = Rrest+1 where Rtype=(select Rtype from room where Rno = '%s')", no);
	mysql_query(&mysql, sql4);

	char* sql5 = (char*)malloc(100);
	sprintf(sql5, "update room set Rstate = '空' where Rno = '%s'", no);
	mysql_query(&mysql, sql5);

	clientdelete(no);
	int tmp;
	printf("按0返回菜单\n");
	scanf("%d", &tmp);
}
void SelectRoomByty(char* type, int page)
{
	if (page == 1) {
		printf("请输入每页显示条数:");
		scanf("%d", &xianshitiaoshu);      //每页显示服务员的个数
	}
	if (page == -1) {
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room where Rtype='%s' and Rstate='空' limit %d,%d", type, index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0) {    //返回值 查询成功是0
		printf("查询失败");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("无结果,或者无法存储结果集");
		}
		else {
			printf("\t\t\t\t\t第%d页\n", page);
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("%s\t%s\n", row[0], row[1]);
			}
		}
	}
	//释放结果集
	mysql_free_result(result);
	printf("下一页（输入-1退出)");
	int cho;  //输入进来的页码
	printf("请选择:");
	scanf("%d", &cho);
	system("cls");
	SelectRoomByty(type, cho);
}

void clientdelete(char* no)
{
	char* sql2 = (char*)malloc(100);
	query = "delete from client where Rno='%s'";
	sprintf(sql2, query, no);

	if (mysql_query(&mysql, sql2) != 0) {    //返回值 查询成功是0
		printf("删除失败\n");
		exit(1);
	}
	else 
	{
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("客户信息删除成功，影响了%d行\n", mysql_affected_rows(&mysql));
		}
		else
		{
			printf("客户信息删除失败\n");
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
	printf("请输入要增加的住户姓名，身份证号，住户电话，入住天数，入住时间，搬离时间:\n");
	scanf("%s%s%s%d%s%s", Cname, Cno, Ctele, &Cday, Cin, Cout);
	char* sql2 = (char*)malloc(100);
	sprintf(sql2, "insert into client values('%s','%s','%s','%s','%d','%s','%s')", no, Cname, Cno, Ctele, Cday, Cin, Cout);

	if (mysql_query(&mysql, sql2) != 0)
	{    //返回值 查询成功是0
		printf("顾客信息录入失败");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL)
		{
			printf("顾客信息录入成功，影响了%d行\n", mysql_affected_rows(&mysql));
		}
		else
		{
			printf("顾客信息录入失败\n");
		}
	}
}

void CheckRoomByno(char* no)
{
	int n;
	
	printf("请输入入住人数：");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		printf("请输入第%d个住户信息：\n", i);
		clientadd(no);
	}
	int clean;
	printf("是否需要对房间进行清扫：1.是  2.否\n");
	scanf("%d", &clean);
	if (clean == 1)
	{
		char* sql3 = (char*)malloc(100);
		sprintf(sql3, "update room set Rclean = '是' where Rno = '%s'", no);
		if (mysql_query(&mysql, sql3) != 0) {    //返回值 查询成功是0
			printf("房间清扫设置失败\n");
			exit(1);
		}
		else
		{
			printf("房间清扫设置成功\n");
		}
	}
	char* sql2 = (char*)malloc(100);
	sprintf(sql2, "update room set Rstate = '满' where Rno = '%s'", no);
	char* sql4 = (char*)malloc(100);
	sprintf(sql4, "update room_type set Rrest = Rrest-1 where Rtype=(select Rtype from room where Rno = '%s')", no);
	if ((mysql_query(&mysql, sql2) == 0) && (mysql_query(&mysql, sql4) == 0)) 
	{    //返回值 查询成功是0
		printf("入住办理成功\n");
		int tmp;
		printf("按0返回菜单\n");
		scanf("%d", &tmp);
	}
	else
	{
		printf("入住办理失败\n");
		exit(1);
	}
}

void PrintEmpty(int page)
{
	if (page == 1)
	{
		printf("请输入每页显示条数:");
		scanf("%d", &xianshitiaoshu);
	}
	if (page == -1) {
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room where Rstate='空' limit %d,%d", index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0) {    //返回值 查询成功是0
		printf("查询失败\n");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("无结果,或者无法存储结果集\n");
		}
		else {
			printf("\t\t\t\t\t第%d页\n", page);
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("%s\t%s\t%s\t\n", row[0], row[1], row[2]);
			}
		}
	}
	//释放结果集
	mysql_free_result(result);
	printf("下一页（输入-1退出)");
	int cho;  //输入进来的页码
	printf("请选择:");
	scanf("%d", &cho);
	system("cls");

	PrintEmpty(cho);
}

void PrintFull(int page)
{
	if (page == 1) {
		printf("请输入每页显示条数:");
		scanf("%d", &xianshitiaoshu);
	}
	if (page == -1) {
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select client.Rno,Rtype,Rstate,count(Cno),Cday from room,client where room.Rstate='满' and room.Rno = client.Rno group by client.Rno limit %d,%d", index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0) {    //返回值 查询成功是0
		printf("查询失败\n");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("无结果,或者无法存储结果集");
		}
		else {
			printf("\t\t\t\t\t第%d页\n", page);
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("%s\t%s\t%s\t%s\t%s\t\n", row[0], row[1], row[2], row[3], row[4]);
			}
		}
	}
	//释放结果集
	mysql_free_result(result);
	printf("下一页（输入-1退出)");
	int cho;  //输入进来的页码
	printf("请选择:");
	scanf("%d", &cho);
	system("cls");
	PrintFull(cho);
}

void PrintAllRoom(int page)//打印房间号，房间类型，入住人数，入住天数，是否为空
{
	while (1)
	{
		printf("请输入查询空房间还是满房间: \n");
		printf("1.空房间\n");
		printf("2.满房间\n");
		int n;
		scanf("%d", &n);
		if (n == 1)
		{
			printf("1.空房间:\n");
			PrintEmpty(1);
			break;
		}
		else if (n == 2)
		{
			printf("1.满房间:\n");
			PrintFull(1);
			break;
		}
		else
		{
			printf("选择错误，重新输入");
		}
	}
}
void CountAllPerson()//统计所有人数
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select count(Cno) from client");
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);
	printf("当前入住人数：%s\n", row[0]);
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

void CountUnRoomrate()//统计未入住率
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select count(Rno) from room where Rstate = '空' ");
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);

	printf("当前空房数：%s\n", row[0]);
	printf("当前未入住率：%s", row[0]);
	CountAllRoom();
}
void CountRoomrate()//统计入住率
{
	char *sql = (char*)malloc(100);
	sprintf(sql, "select count(Rno) from room where Rstate = '满' ");
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);

	printf("当前满房数：%s\n", row[0]);
	printf("当前入住率：%s", row[0]);
	CountAllRoom();
}
void PrintHotel()
{
	CountAllPerson();//统计所有人数
	CountUnRoomrate();//统计未入住率
	CountRoomrate();//统计入住率
	int tmp;
	printf("按0返回菜单");
	scanf("%d", &tmp);
}
void RoomClean(int page)
{
	if (page == 1)
	{
		printf("请输入每页显示条数:");
		scanf("%d", &xianshitiaoshu);
	}
	if (page == -1) {
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from room where Rclean='是' limit %d,%d", index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0) {    //返回值 查询成功是0
		printf("查询失败\n");
		exit(1);
	}
	else {
		if ((result = mysql_store_result(&mysql)) == NULL) {
			printf("无结果,或者无法存储结果集\n");
		}
		else {
			printf("\t\t\t\t\t第%d页\n", page);
			while ((row = mysql_fetch_row(result)) != NULL) {
				printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
			}
		}
	}
	//释放结果集
	mysql_free_result(result);
	printf("下一页（输入-1退出)");
	int cho;  //输入进来的页码
	printf("请选择:");
	scanf("%d", &cho);
	system("cls");
	RoomClean(cho);
}
void Bossmenu()
{
	while (1)
	{
		head();
		printf("\t\t\t*          *                    老板服务                     *            *\n");
		printf("\t\t\t*          *               请输入要实现的功能                *            *\n");
		printf("\t\t\t*          *                   1.登记入住                    *            *\n");
		printf("\t\t\t*          *                   2.办理结账                    *            *\n");
		printf("\t\t\t*          *                   3.查询客房                    *            *\n");
		printf("\t\t\t*          *                   4.查询类型                    *            *\n");
		printf("\t\t\t*          *                   5.打印客房                    *            *\n");
		printf("\t\t\t*          *                   6.客房统计                    *            *\n");
		printf("\t\t\t*          *                     7.退出                      *            *\n");
		int n;
		scanf("%d", &n);
		switch (n)
		{
			char no[20];
			char type[20];
		case 1:
			printf("请输入登记入住的房间号：");
			scanf("%s", no);
			CheckRoomByno(no);
			break;
		case 2:
			printf("请输入办理结账的房间号：");
			scanf("%s", no);
			PayRoom(no);
			break;
		case 3:
			printf("请输入要查询的房间号：");
			scanf("%s", no);
			SelectRoomByno(no);
			break;
		case 4:
			printf("请输入要查询的房间类型：");
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
		printf("\t\t\t*          *                    保洁服务                     *            *\n");
		printf("\t\t\t*          *               请输入要实现的功能                *            *\n");
		printf("\t\t\t*          *                   1.登记入住                    *            *\n");
		printf("\t\t\t*          *                   2.办理结账                    *            *\n");
		printf("\t\t\t*          *                   3.查询客房                    *            *\n");
		printf("\t\t\t*          *                   4.查询类型                    *            *\n");
		printf("\t\t\t*          *                   5.打印客房                    *            *\n");
		printf("\t\t\t*          *                   6.清扫房间                    *            *\n");
		printf("\t\t\t*          *                     7.退出                      *            *\n");
		int n;
		int flag;
		scanf("%d", &n);
		switch (n)
		{
			char no[20];
		case 1:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
			scanf("%d", &flag);
			break;
		case 2:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
			scanf("%d", &flag);
			break;
		case 3:
			printf("请输入查询的房间号：");
			scanf("%s", no);
			SelectRoomByno(no);
			break;
		case 4:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
			scanf("%d", &flag);
			break;
		case 5:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
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
		printf("\t\t\t*          *                    柜台服务                     *            *\n");
		printf("\t\t\t*          *               请输入要实现的功能                *            *\n");
		printf("\t\t\t*          *                   1.登记入住                    *            *\n");
		printf("\t\t\t*          *                   2.办理结账                    *            *\n");
		printf("\t\t\t*          *                   3.查询客房                    *            *\n");
		printf("\t\t\t*          *                   4.查询类型                    *            *\n");
		printf("\t\t\t*          *                   5.打印客房                    *            *\n");
		printf("\t\t\t*          *                   6.客房统计                    *            *\n");
		printf("\t\t\t*          *                     7.退出                      *            *\n");		int n, flag;
		scanf("%d", &n);
		switch (n)
		{
			char no[20];
			char type[20];
		case 1:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
			scanf("%d", &flag);
			break;
		case 2:
			printf("请输入登记入住的房间号：");
			scanf("%s", no);
			PayRoom(no);
			break;
		case 3:
			printf("请输入查询的房间号：");
			scanf("%s", no);
			SelectRoomByno(no);
			break;
		case 4:
			printf("请输入查询的房间类型：");
			scanf("%s", type);
			SelectRoomByty(type, 1);
			break;
		case 5:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
			scanf("%d", &flag);
			break;
		case 6:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
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
		printf("\t\t\t*          *                    前台服务                     *            *\n");
		printf("\t\t\t*          *               请输入要实现的功能                *            *\n");
		printf("\t\t\t*          *                   1.登记入住                    *            *\n");
		printf("\t\t\t*          *                   2.办理结账                    *            *\n");
		printf("\t\t\t*          *                   3.查询客房                    *            *\n");
		printf("\t\t\t*          *                   4.查询类型                    *            *\n");
		printf("\t\t\t*          *                   5.打印客房                    *            *\n");
		printf("\t\t\t*          *                   6.客房统计                    *            *\n");
		printf("\t\t\t*          *                     7.退出                      *            *\n");
		int n, flag;
		scanf("%d", &n);
		switch (n)
		{
			char no[20];
			char type[20];
		case 1:
			printf("请输入登记入住的房间号：");
			scanf("%s", no);
			CheckRoomByno(no);
			break;
		case 2:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
			scanf("%d", &flag);
			break;
		case 3:
			printf("请输入查询的房间号：");
			scanf("%s", no);
			SelectRoomByno(no);
			break;
		case 4:
			printf("请输入查询的房间类型：");
			scanf("%s", type);
			SelectRoomByty(type, 1);
			break;
		case 5:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
			scanf("%d", &flag);
			break;
		case 6:
			printf("对不起，您无此项权限！\n");
			printf("输入0返回菜单：");
			scanf("%d", &flag);
			break;
		case 7:
			exit(0);
			break;
		}
		system("cls");
	}
}