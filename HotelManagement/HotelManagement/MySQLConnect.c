#include "MySQLConnect.h"

MYSQL mysql, *sock;

const char *host = "127.0.0.1";
const char *user = "root";
const char *pass = "111111";   //�����Լ���������޸�
const char *db = "hotel";    //�����Լ����ݿ�����޸�
const int port = 3306;       //Ĭ�϶˿ں�3306
const char *win_socket = NULL;
const long flag = 0;
void Connect() {
	//����֮ǰ�ĳ�ʼ��
	mysql_init(&mysql);  //ȡ��ַ
	if ((sock = mysql_real_connect(&mysql, host, user, pass, db, port, win_socket, flag)) == NULL) {
		printf("����ʧ��");
		fprintf(stderr, "%s", mysql_error(&mysql));
		exit(1);
	}
	else {
		mysql_query(&mysql, "set names GBK");    //�����ַ����໥ת����������û���⣬�Ž������û����
		//fprintf(stderr, "���ӳɹ�!\n");
	}
}