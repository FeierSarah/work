#include<iostream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<algorithm> 
#include<vector>

using namespace std;
//��¼֪ʶ����ֲ����
string plant[] = { "õ��", "�ɻ�", "������", "ˮ��", "ƻ����", "�Ͳ�", "����" };
//��¼֪ʶ��ֲ������
string feature[] = { "ҩ��", "��Ƭ��Ҷ", "�����˷۵�", "����Ҷ", "ˮ��", "�д�", "��ʳ��", "Ǿޱ��", "ʮ�ֻ���", "ϲ��", "���ʵ",
//�ַ�������         0          1            2          3         4       5        6        7           8         9       10      
 "�а�ɫ��ĩ", "ľ��", "һƬ��Ҷ", "�����й�Ƥ", "�޾�Ҷ", "�޸�", "˫��Ҷ", "����Ҷ", "����ֲ��","����ֲ��",
//   11          12        13          14           15       16       17        18         19         20   
"����ֲ��", "�ߵ�ֲ��", "�͵�ֲ��", "õ��", "�ɻ�", "������", "ˮ��", "ƻ����", "�Ͳ�", "����" };
//  21          22          23        24      25       26        27       28      29      30

//��Ź���Ľṹ�� 
typedef struct 
{  
	int relation[6];   //��ϵ 
	int name;		   //������  
}Rule;

 // ��ſ��ܵĶ��� 
typedef struct
{
	int plant;         // name 
	double confidence; //���Ŷ� = ����������� / ����������;
	int site;          // ��rule�е�λ��
	int num;           // ����������� 
	int size;          // ��animal�������������� 
}Result;

vector<Result> result;
// �����   
//�������ʱ�������-1����������� 
Rule rule[17] = 
{ { { 14, -1 }, 19 }, { { 19, 3, -1 }, 7 }, { { 17, 2, -1 },  8}, { { 13, -1 }, 18 }, { { 14, -1 }, 19 },
{ { 15, 16, -1 }, 21 }, { { 1, -1 }, 17 }, { { 21, -1 }, 20 }, { { 21, -1 }, 23 }, { { 19, -1 }, 22 },
{ { 7, 5, -1 }, 24 }, { { 17, 4, 10, 6, -1 }, 25 }, { { 17, 5, 9, -1 }, 26 }, { { 23, 0, 4, -1 }, 27 }, { { 7, 10, 6, 12, -1 }, 28 },
{ { 8, 6, -1 }, 29 }, { { 23, 6, 4, -1 }, 30 } };

int flag[23] = { 0 };  //��Ǹ��������Ƿ�ѡ��

int IsPlant(int a);
int change_speices();  //�����������ֲ����Ĺ������ 
int fnum();            //��ȡflag��ǵ���Ŀ 
int z_inference();     //�������� 
int category();        //���������� 
void cal_confi();      //�������Ŷ� 
void r_inference();    //�������� 
void input();          //���� 
void menu();           //�˵� 

//�ж����Ŷȴ�С
bool Compare(const Result& a, const Result& b)
{
	return a.confidence > b.confidence;
}

//���򲢷���������
void Rsort(vector<Result>& r)
{
	//��������������������
	sort(r.begin(), r.end(), Compare);
	return;
}

//ѡ�������˵� 
void menu()
{
	//���֪ʶ�������������ֲ�����ĳ�Ա��ÿ���4������
	for (int i = 0; i < sizeof(feature) - sizeof(plant); i++)
	{
		if (i % 4 == 0 && i != 0)
			cout << endl;
		cout << setiosflags(ios::left) << setw(3) << i << ".";
		cout << setiosflags(ios::left) << setw(15) << feature[i];
	}
	memset(flag, 0, sizeof(flag));
}
//��������ֵ  ѡ������ 
void input()
{
	for (int i = 0; i < 24; i++)
		flag[i] = 0;
	int  ti = 0;
	cout << endl << "input selection(end -1):";
	while (ti != -1)
	{
		cin >> ti;
		if (ti >= 0 && ti <= 23)
			flag[ti] = 1;
		else if (ti != -1)
		{
			cout << "Input error! Please enter a number between 0~23!" << endl;  //notanimal=25
			cin.clear();		//��������������
			cin.sync(); 		//������뻺����
			cout << "Please continue to enter: ";
		}
	}
}
//��ĳ���� ������ĳ������ 
int IsPlant(int a)
{
	if (a >= 24 && a <= 30)
		return 1;
	return 0;
}
// �ж��Ƿ�ĳһ������ 
int IsPlant_speices(int a)
{
	if (a >= 20 && a <= 23)
		return 1;
	return 0;
}
// ����flag�����б�ǵ����� 
int fnum()
{
	int fum = 0;
	for (int i = 0; i < 24; i++)
	if (flag[i] == 1)
		fum++;
	return fum;
}
//�����ӡ�������
int category()
{
	bool k;
	int count = 0;
	for (int i = 20; i < 24; i++)
	{
		k = false;
		if (flag[i] == 1)
		{
			k = true;
			count++;
			if (count == 1)
				cout << "Can't reason about specific animals! Category is ";
			cout << setiosflags(ios::left) << setw(10) << feature[i];
		}
	}
	cout << endl;
	if (!k)
		cout << "Sorry! No such animal in the system" << endl;
	return 1;
}

// change_speices --�� flag �����仯  �����Ƿ��� �������� �����õ�����ʵ ���
//�� ��ë --�����鶯��  �ͽ�flag�в��鶯�������һ ������ë��һ����flag��0
int change_speices()
{
	int i, j, ti;
	bool t;
	int temp[23] = { 0 }; //��ʱ 
	int f[23] = { 0 }; // ���ʹ�ù���flag[] &  < 20  20 ������ 
	for (i = 0; i < 8; i++)
	{ // rule ǰ8�� ���� 
		t = true;
		j = 0;
		ti = rule[i].relation[j];
		while (ti != -1)
		{
			if (flag[ti] == 1) temp[ti] = 1;
			else 
			{
				memset(temp, 0, sizeof(temp));
				t = false;
				break;
			}
			j++;
			ti = rule[i].relation[j];
		}
		if (t)
		{
			for (int k = 0; k <= 20; k++)
			if (temp[k] == 1)
				f[k] = 1;
			flag[rule[i].name] = 1;
		}
		memset(temp, 0, sizeof(temp));
	}
	// ���������ʵ  ��ɾ��  ������� 
	for (i = 0; i <= 20; i++)
	if (f[i] == 1)
		flag[i] = 0;
	return 1;
}
// ���¼������Ŷ� 
void cal_confi()
{
	for (int i = 0; i < result.size(); i++)
	{
		for (int j = 8; j < 15; j++)
		{
			if (result[i].plant == rule[j].name)
			{
				result[i].confidence = 1.0 * result[i].num / result[i].size;
				break;
			}
		}
	}
}

//����  ˫������ -- ����������ȥ ��ʵ���� ������������ 
int z_inference()
{
	int ti, num;
	int i, j;
	int fum = fnum();
	cout << endl;
	for (i = 8; i < 15; i++)
	{  //������� 
		Result temp;
		j = 0; num = 0;
		ti = rule[i].relation[j];
		while (ti != -1)
		{
			if (flag[ti] == 1) num++;
			j++;
			ti = rule[i].relation[j];
		}
		// ��ʱ j  ������rule[i]�����е������� 
		if (num != 0 && fum <= j)
		{  //  ����������С�ڵ��ڵ���� ����flag�����б��λ��Ŀ���ڴ˶�����������򲻷���result�� 
			if (IsPlant(rule[i].name))
			{ // �Ǿ���Ķ��� 
				temp.plant = rule[i].name;
				int size = j; // rule[i]�����е�������
				temp.size = size;
				temp.confidence = 1.0 * num / size;
				temp.site = i;
				temp.num = num;
				result.push_back(temp);
			}
		}
	}

	if (!result.empty())
		Rsort(result);  //�����ŶȴӸߵ������� 

	/*
	//��ӡ������vector
	for(vector<Result>::iterator it = result.begin();it != result.end();++it){
	cout<<setiosflags(ios::left)<<setw(10)<<feature[(*it).animal]<<" ";
	cout<<(*it).confidence<<" ";
	}
	cout<<endl;
	*/
	// �ж� -- δѯ�� --�������� �� 
	if (result.empty()) 
	{ // �����������޷����κ�һ��������  ����û�����ֶ���  ������һ�ֶ������ (ϵͳ���޴˶����������  
		category();
	}
	else if (result.front().confidence == 1.0)
	{ // ���ܸ��������պ������  ����������û���� 
		cout << "This animal is " << feature[result.front().plant] << endl;
		result.clear(); // ���  
		return 1;
	}
	else // ����������ȫ  ��������  ѯ������ 
		r_inference();
}
//������������  ���뷴������ 
void r_inference()
{
	vector<Result>::iterator it = result.begin();
	int enquire[23];  // �������ѯ�ʹ����������� 0 N  1 Y 2 D��0 ����û�д����� 1 ������  2 �����������֪���� 
	memset(enquire, -1, sizeof(enquire));

	for (int i = 0; i< result.size();)
	{// �����Ŷ���߿�ʼѯ��
		bool in_i = true; // i ++ �ı�� 
		int  nu = result[i].size;
		for (int j = 0; j < nu; j++)
		{  // ѯ�� δ˵�� ���� 
			if (flag[rule[result[i].site].relation[j]] == 0)
			{
				int en = rule[result[i].site].relation[j];
				char c;
				if (enquire[en] == -1)
				{ // ������δ��ѯ�ʹ� �����ѯ����� ����ֱ���жϴ��� 
					cout << "Does this animal have this characteristic?" << feature[rule[result[i].site].relation[j]] << endl;
					cout << "Y(y) or N(n) or D(don't know) : ";
					cin >> c;
					while (c != 'Y' && c != 'y' && c != 'N' && c != 'n' && c != 'D' && c != 'd')
					{
						cout << "Please enter Y(y) or N(n) or D(d)!" << endl;
						cin >> c;
					}
				}
				if (enquire[en] == 1 || c == 'Y' || c == 'y')
				{ //�д�����  �ı����Ŷ�
					result[i].num++;
					enquire[en] = 1;
				}
				else if (enquire[en] == 0 || c == 'N' || c == 'n')
				{ // û�д�����  ֱ��ȥ��
					enquire[en] = 0;
					result.erase(it + i);  // eraseɾ���� i������  ����ɾ������Ԫ�أ�����������ָ��ɾ��֮ǰԪ�غ�ĵ�һ��Ԫ�أ�
					in_i = false;  // ��� ������Ԫ�� �� i������ 
					if (result.empty()) //  result Ϊ�� ������ �˳� 
						category();
					break;
				}
				else if (enquire[en] == 2 || c == 'D' || c == 'd')
				{
					enquire[en] = 2; 
				}  // ��ȷ������֪��  ���ŶȲ��ı� 	
			}
		}
		if (in_i)
			++i;
	}

	if (!result.empty())
	{
		// �ı����Ŷ� 
		cal_confi();
		if (result.size() > 1) //��������
			Rsort(result);

		//�ж� -- ѯ�ʺ�  -- ˫������� 
		if (result.front().confidence == 1.0)
		{
			cout << "This plant is " << feature[result.front().plant] << endl;
		}
		else
		{
			cout << "Possible animals (confidence from big to small) :";
			for (vector<Result>::iterator it = result.begin(); it != result.end(); ++it)
				cout << setiosflags(ios::left) << setw(10) << feature[(*it).plant] << " ";
			cout << endl;
		}
		result.clear(); // ��� 
	}
}
int main()
{
	char q;
	cin >> q;
	while (q != 'N' && q != 'n')
	{
		menu();
		input();
		change_speices();
		z_inference();
		cout << "\n������(Y/N)" << endl;
		cin >> q;
		system("cls");
	}
	return 0;
}