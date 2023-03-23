#pragma once
#include "BasicData.h"
#include "Container.h"
#include <iomanip>

class Order
{
private:

	string code; // ��� ������
	string CarCode; // ��� ������
	string loginManager; // ����� ���������
	Date date; // ���� ����������
	int numberOf; // ����������

public:

	Order() {
		code = "";
		CarCode = "";
		loginManager = "";
		numberOf = 0;
	} // �����������

	void SetCode(Container<Order>& obj); // ���� ������
	void SetCarCode(const string code) { this->CarCode = code; } // ���� ���� ������
	void SetLoginManager(const string login) { this->loginManager = login; } // ���� ������ ���������
	void SetDate() { this->date.SetInfo(); } // ���� ����
	void SetNumberOf(int max) { this->numberOf = DataProcessing::checkInterval(1, max); } // ���� ����������
	
	string GetCode() { return this->code; } // ������� ����
	string GetCarCode() { return this->CarCode; } // ������� ���� ������
	string getLoginManager() { return this->loginManager; } // ������� ������ ���������
	Date& GetDate() { return this->date; } // ������� ����
	int GetNumberOf() { return this->numberOf; } // ������� ����������

	void SetInfo(const string code, const string CarCode, const string loginManager, const Date& date, const int numberOf); // �������������

	friend istream& operator>>(istream& stream, Order& obj); // ���������� ��������� >>
	friend ostream& operator<<(ostream& stream, const Order& obj); // ���������� ��������� <<
	void operator=(const Order& obj) { SetInfo(obj.code, obj.CarCode, obj.loginManager, obj.date, obj.numberOf); } // ���������� ��������� =
	bool operator<(const Order& obj); // ���������� ��������� <
};