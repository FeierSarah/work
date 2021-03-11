//#define _CRT_SECURE_NO_WARNINGS //压制老版本C的有警告的函数
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//#include<WinSock2.h>  //windows通信协议
//#include<Windows.h>
//#include "C:\Program Files\MySQL\MySQL Server 5.7\include\mysql.h"
//#include<conio.h>
//#include<process.h>
//#pragma comment(lib,"libmysql.lib")  //mysql的动态链接库
//#include<WinSock2.h>  //windows通信协议
//#include<Windows.h>
//
#define false 0
#define true 1
////必要配置
//MYSQL mysql, *sock;
//const char *host = "127.0.0.1";
//const char *user = "root";
//const char *pass = "111111";   //根据自己密码进行修改
//const char *db = "hotel";    //根据自己数据库进行修改
//const int port = 3306;       //默认端口号3306
//const char *win_socket = NULL;
//int xianshitiaoshu;   //分页查询，每页显示的人数
//const long flag = 0;  //通常为0
//const char* query;  //保存查询的语句
//MYSQL_RES* result; //结果集指针
//MYSQL_ROW row;
//必要配置

#include"waiter.h"

//管理员配置
//char *admin = (char*)malloc(100);
//char *adminpassword = (char *)malloc(100);
//管理员配置

int SingleAdminSelect(char Wid[]){
	
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from waiter where Wid = '%s'", Wid);
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	if ((row = mysql_fetch_row(result)) == NULL){   //如果查询到的值为空，则就是在数据库里不存在这个员工，返回false
		printf("信息不存在");
		return false;
	}
	printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
	
	return true;
}

void Adminmenu();
//管理员登录页面

void Admin()
{
	char admin[20];
	char adminpassword[20];

	printf("请输入用户名：");
	scanf("%s", admin);
	printf("请输入密码：");
	scanf("%s", adminpassword);
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from admin where Aid = '%s'", admin);
	if (mysql_query(&mysql, sql) != 0){    //返回值 查询成功是0,包括查询为空
		printf("未完成查询");
		exit(1);
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("无结果,或者无法存储结果集");
		}
		else{
			row = mysql_fetch_row(result);        //结果已经判定不会为空且只有一条，所以直接赋值即可
			if (row == NULL){ 
				printf("用户名错误,返回主界面");
				Sleep(600);
				return; 
			}
			if (strcmp(row[1], adminpassword) == 0){   //密码进行比对是否正确
				printf("登录成功\n");    //然后进入登录界面
				for (int a = 0; a<5; a++)
				{
					printf(".");
					Sleep(600);
				}
				system("cls");                     //清屏
				mysql_free_result(result);        //释放结果集
				//登录界面
				Adminmenu();

				//释放结果集
			}
			else{
				printf("密码错误\n");
				Sleep(600);
			}
		}
	}
}

void AdminSelectAll(int page)
{
	if (page == 1){
		printf("请输入每页显示条数:");
		scanf("%d", &xianshitiaoshu);      //每页显示服务员的个数
	}
	if (page == -1){
		return;
	}
	int index = (page - 1) *xianshitiaoshu;
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from waiter limit %d,%d", index, xianshitiaoshu);
	if (mysql_query(&mysql, sql) != 0){    //返回值 查询成功是0
		printf("查询失败");
		exit(1);
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("无结果,或者无法存储结果集");
		}
		else{
			printf("\t\t\t\t\t第%d页\n", page);
			while ((row = mysql_fetch_row(result)) != NULL){
				printf("%s\t%s\t%s\t%s\t%s\t\n", row[0], row[1], row[2], row[3],row[4]);
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
	AdminSelectAll(cho);
}

//管理员修改数据
void AdminUpdate()
{
	char Wid[20];   //存储ID
	char Wrole[20];    //存储职位
	printf("请输入要修改职位的服务员ID：");
	scanf("%s", Wid);
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from waiter where Wid = '%s'", Wid);
	mysql_query(&mysql, sql);
	result = mysql_store_result(&mysql);
	while ((row = mysql_fetch_row(result)) == NULL){    //返回值 查询成功是0
		printf("无此ID,请重新输入：");
		scanf("%s", Wid);
		sprintf(sql, "select * from waiter where Wid = '%s'", Wid);
		mysql_free_result(result);     //每次执行前先释放结果集
		mysql_query(&mysql, sql);
		result = mysql_store_result(&mysql);
	}
	system("cls");
	printf("查找成功，此ID信息为\n");
	printf("%s\t%s\t%s\t%s\t%s\t\n", row[0], row[1], row[2], row[3],row[4]);
	printf("请输入员工修改后的职位(前台服务员/经理/保洁员/收银员）：");
	int flag = 1;   //更改职位成功则变为0
	while (flag){
		scanf("%s", Wrole);
		if (strcmp(Wrole, "前台服务员") == 0){
			flag = 0;
			sprintf(sql, "update waiter set Wrole = '%s',Wpriority='入住' where Wid = '%s'", Wrole, Wid);
		}
		else if (strcmp(Wrole, "经理") == 0){
			flag = 0;
			sprintf(sql, "update waiter set Wrole = '%s',Wpriority='入住' where Wid = '%s'", Wrole, Wid);
		}
		else if (strcmp(Wrole, "保洁员") == 0){
			flag = 0;
			sprintf(sql, "update waiter set Wrole = '%s',Wpriority='无权限' where Wid = '%s'", Wrole, Wid);
		}
		else if (strcmp(Wrole, "收银员") == 0){
			flag = 0;
			sprintf(sql, "update waiter set Wrole = '%s',Wpriority='结账' where Wid = '%s'", Wrole, Wid);
		}
		else{
			printf("无相应职位,请重新输入\n");
		}
	}
	if (mysql_query(&mysql, sql) != 0){    //返回值 查询成功是0
		printf("修改失败");
		exit(1);
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("成功，影响了%d行", mysql_affected_rows(&mysql));
		}
		else{
			printf("失败");
		}
	}
}

//管理员增加数据
void AdminAdd()
{
	char Wid[20];
	char Wpassword[20];
	char Wrole[20];
	char Wname[20];
	printf("请输入要增加的员工编号，员工姓名，密码，工作职位:\n");
	scanf("%s%s%s%s", Wid, Wname,Wpassword,Wrole);
	char* sql = (char*)malloc(100);
	if (strcmp(Wrole, "前台服务员") == 0){
		sprintf(sql, "insert  into waiter  values('%s','%s','%s','%s','入住')", Wid, Wname, Wpassword, Wrole);
	}
	else if (strcmp(Wrole, "经理") == 0){
		sprintf(sql, "insert  into waiter  values('%s','%s','%s','%s','所有功能')", Wid, Wname, Wpassword, Wrole);
	}
	else if (strcmp(Wrole, "保洁员") == 0){
		sprintf(sql, "insert  into waiter  values('%s','%s','%s','%s','无权限')", Wid, Wname, Wpassword, Wrole);
	}
	else if (strcmp(Wrole, "收银员") == 0){
		sprintf(sql, "insert  into waiter  values('%s','%s','%s','%s','结账')", Wid, Wname, Wpassword, Wrole);
	}

	if (mysql_query(&mysql, sql) != 0){    //返回值 成功是0
		printf("增加失败");
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("成功，影响了%d行\n", mysql_affected_rows(&mysql));
			SingleAdminSelect(Wid);
		}
		else{
			printf("失败");
		}
	}
}

//管理员删除员工数据
void AdminDeleteData()
{
	char* sql2 = (char*)malloc(100);
	char Wid[20];
	printf("要删除的职工号：");
	scanf("%s", Wid);
	while (SingleAdminSelect(Wid) == false){
		printf("请输入正确的员工号: ");
		scanf("%s", Wid);
	}
	query = "delete from waiter where Wid='%s'";
	sprintf(sql2, query, Wid);
	mysql_query(&mysql, sql2);
	printf("\n已删除该员工\n");
}

int Login()
{
	char *admin = (char*)malloc(100);
	char *adminpassword = (char *)malloc(100);
	printf("请输入用户名：");
	scanf("%s", admin);
	printf("请输入密码：");
	scanf("%s", adminpassword);
	char *sql = (char*)malloc(100);
	sprintf(sql, "select * from waiter where Wid = '%s'", admin);
	if (mysql_query(&mysql, sql) != 0){    //返回值 查询成功是0
		printf("用户名不正确");
	}
	else{
		if ((result = mysql_store_result(&mysql)) == NULL){
			printf("无结果,或者无法存储结果集");
		}
		else{
			row = mysql_fetch_row(result);        //结果已经判定不会为空且只有一条，所以直接赋值即可

			if (row == NULL){
				printf("用户名错误,返回主界面");
				Sleep(600);
				return;
			}

			if (strcmp(row[2], adminpassword) == 0){   //密码进行比对是否正确
				printf("登录成功\n");    //然后进入登录界面
				for (int a = 0; a<5; a++)
				{
					printf(".");
					Sleep(600);
				}
				system("cls");                     //清屏
				//mysql_free_result(result);        //释放结果集
				//登录界面
				printf("%s\n", row[3]);
				if (strcmp(row[3], "前台服务员") == 0){
					Waitermenu();
				}
				else if (strcmp(row[3], "经理") == 0){
					Bossmenu();
				}
				else if (strcmp(row[3], "保洁员") == 0){
					Cleanermenu();
				}
				else if (strcmp(row[3], "收银员") == 0){
					Moneymenu();
				}
				else
				{
					printf("身份错误");
				}

				//释放结果集
				mysql_free_result(result);
			}
			else{
				printf("密码错误\n");
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
		printf("\t\t\t*          *            欢迎来到酒店后台管理系统             *            *\n");
		printf("\t\t\t*          *            请选择登录或者注册                   *            *\n");
		printf("\t\t\t*          *            1.后台管理员登录                     *            *\n");
		printf("\t\t\t*          *            2.员工登录                           *            *\n");
		printf("\t\t\t*          *            3.退出                               *            *\n");
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
			printf("输入错误，请重新输入:\n");
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
		printf("\t\t\t*          *                   管理员服务                    *            *\n");
		printf("\t\t\t*          *               请输入要实现的功能                *            *\n");
		printf("\t\t\t*          *               1.查询所有员工信息                *            *\n");
		printf("\t\t\t*          *               2.查询单个员工信息                *            *\n");
		printf("\t\t\t*          *               3.添加员工数据                    *            *\n");
		printf("\t\t\t*          *               4.删除员工数据                    *            *\n");
		printf("\t\t\t*          *               5.修改员工类型                    *            *\n");
		printf("\t\t\t*          *               6.返回欢迎界面                    *            *\n");
		int n;
		scanf("%d", &n);
		switch (n)
		{
		int index;                 //控制在屏幕中显示时间，按-1退出
		case 1:
			
			AdminSelectAll(1);      //查询所有员工信息
			break;
		case 2:
			printf("请输入员工号：");    //查询单个员工信息 
			char Wid[20];
			scanf("%s", Wid);
			SingleAdminSelect(Wid);
			printf("输入任意数退出：");
			scanf("%d", &index);
			break;
		case 3:
			AdminAdd();            //增加员工信息
			printf("输入任意数退出：");
			scanf("%d", &index);
			break;
		case 4:
			AdminDeleteData();    //删除员工信息
			printf("输入任意数退出：");
			scanf("%d", &index);
			break;
		case 5:
			AdminUpdate();    //修改员工信息
			printf("输入任意数退出：");
			scanf("%d", &index);
			break;
		case 6:
			
			flag = 0;        //返回主界面-------------------------------------------------------------------
			break;
		default:
			printf("输入错误，请重新输入:\n");
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

