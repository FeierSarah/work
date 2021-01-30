#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include "C:\Program Files\MySQL\MySQL Server 5.5\include\mysql.h"
#pragma comment(lib,"libmysql.lib")

MYSQL mysql, *sock;
const char* host = "127.0.0.1";
const char* user = "root";
const char* pass = "";
const char* db = "db_test1";
const int port = 3306;
const char* win_socket = NULL;
const long flag = 0;
const char* query;
MYSQL_RES* result;
MYSQL_ROW row;

void conect()
{
	mysql_init(&mysql);
	if ((sock = mysql_real_connect(&mysql, host, user, pass, db, port, win_socket, flag)))
	{
		printf("连接失败\n");
		fprintf(stderr, "%s", mysql_error(&mysql));
		exit(1);
	}
	else
	{
		fprintf(stderr, "连接成功！\n");
	}
}

void selectAll()
{
	query = "select * from emp";
	if (mysql_query(&mysql, query) != 0)
	{
		printf("查询失败\n");
		exit(1);
	}
	else
	{
		if ((result = mysql_store_result(&mysql)) == NULL)
		{
			printf("无结果，或无法存储结果集\n");
			exit(1);
		}
		else
		{
			while ((row = mysql_fetch_row(result)) != NULL)
			{
				printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
			}
		}
	}
}

int main()
{
	conect();
	return 0;
}