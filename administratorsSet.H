#pragma once

#include <iostream>     // cin �� cout
#include <malloc.h>       // �õ������ڴ溯�� malloc() ���ͷ��ڴ溯�� free()
#include <string>		  // �ַ�������
#include <stdio.h>		  // �ļ����������ļ���
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include<vector>
#include  "md5.H"
using namespace std;

struct AdministatorsInfor {//�˺ź�����Ľṹ��
	string account;
	string password;
};


bool isExist(const vector<AdministatorsInfor>& account_passwod, const string& account)
{//�Ƚ��˺��Ƿ����
	for (const auto& i : account_passwod) {
		if (i.account == account)
			return true;
	}
	return false;
}

void administratorsSet()/*��������Ա*/
{
	vector<AdministatorsInfor> Administators;
	ifstream in("Administrator.txt", ios::in);//���ļ�
	if (in.fail()) {//�����ʧ�ܣ��˳�
		cout << "ERROR: Cannot open file 'payroll'." << endl;
		exit(1);
	}
	string first, second;
	while (in >> first >> second) {
		Administators.push_back({ first, second });//����
		first.clear();//ɾ��
		second.clear();
	}
	in.close();//�ر��ļ�
	string a;
	bool flag = 1;
	string p;
	cout << "�������˺ţ�" << endl;
	cin >> a;
	a = getMD5(a);
	while (flag) {
		if (isExist(Administators, a))
		{
			a.clear();
			cout << "���˺��Ѿ����ڣ�����������" << endl;
			cin >> a;
		}
		else
			break;

	}

	cout << "���������룺" << endl;
	cin >> p;
	p = getMD5(p);
	ofstream out("user.txt", ios::app);//���ļ�
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