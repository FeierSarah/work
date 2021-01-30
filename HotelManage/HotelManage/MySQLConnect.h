#pragma once
#define _CRT_SECURE_NO_WARNINGS //压制老版本C的有警告的函数
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<WinSock2.h>  //windows通信协议
#include<Windows.h>
#include "C:\Program Files\MySQL\MySQL Server 5.5\include\mysql.h"
#include<conio.h>
#include<process.h>
#pragma comment(lib,"libmysql.lib")  //mysql的动态链接库
#include<WinSock2.h>  //windows通信协议
#include<Windows.h>


extern const long flag;  //通常为0

extern MYSQL mysql, *sock;

//必要配置
extern const char *host;
extern const char *user;
extern const char *pass;   //根据自己密码进行修改
extern const char *db;  //根据自己数据库进行修改
extern const int port;    //默认端口号3306
extern const char *win_socket;

void Connect();
//必要配置
