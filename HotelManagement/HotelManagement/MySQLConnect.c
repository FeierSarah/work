#include "MySQLConnect.h"

MYSQL mysql, *sock;

const char *host = "127.0.0.1";
const char *user = "root";
const char *pass = "111111";   //根据自己密码进行修改
const char *db = "hotel";    //根据自己数据库进行修改
const int port = 3306;       //默认端口号3306
const char *win_socket = NULL;
const long flag = 0;
void Connect() {
	//连接之前的初始化
	mysql_init(&mysql);  //取地址
	if ((sock = mysql_real_connect(&mysql, host, user, pass, db, port, win_socket, flag)) == NULL) {
		printf("连接失败");
		fprintf(stderr, "%s", mysql_error(&mysql));
		exit(1);
	}
	else {
		mysql_query(&mysql, "set names GBK");    //两个字符码相互转化，读出来没问题，放进里面就没问题
		//fprintf(stderr, "连接成功!\n");
	}
}