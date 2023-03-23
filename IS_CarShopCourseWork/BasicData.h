#pragma once
#include "ProcessingData.h"

// ����������� �����
class BasicInfo
{
public:
	virtual void SetInfo() = 0;
	virtual string OutputAllInfo() = 0;
};

// ����� ���
class FullName : public BasicInfo
{
private:

	string surname; // �������
	string name; // ���
	string patronymic; // ��������
	string fullName; // ���

public:

	FullName() {
		surname = "";
		name = "";
		patronymic = "";
		fullName = "";
	} // �����������

	void SetSurname() { getline(cin, this->surname); } // ���� �������
	void SetName() { getline(cin, this->name); } // ���� �����
	void SetPatronymic() { getline(cin, this->patronymic); } // ���� ��������

	void SetInfo(const string surname, const string name, const string patronymic); // ��������� ����������
	void SetInfo() override; // ��������� ����������

	string getSurname() { return this->surname; } // ������� �������
	string GetName() { return this->name; } // ������� ������
	string GetPatronymic() { return this->patronymic; } // ������� ��������

	string OutputAllInfo() override; // ������� ���� ����������

	friend istream& operator>>(istream& stream, FullName& obj); // ���������� ��������� >>
	friend ostream& operator<<(ostream& stream, const FullName& obj); // ���������� ��������� <<
	void operator=(const FullName& obj) { FullName::SetInfo(obj.surname, obj.name, obj.patronymic); } // ���������� ��������� =
	bool operator==(const FullName& obj) { return surname == obj.surname && name == obj.name && patronymic == obj.patronymic; }
};

// ����� �����
class Address : public BasicInfo
{
private:

	string city; // �����
	string street; // �����
	string house; // ���
	string fullAddress; // ������ �����

public:

	Address() {
		city = "";
		street = "";
		house = "";
		fullAddress = "";
	} // �����������

	void SetCity() { getline(cin, this->city); } // ���� ������
	void SetStreet() { getline(cin, this->street); } // ���� �����
	void SetHouse() { getline(cin, this->house); } // ���� ����

	void SetInfo(const string city, const string street, const string house); // ��������� ���� ����������
	void SetInfo() override; // ��������� ����������

	string GetCity() { return this->city; } // ������� ������
	string GetStreet() { return this->street; } // ������� �����
	string GetHouse() { return this->house; } // ������� ����

	string OutputAllInfo() override; // ����� ���� ����������

	friend istream& operator>>(istream& stream, Address& obj); // ���������� ��������� >>
	friend ostream& operator<<(ostream& stream, const Address& obj); // ���������� ��������� <<
	void operator=(const Address& obj) { SetInfo(obj.city, obj.street, obj.house); } // ���������� ��������� =
	bool operator==(const Address& obj) { return city == obj.city && street == obj.street && house == obj.house; }
};

// ����
class Date : public BasicInfo
{
private:

	int day; // ����
	int month; // �����
	int year; // ���
	string fullDate; // ������ ����

public:

	Date() : day(0), month(0), year(0), fullDate("") { } // �����������

	void SetDay() { this->day = DataProcessing::checkInterval(1, 31); } // ��������� ����
	void SetMonth() { this->month = DataProcessing::checkInterval(1, 12); } // ��������� ������
	void SetYear(int min, int max) { this->year = DataProcessing::checkInterval(min, max); } // ��������� ����

	void SetInfo(int day, int month, int year) { this->day = day; this->month = month; this->year = year; } // ��������� ������
	void SetInfo() override; // ��������� ������

	int GetDay() { return this->day; } // ������� ���
	int GetMonth() { return this->month; } // ������� ������
	int GetYear() { return this->year; } // ������� ����

	string OutputAllInfo() override; // ������� ������ ����

	friend istream& operator>>(istream& stream, Date& obj); // ���������� ��������� >>
	friend ostream& operator<<(ostream& stream, const Date& obj); // ���������� ��������� <<
	void operator=(const Date& obj); // ���������� ��������� =
	bool operator<=(const Date& obj); // ���������� ��������� <=
	bool operator>=(const Date& obj); // ���������� ��������� >=
	bool operator<(const Date& obj); // ���������� ��������� <
	bool operator==(const Date& obj); // ���������� ��������� ==

};