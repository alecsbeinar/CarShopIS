#pragma once
#include "Container.h"
#include "BasicData.h"
#include <iomanip>

extern HANDLE h;

// �������
class Human
{
private:

	FullName FIO; // ���
	Date birthday; // ���� ��������
	string number_telephone; // ����� ��������

public:

	Human() {} // �����������

	void setFIO() { this->FIO.SetInfo(); } // ��������� ���
	void setBirthday() { this->birthday.SetInfo(); } // ��������� ��� ��������
	void setNumberTelephone(); // ��������� ������ ��������

	FullName& getFIO() { return this->FIO; } // ������� ���
	Date& getBirthday() { return this->birthday; } // ������� ��� ��������
	string getNumberTelephone() { return this->number_telephone; } // ������� ������ ��������

	void setInfo(const FullName& FIO, const Date& birth, string number_telephone); // ��������� ������
	void outputInfo(); // ����� ������

	void operator=(const Human& obj) { setInfo(obj.FIO, obj.birthday, obj.number_telephone); } // ���������� ��������� =

};

// ������������
class User : public Human
{
private:
	// � ��������� ����������� 3 �������: �������������, ������������, ��������
	string status; // ������ ������������
	string login; // ����� ������������
	string salted_hash_password; // ������������ ������
	string salt;  // ���� ��� �����������

public:

	User() :Human() {
		status = "";
		login = "";
		salted_hash_password = "";
		salt = "";
	} // �����������
	User(string status)
	{
		login = "";
		salted_hash_password = "";
		salt = "";
		this->status = status;
	} // �����������

	void setLogin(Container<User>& obj); // ���� ������
	void setPassword(); // ���� ������

	string getStatus() { return this->status; } // ������� �������
	string getLogin() { return this->login; } // ������� ������
	string getPassword() { return this->salted_hash_password; } // ������� ������
	string getSalt() { return this->salt; } // ������� '����'

	void setInfo(Container<User>& obj); // ��������� ������
	void setInfo(const string status, const string login, const string password, const string salt); // ��������� ������
	void outputInfo(); // ����� ������

	friend istream& operator>>(istream& stream, User& obj); // ���������� ��������� >>
	friend ostream& operator<<(ostream& stream, User& obj); // ���������� ��������� <<
	void operator=(const User& obj) { setInfo(obj.status, obj.login, obj.salted_hash_password, obj.salt); Human::operator=(obj); } // ���������� ��������� =
	bool operator<(User& obj); // ���������� ��������� <

};

