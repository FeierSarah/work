#pragma once
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
extern int xianshitiaoshu;   //��ҳ��ѯ��ÿҳ��ʾ������
extern const char* query;  //�����ѯ�����
extern MYSQL_RES* result; //�����ָ��
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
