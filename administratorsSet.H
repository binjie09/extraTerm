#pragma once

#include <iostream>     // cin 及 cout
#include <malloc.h>       // 用到申请内存函数 malloc() 和释放内存函数 free()
#include <string>		  // 字符串处理
#include <stdio.h>		  // 文件操作（读文件）
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include<vector>
#include  "md5.H"
using namespace std;

struct AdministatorsInfor {//账号和密码的结构体
	string account;
	string password;
};


bool isExist(const vector<AdministatorsInfor>& account_passwod, const string& account)
{//比较账号是否相等
	for (const auto& i : account_passwod) {
		if (i.account == account)
			return true;
	}
	return false;
}

void administratorsSet()/*建立管理员*/
{
	vector<AdministatorsInfor> Administators;
	ifstream in("Administrator.txt", ios::in);//打开文件
	if (in.fail()) {//如果打开失败，退出
		cout << "ERROR: Cannot open file 'payroll'." << endl;
		exit(1);
	}
	string first, second;
	while (in >> first >> second) {
		Administators.push_back({ first, second });//将两
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
		if (isExist(Administators, a))
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
}
Administrators::Administrators()
{
}