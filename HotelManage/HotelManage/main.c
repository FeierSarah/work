#include"waiter.h"


int head()							//进入管理系统 
{
	printf("\t\t\t===========================================================================\n");
	printf("\t\t\t*             *                                          *                *\n");
	printf("\t\t\t*          *             欢迎使用酒店客房管理系统            *            *\n");
	printf("\t\t\t*        *                                                      *         *\n");
	printf("\t\t\t*     *                                                            *      *\n");
	printf("\t\t\t*     *                                                            *      *\n");
	printf("\t\t\t*        *                                                      *         *\n");
	printf("\t\t\t*            *                                              *             *\n");
	printf("\t\t\t*                 *            七匹狼开发             *                   *\n");
	printf("\t\t\t*                        *                     *                          *\n");
	printf("\t\t\t*                               *        *                                *\n");
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t===========================================================================\n");
	printf("请按回车键进入界面");
	getchar();
	printf("正在进入系统选项");
	for (int a = 0; a < 5; a++)
	{
		printf(".");
		Sleep(200);
	}
	printf("\n");

	return 0;
}

//管理员登录页面
//void Admin()
//{
//	管理员配置
//	char *admin = (char*)malloc(100);
//	char *adminpassword = (char *)malloc(100);
//	printf("请输入用户名：");
//	scanf("%s", admin);
//	printf("请输入密码：");
//	scanf("%s", adminpassword);
//	char *sql = (char*)malloc(100);
//	sprintf(sql, "select * from admin where Aid = '%s'", admin);
//	if (mysql_query(&mysql, sql) != 0) {    //返回值 查询成功是0
//		printf("用户名不正确");
//	}
//	else {
//		if ((result = mysql_store_result(&mysql)) == NULL) {
//			printf("无结果,或者无法存储结果集");
//		}
//		else {
//			row = mysql_fetch_row(result);        //结果已经判定不会为空且只有一条，所以直接赋值即可
//			if (strcmp(row[1], adminpassword) == 0) {   //密码进行比对是否正确
//				printf("登录成功\n");    //然后进入登录界面
//				for (int a = 0; a < 5; a++)
//				{
//					printf(".");
//					Sleep(600);
//				}
//				system("cls");                     //清屏
//				mysql_free_result(result);        //释放结果集
//												 登录界面
//
//
//												释放结果集
//			}
//			else {
//				printf("密码错误\n");
//				head();
//			}
//		}
//	}
//}

int main() {
	system("color bc");
	Connect();
	Bossmenu();
	//Cleanermenu();
	return 0;
}