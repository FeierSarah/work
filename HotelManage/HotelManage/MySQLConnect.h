#pragma once
#define _CRT_SECURE_NO_WARNINGS //ѹ���ϰ汾C���о���ĺ���
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<WinSock2.h>  //windowsͨ��Э��
#include<Windows.h>
#include "C:\Program Files\MySQL\MySQL Server 5.5\include\mysql.h"
#include<conio.h>
#include<process.h>
#pragma comment(lib,"libmysql.lib")  //mysql�Ķ�̬���ӿ�
#include<WinSock2.h>  //windowsͨ��Э��
#include<Windows.h>


extern const long flag;  //ͨ��Ϊ0

extern MYSQL mysql, *sock;

//��Ҫ����
extern const char *host;
extern const char *user;
extern const char *pass;   //�����Լ���������޸�
extern const char *db;  //�����Լ����ݿ�����޸�
extern const int port;    //Ĭ�϶˿ں�3306
extern const char *win_socket;

void Connect();
//��Ҫ����
