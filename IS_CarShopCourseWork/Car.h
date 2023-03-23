#pragma once
#include "WheeledVehicle.h"
#include "Container.h"
#include "ProcessingData.h"
#include <iomanip>

class Car : public WheeledVehicle
{
private:
	string brand;
	string model;
	string code;  // ���
	double price; // ����
	int numberOf; // ����������

public:

	Car() {
		brand = "";
		model = "";
		code = "";
		price = 0;
		numberOf = 0;
	} // �����������

	void SetBrand() { getline(cin, this->brand); } // ���� �����
	void SetModel() { getline(cin, this->model); } // ���� ������
	void SetCode(Container<Car>& obj); // ���� ����
	void SetPrice() { this->price = DataProcessing::checkInterval(0.0, 1000000.00); } // ���� ����
	void SetNumberOf() { this->numberOf = DataProcessing::checkInterval(0, 1000); } // ���� ����������

	string GetBrand() { return this->brand; } // ������� �����
	string GetModel() { return this->model; } // ������� ������
	string GetCode() { return this->code; } // ������� ����
	double GetPrice() { return this->price; } // ������� ����
	int GetNumberOf() { return this->numberOf; } // ������� ����������

	void SetInfo(const string code, const string brand, const string model, const double price, const int numberOf); // �������������
	void OutputInfo(); // ����� ����������
	void Decrease(int number) { this->numberOf -= number; } // ��������� �� ����������
	void Increase(int number) { this->numberOf += number; } // ����������� � ����������

	friend istream& operator>>(istream& stream, Car& obj); // ���������� ��������� >>
	friend ostream& operator<<(ostream& stream, const Car& obj); // ���������� ��������� <<
	void operator=(const Car& obj) { SetInfo(obj.code, obj.brand, obj.model, obj.price, obj.numberOf); } // ���������� ��������� =
	bool operator<(const Car& obj); // ���������� ��������� <

};

