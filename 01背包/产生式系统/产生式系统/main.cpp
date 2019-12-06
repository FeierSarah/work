#include<iostream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<algorithm> 
#include<vector>

using namespace std;
//记录知识库内植物名
string plant[] = { "玫瑰", "荷花", "仙人球", "水棉", "苹果树", "油菜", "海带" };
//记录知识库植物特征
string feature[] = { "药用", "两片子叶", "吸引菜粉蝶", "有托叶", "水生", "有刺", "可食用", "蔷薇科", "十字花科", "喜阳", "结果实",
//字符数组标号         0          1            2          3         4       5        6        7           8         9       10      
 "有白色粉末", "木本", "一片子叶", "种子有果皮", "无茎叶", "无根", "双子叶", "单子叶", "被子植物","孢子植物",
//   11          12        13          14           15       16       17        18         19         20   
"藻类植物", "高等植物", "低等植物", "玫瑰", "荷花", "仙人球", "水棉", "苹果树", "油菜", "海带" };
//  21          22          23        24      25       26        27       28      29      30

//存放规则的结构体 
typedef struct 
{  
	int relation[6];   //关系 
	int name;		   //推理结果  
}Rule;

 // 存放可能的动物 
typedef struct
{
	int plant;         // name 
	double confidence; //置信度 = 满足的特性数 / 所含特征数;
	int site;          // 在rule中的位置
	int num;           // 满足的特征数 
	int size;          // 此animal的所含总特征数 
}Result;

vector<Result> result;
// 规则库   
//输入规则时最后输入-1则代表规则结束 
Rule rule[17] = 
{ { { 14, -1 }, 19 }, { { 19, 3, -1 }, 7 }, { { 17, 2, -1 },  8}, { { 13, -1 }, 18 }, { { 14, -1 }, 19 },
{ { 15, 16, -1 }, 21 }, { { 1, -1 }, 17 }, { { 21, -1 }, 20 }, { { 21, -1 }, 23 }, { { 19, -1 }, 22 },
{ { 7, 5, -1 }, 24 }, { { 17, 4, 10, 6, -1 }, 25 }, { { 17, 5, 9, -1 }, 26 }, { { 23, 0, 4, -1 }, 27 }, { { 7, 10, 6, 12, -1 }, 28 },
{ { 8, 6, -1 }, 29 }, { { 23, 6, 4, -1 }, 30 } };

int flag[23] = { 0 };  //标记各个特征是否选择

int IsPlant(int a);
int change_speices();  //将可以推理出植物类的规则进行 
int fnum();            //获取flag标记的数目 
int z_inference();     //正向推理 
int category();        //输出动物类别 
void cal_confi();      //计算置信度 
void r_inference();    //反向推理 
void input();          //输入 
void menu();           //菜单 

//判断置信度大小
bool Compare(const Result& a, const Result& b)
{
	return a.confidence > b.confidence;
}

//排序并返回排序结果
void Rsort(vector<Result>& r)
{
	//调用数组容器的排序函数
	sort(r.begin(), r.end(), Compare);
	return;
}

//选择特征菜单 
void menu()
{
	//输出知识库中特征数组除植物名的成员，每输出4个换行
	for (int i = 0; i < sizeof(feature) - sizeof(plant); i++)
	{
		if (i % 4 == 0 && i != 0)
			cout << endl;
		cout << setiosflags(ios::left) << setw(3) << i << ".";
		cout << setiosflags(ios::left) << setw(15) << feature[i];
	}
	memset(flag, 0, sizeof(flag));
}
//特征输入值  选择数字 
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
			cin.clear();		//清除流错误错误标记
			cin.sync(); 		//清空输入缓冲区
			cout << "Please continue to enter: ";
		}
	}
}
//是某动物 而不是某种物种 
int IsPlant(int a)
{
	if (a >= 24 && a <= 30)
		return 1;
	return 0;
}
// 判断是否某一物种类 
int IsPlant_speices(int a)
{
	if (a >= 20 && a <= 23)
		return 1;
	return 0;
}
// 返回flag数组中标记的总数 
int fnum()
{
	int fum = 0;
	for (int i = 0; i < 24; i++)
	if (flag[i] == 1)
		fum++;
	return fum;
}
//输出打印物种类别
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

// change_speices --》 flag 发生变化  推理是否有 物种种类 并将用到的事实 清空
//如 有毛 --》哺乳动物  就将flag中哺乳动物的项置一 并将有毛这一特征flag清0
int change_speices()
{
	int i, j, ti;
	bool t;
	int temp[23] = { 0 }; //临时 
	int f[23] = { 0 }; // 标记使用过的flag[] &  < 20  20 哺乳类 
	for (i = 0; i < 8; i++)
	{ // rule 前8个 规则 
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
	// 推理过的事实  则删除  保留结果 
	for (i = 0; i <= 20; i++)
	if (f[i] == 1)
		flag[i] = 0;
	return 1;
}
// 重新计算置信度 
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

//推理  双向推理 -- 正向推理不下去 事实不够 采用逆向推理 
int z_inference()
{
	int ti, num;
	int i, j;
	int fum = fnum();
	cout << endl;
	for (i = 8; i < 15; i++)
	{  //检查规则库 
		Result temp;
		j = 0; num = 0;
		ti = rule[i].relation[j];
		while (ti != -1)
		{
			if (flag[ti] == 1) num++;
			j++;
			ti = rule[i].relation[j];
		}
		// 此时 j  保存则rule[i]所含有的特征数 
		if (num != 0 && fum <= j)
		{  //  给定特征数小于等于的情况 （即flag数组中标记位数目大于此动物的特征数则不放入result） 
			if (IsPlant(rule[i].name))
			{ // 是具体的动物 
				temp.plant = rule[i].name;
				int size = j; // rule[i]所含有的特征数
				temp.size = size;
				temp.confidence = 1.0 * num / size;
				temp.site = i;
				temp.num = num;
				result.push_back(temp);
			}
		}
	}

	if (!result.empty())
		Rsort(result);  //对置信度从高到低排序 

	/*
	//打印排序后的vector
	for(vector<Result>::iterator it = result.begin();it != result.end();++it){
	cout<<setiosflags(ios::left)<<setw(10)<<feature[(*it).animal]<<" ";
	cout<<(*it).confidence<<" ";
	}
	cout<<endl;
	*/
	// 判断 -- 未询问 --正向推理 后 
	if (result.empty()) 
	{ // 给定特征数无法用任何一规则推理  可能没有这种动物  可能是一种动物类别 (系统中无此动物，则输出类别）  
		category();
	}
	else if (result.front().confidence == 1.0)
	{ // 可能给的特征刚好推理出  可能特征还没用完 
		cout << "This animal is " << feature[result.front().plant] << endl;
		result.clear(); // 清空  
		return 1;
	}
	else // 特征描述不全  逆向推理  询问特征 
		r_inference();
}
//特征不足推理  进入反向推理 
void r_inference()
{
	vector<Result>::iterator it = result.begin();
	int enquire[23];  // 用来标记询问过的特征数组 0 N  1 Y 2 D（0 代表没有此特征 1 代表有  2 代表不请楚、不知道） 
	memset(enquire, -1, sizeof(enquire));

	for (int i = 0; i< result.size();)
	{// 从置信度最高开始询问
		bool in_i = true; // i ++ 的标记 
		int  nu = result[i].size;
		for (int j = 0; j < nu; j++)
		{  // 询问 未说明 特征 
			if (flag[rule[result[i].site].relation[j]] == 0)
			{
				int en = rule[result[i].site].relation[j];
				char c;
				if (enquire[en] == -1)
				{ // 此特征未被询问过 则输出询问语句 否则直接判断处理 
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
				{ //有此特征  改变置信度
					result[i].num++;
					enquire[en] = 1;
				}
				else if (enquire[en] == 0 || c == 'N' || c == 'n')
				{ // 没有此特征  直接去掉
					enquire[en] = 0;
					result.erase(it + i);  // erase删除后 i不自增  就能删除最后的元素（迭代器就是指向删除之前元素后的第一个元素）
					in_i = false;  // 如果 擦除了元素 则 i不自增 
					if (result.empty()) //  result 为空 输出类别 退出 
						category();
					break;
				}
				else if (enquire[en] == 2 || c == 'D' || c == 'd')
				{
					enquire[en] = 2; 
				}  // 不确定、不知道  置信度不改变 	
			}
		}
		if (in_i)
			++i;
	}

	if (!result.empty())
	{
		// 改变置信度 
		cal_confi();
		if (result.size() > 1) //重新排序
			Rsort(result);

		//判断 -- 询问后  -- 双向推理后 
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
		result.clear(); // 清空 
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
		cout << "\n继续？(Y/N)" << endl;
		cin >> q;
		system("cls");
	}
	return 0;
}