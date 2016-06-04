#include <iostream>     // cin �� cout
#include <malloc.h>       // �õ������ڴ溯�� malloc() ���ͷ��ڴ溯�� free()
#include <string>		  // �ַ�������
#include <stdio.h>		  // �ļ����������ļ���
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
struct address				   /*��ͥ��ַ*/
{
	char city[10];		   /*����*/
	char town[10];	   	   /*�س�*/
	char village[10];	   /*����*/
};

struct telephone				   /*��ϵ��ʽ*/
{
	char SJ[50];			   /*�ֻ�*/
	char JD[30];			   /*��ͥ�绰*/
	char XD[30];			   /*ѧУ�绰*/
};

struct person					/*������Ϣ*/
{
	char name[20];          /*����*/
	char sex[10];          /*�Ա�*/
	char MZ[16];			/*����*/
	char GJ[17];			/*����*/
	char XL[19];			/*ѧ��*/
};

struct score						//�ɼ�
{
	char num[20];				//ѧ��
	char english[20];
	char chinese[20];
	char math[20];
	char physics[20];
};

typedef struct linknode			//����ڵ������
{
	char address[100];		//��ַ
	char birthday[100];		//��������
	struct score sc;		//�ɼ�
	struct person pe;		//������Ϣ
	struct telephone te;	//��ϵ��ʽ
	bool flag;
	struct linknode* next;
}nodetype;
struct information {//�˺ź�����Ľṹ��
	string account;
	string password;
};


class User {//�û���
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

class Administrators {  /*����Ա��*/

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
	//////////////////////////////ѧ������ϵͳ/////////////////////
	cout << "         1�û�ע��" << endl;
	cout << "         2�û���¼" << endl;
	cout << "         3����Ա��¼" << endl;
	cout << "         4�˳�ϵͳ" << endl;
	//////////////////////////////////////////////////////////////
	Administrators b;
	int select;
	cin >> select;
	switch (select)
	{
	case 1: UserRegisterAccount(); break;/*�û�ע�ắ��*/
	case 2: UserLogin(); break;/*�û���¼����*/
	case 3: AdministratorsLogin(); break;/*����Ա����*/
	case 4: ExitSystem(); break;/*�˳�ϵͳ����*/
	}
	return 0;
}

bool isExist(const vector<information>& account_passwod, const string& account)
{//�Ƚ��˺��Ƿ����
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


void UserRegisterAccount()/*�û�ע�ắ��*/
{
	vector<information> account_passwod;
	ifstream in("user.txt", ios::in);//���ļ�
	if (in.fail()) {//�����ʧ�ܣ��˳�
		cout << "ERROR: Cannot open file 'payroll'." << endl;
		exit(1);
	}
	string first, second;
	while (in >> first >> second) {
		account_passwod.push_back({ first, second });//����
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
		if (isExist(account_passwod, a))
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
	//u.preservation();
}

void UserLogin()//�û���¼����
{
	void userCenter();
	vector<information> account_passwod;
	ifstream in("user.txt");//���ļ�
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
	cout << "�������˺ź����룺" << endl;
	cin >> a >> p;
	a = getMD5(a);
	p = getMD5(p);
	while (flag) {
		if (isExist(account_passwod, a, p))
		{
			a.clear();
			p.clear();
			cout << "���˺������������������" << endl;
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
	cout << "1������Ϣ��ѯ" << endl << "2�����޸�" << endl << "3�˳�ϵͳ" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:								//MyInformationInquiry();//������Ϣ��ѯ_________________________by bj(�������û�ҵ�����ע�͵���)
		break;
	case 2:
		PasswordModification(); break;//�����޸�
	case 3:								//ReturnToTheUpperLevel();//_________________________by bj(�������Ҳû�ҵ�����ע�͵���)
		break;//������һ��
	}
}

void PasswordModification() {
	void usercenter();
	vector<information> account_passwod;
	ifstream in("user.txt");//���ļ�
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
	cout << "������ɵĵ��ʺź�����";
	cin >> a >> p;
	a = getMD5(a);
	p = getMD5(p);
	cout << "�����µ�����";
	cin >> newPsassword;
	if (isExist(account_passwod, a, p, newPsassword))
	{

		ofstream out("user.txt", ios::out);//���ļ�
		if (out.fail()) {
			cout << "ERROR: Cannot open file 'payroll'." << endl;
			exit(1);
		}

		for (auto& i : account_passwod) {
			out << i.account << " " << i.password << endl;
		}
		out.close();
		cout << "�޸�����ɹ�" << endl;
	}


}

void AdministratorsLogin()
{//����Ա��¼����
	void Administratorscenter();
	vector<information> account_passwod;
	ifstream in("Administrators.txt");//���ļ�
	if (in.fail()) {//�����ʧ�ܣ��˳�
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
	cout << "�������˺ź����룺" << endl;
	cin >> a >> p;
	a = getMD5(a);
	p = getMD5(p);
	while (flag) {
		if (isExist(account_passwod, a, p))   //����������������by bj(û�ҵ�isExist������� ֻ��isExist��isExist2��isExist3��Щ���������ʽ�ĺ��� ��ȫ��֪�������ĸ�)
		{
			a.clear();
			p.clear();
			cout << "����Ա�˺������������������" << endl;
			cin >> a >> p;
		}
		else
			Administratorscenter();//����Ա����
		break;
	}
}

void  AdministratorCenterInterface()
{
	//////////////////////////////////////�������//////////////////////////////////////
	cout << "1��ѯѧ����Ϣ" << endl;
	cout << "2�޸�ѧ����Ϣ" << endl;
	cout << "3���ѧ����Ϣ" << endl;
	cout << "4ɾ��ѧ����Ϣ" << endl;
	cout << "5��ʾ����ѧ���Ĳ�����Ϣ" << endl;
	cout << "6��������" << endl;
	cout << "7�˳���ϵͳ" << endl;
}



void Administratorscenter()
{
	void  AdministratorCenterInterface();
	AdministratorCenterInterface();
	int choice;
	cout << "��ѡ�����������" << endl;
	cin >> choice;
	switch (choice) {
	case 1: // QueryPersonalInformation(); break ;//��ѯѧ����Ϣ����-----------------------δʵ�ֺ���
	case 2: //ModifyStudentInformation(); break;//�޸�ѧ����Ϣ����
	case 3: //AddStudentLetter(); break;//���ѧ����Ϣ
	case 4: //DeleteStudentInformation(); break;//ɾ��ѧ����Ϣ
	case 5: //ShowAllTheStudentsPartOfTheInformation(); break;//��ʾ����ѧ��������Ϣ
	case 6: //SaveData(); break;//��������
	case 7: //ExitTheLevelSystem(); break;//�˳�����ϵͳ
		;
	}


}

