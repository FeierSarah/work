#include"waiter.h"


int head()							//�������ϵͳ 
{
	printf("\t\t\t===========================================================================\n");
	printf("\t\t\t*             *                                          *                *\n");
	printf("\t\t\t*          *             ��ӭʹ�þƵ�ͷ�����ϵͳ            *            *\n");
	printf("\t\t\t*        *                                                      *         *\n");
	printf("\t\t\t*     *                                                            *      *\n");
	printf("\t\t\t*     *                                                            *      *\n");
	printf("\t\t\t*        *                                                      *         *\n");
	printf("\t\t\t*            *                                              *             *\n");
	printf("\t\t\t*                 *            ��ƥ�ǿ���             *                   *\n");
	printf("\t\t\t*                        *                     *                          *\n");
	printf("\t\t\t*                               *        *                                *\n");
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t*                                                                         *\n");
	printf("\t\t\t===========================================================================\n");
	printf("�밴�س����������");
	getchar();
	printf("���ڽ���ϵͳѡ��");
	for (int a = 0; a < 5; a++)
	{
		printf(".");
		Sleep(200);
	}
	printf("\n");

	return 0;
}

//����Ա��¼ҳ��
//void Admin()
//{
//	����Ա����
//	char *admin = (char*)malloc(100);
//	char *adminpassword = (char *)malloc(100);
//	printf("�������û�����");
//	scanf("%s", admin);
//	printf("���������룺");
//	scanf("%s", adminpassword);
//	char *sql = (char*)malloc(100);
//	sprintf(sql, "select * from admin where Aid = '%s'", admin);
//	if (mysql_query(&mysql, sql) != 0) {    //����ֵ ��ѯ�ɹ���0
//		printf("�û�������ȷ");
//	}
//	else {
//		if ((result = mysql_store_result(&mysql)) == NULL) {
//			printf("�޽��,�����޷��洢�����");
//		}
//		else {
//			row = mysql_fetch_row(result);        //����Ѿ��ж�����Ϊ����ֻ��һ��������ֱ�Ӹ�ֵ����
//			if (strcmp(row[1], adminpassword) == 0) {   //������бȶ��Ƿ���ȷ
//				printf("��¼�ɹ�\n");    //Ȼ������¼����
//				for (int a = 0; a < 5; a++)
//				{
//					printf(".");
//					Sleep(600);
//				}
//				system("cls");                     //����
//				mysql_free_result(result);        //�ͷŽ����
//												 ��¼����
//
//
//												�ͷŽ����
//			}
//			else {
//				printf("�������\n");
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