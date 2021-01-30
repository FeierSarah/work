#pragma once
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
extern int xianshitiaoshu;   //分页查询，每页显示的人数
extern const char* query;  //保存查询的语句
extern MYSQL_RES* result; //结果集指针
extern MYSQL_ROW row;
extern MYSQL mysql, *sock;

void SelectFullRoomByno(char* no);
extern void SelectRoomByno(char* no);
extern void PayRoom(char* no);
extern void SelectRoomByty(char* type, int page);
extern void CheckRoomByno(char* no);
extern void PrintFull(int page);
extern void PrintEmpty(int page);
extern void PrintAllRoom(int page);
extern void CountAllPerson();
extern void CountUnRoomrate();
extern void CountRoomrate();
extern void CountAllRoom();
extern void PrintHotel();
extern void RoomClean(int page);
extern void Bossmenu();
extern void Cleanermenu();
extern void Waitermenu();
extern void Moneymenu();
extern void clientdelete(char* no);
#pragma once
