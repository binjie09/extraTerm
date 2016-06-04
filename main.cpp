#include <iostream>     // cin 及 cout
#include <malloc.h>       // 用到申请内存函数 malloc() 和释放内存函数 free()
#include <string>		  // 字符串处理
#include <stdio.h>		  // 文件操作（读文件）
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <list>
#include<vector>
#pragma comment(lib,"ws2_32.lib")
#include  "md5.h"
#include "administratorsSet.h"

using namespace std;
void AdministratorsLogin();
void UserLogin();
void UserRegisterAccount();
struct address				   /*家庭地址*/
{
	char city[10];		   /*城市*/
	char town[10];	   	   /*县城*/
	char village[10];	   /*乡镇*/
};

struct telephone				   /*联系方式*/
{
	char SJ[50];			   /*手机*/
	char JD[30];			   /*家庭电话*/
	char XD[30];			   /*学校电话*/
};

struct person					/*个人信息*/
{
	char name[20];          /*名字*/
	char sex[10];          /*性别*/
	char MZ[16];			/*民族*/
	char GJ[17];			/*国籍*/
	char XL[19];			/*学历*/
};

struct score						//成绩
{
	char num[20];				//学号
	char english[20];
	char chinese[20];
	char math[20];
	char physics[20];
};

typedef struct linknode			//定义节点的类型
{
	char address[100];		//地址
	char birthday[100];		//出生日期
	struct score sc;		//成绩
	struct person pe;		//个人信息
	struct telephone te;	//联系方式
	bool flag;
	struct linknode* next;
}nodetype;
struct information {//账号和密码的结构体
	string account;
	string password;
};


class User {//用户类
public:
	User() {}
	User(string a, string b)
	{
		accountNumber = a;
		password = b;
	}
	string getAccountNumber() {
		return accountNumber;
	}
	string getPossword() {
		return password;
	}
	~User() {}
private:
	string accountNumber;
	string password;

};

class Administrators {  /*管理员类*/

public:
	Administrators();
	Administrators(int x, char *y) {
		accountNumber = x;
		password = y;
	}
	void Login();
private:
	string accountNumber;
	string password;

};


void ExitSystem()
{
	exit(1);
}

int main() {
	//void administratorsSet();
	//administratorsSet();
	//////////////////////////////学生管理系统/////////////////////
	cout << "         1用户注册" << endl;
	cout << "         2用户登录" << endl;
	cout << "         3管理员登录" << endl;
	cout << "         4退出系统" << endl;
	//////////////////////////////////////////////////////////////
	Administrators b;
	int select;
	cin >> select;
	switch (select)
	{
	case 1: UserRegisterAccount(); break;/*用户注册函数*/
	case 2: UserLogin(); break;/*用户登录函数*/
	case 3: AdministratorsLogin(); break;/*管理员函数*/
	case 4: ExitSystem(); break;/*退出系统函数*/
	}
	return 0;
}

bool isExist(const vector<information>& account_passwod, const string& account)
{//比较账号是否相等
	for (const auto& i : account_passwod) {
		if (i.account == account)
			return true;
	}
	return false;
}
bool isExist(const vector<information>& account_passwod, const string& account, const string& password)
{
	for (const auto& i : account_passwod) {
		if (i.account == account && i.password == password)
			return  false;
	}
	return true;
}

bool isExist(vector<information>& account_passwod, const string& account, const string& password, string& newpassword)
{
	for (auto& i : account_passwod) {
		if (i.account == account && i.password == password) {
			i.password = getMD5(newpassword);
			return  1;
		}
	}
	return false;
}


void UserRegisterAccount()/*用户注册函数*/
{
	vector<information> account_passwod;
	ifstream in("user.txt", ios::in);//打开文件
	if (in.fail()) {//如果打开失败，退出
		cout << "ERROR: Cannot open file 'payroll'." << endl;
		exit(1);
	}
	string first, second;
	while (in >> first >> second) {
		account_passwod.push_back({ first, second });//将两
		first.clear();//删除
		second.clear();
	}
	in.close();//关闭文件
	string a;
	bool flag = 1;
	string p;
	cout << "请输入账号：" << endl;
	cin >> a;
	a = getMD5(a);
	while (flag) {
		if (isExist(account_passwod, a))
		{
			a.clear();
			cout << "该账号已经存在，请重新输入" << endl;
			cin >> a;
		}
		else
			break;

	}

	cout << "请输入密码：" << endl;
	cin >> p;
	p = getMD5(p);
	ofstream out("user.txt", ios::app);//打开文件
	if (out.fail()) {
		cout << "ERROR: Cannot open file 'payroll'." << endl;
		exit(1);
	}
	out << a << " " << p << endl;
	out.close();
	//u.preservation();
}

void UserLogin()//用户登录函数
{
	void userCenter();
	vector<information> account_passwod;
	ifstream in("user.txt");//打开文件
	if (in.fail()) {
		cout << "ERROR: Cannot open file 'payroll'." << endl;
		exit(1);
	}
	string first, second;
	while (in >> first >> second) {
		account_passwod.push_back({ first, second });
		first.clear();
		second.clear();
	}
	in.close();
	string a;
	bool flag = 1;
	string p;
	cout << "请输入账号和密码：" << endl;
	cin >> a >> p;
	a = getMD5(a);
	p = getMD5(p);
	while (flag) {
		if (isExist(account_passwod, a, p))
		{
			a.clear();
			p.clear();
			cout << "该账号密码错误，请重新输入" << endl;
			cin >> a >> p;
		}
		else
			userCenter();
		break;
	}
}

void userCenter() {
	void PasswordModification();
	int choice;
	cout << "1个人信息查询" << endl << "2密码修改" << endl << "3退出系统" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:								//MyInformationInquiry();//个人信息查询_________________________by bj(这个函数没找到，先注释掉了)
		break;
	case 2:
		PasswordModification(); break;//密码修改
	case 3:								//ReturnToTheUpperLevel();//_________________________by bj(这个函数也没找到，先注释掉了)
		break;//返回上一级
	}
}

void PasswordModification() {
	void usercenter();
	vector<information> account_passwod;
	ifstream in("user.txt");//打开文件
	if (in.fail()) {
		cout << "ERROR: Cannot open file 'payroll'." << endl;
		exit(1);
	}
	string first, second;
	while (in >> first >> second) {
		account_passwod.push_back({ first, second });
		first.clear();
		second.clear();
	}
	in.close();
	string a, p, newPsassword;
	cout << "请输入旧的的帐号和密码";
	cin >> a >> p;
	a = getMD5(a);
	p = getMD5(p);
	cout << "请输新的密码";
	cin >> newPsassword;
	if (isExist(account_passwod, a, p, newPsassword))
	{

		ofstream out("user.txt", ios::out);//打开文件
		if (out.fail()) {
			cout << "ERROR: Cannot open file 'payroll'." << endl;
			exit(1);
		}

		for (auto& i : account_passwod) {
			out << i.account << " " << i.password << endl;
		}
		out.close();
		cout << "修改密码成功" << endl;
	}


}

void AdministratorsLogin()
{//管理员登录函数
	void Administratorscenter();
	vector<information> account_passwod;
	ifstream in("Administrators.txt");//打开文件
	if (in.fail()) {//如果打开失败，退出
		cout << "ERROR: Cannot open file 'payroll'." << endl;
		exit(1);
	}
	string first, second;
	while (in >> first >> second) {
		account_passwod.push_back({ first, second });
		first.clear();
		second.clear();
	}
	in.close();
	string a;
	bool flag = 1;
	string p;
	cout << "请输入账号和密码：" << endl;
	cin >> a >> p;
	a = getMD5(a);
	p = getMD5(p);
	while (flag) {
		if (isExist(account_passwod, a, p))   //————————by bj(没找到isExist这个函数 只有isExist、isExist2、isExist3这些奇怪命名方式的函数 完全不知道该用哪个)
		{
			a.clear();
			p.clear();
			cout << "管理员账号密码错误，请重新输入" << endl;
			cin >> a >> p;
		}
		else
			Administratorscenter();//管理员中心
		break;
	}
}

void  AdministratorCenterInterface()
{
	//////////////////////////////////////管理界面//////////////////////////////////////
	cout << "1查询学生信息" << endl;
	cout << "2修改学生信息" << endl;
	cout << "3添加学生信息" << endl;
	cout << "4删除学生信息" << endl;
	cout << "5显示所有学生的部分信息" << endl;
	cout << "6保存数据" << endl;
	cout << "7退出本系统" << endl;
}



void Administratorscenter()
{
	void  AdministratorCenterInterface();
	AdministratorCenterInterface();
	int choice;
	cout << "请选择序号来操作" << endl;
	cin >> choice;
	switch (choice) {
	case 1: // QueryPersonalInformation(); break ;//查询学生信息函数-----------------------未实现函数
	case 2: //ModifyStudentInformation(); break;//修改学生信息函数
	case 3: //AddStudentLetter(); break;//添加学生信息
	case 4: //DeleteStudentInformation(); break;//删除学生信息
	case 5: //ShowAllTheStudentsPartOfTheInformation(); break;//显示所有学生部分信息
	case 6: //SaveData(); break;//保存数据
	case 7: //ExitTheLevelSystem(); break;//退出本级系统
		;
	}


}

