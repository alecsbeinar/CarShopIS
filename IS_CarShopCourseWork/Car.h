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
	string code;  // Код
	double price; // Цена
	int numberOf; // Количество

public:

	Car() {
		brand = "";
		model = "";
		code = "";
		price = 0;
		numberOf = 0;
	} // Конструктор

	void SetBrand() { getline(cin, this->brand); } // Ввод марки
	void SetModel() { getline(cin, this->model); } // Ввод модели
	void SetCode(Container<Car>& obj); // Ввод кода
	void SetPrice() { this->price = DataProcessing::checkInterval(0.0, 1000000.00); } // Ввод цены
	void SetNumberOf() { this->numberOf = DataProcessing::checkInterval(0, 1000); } // Ввод количества

	string GetBrand() { return this->brand; } // Возврат марки
	string GetModel() { return this->model; } // Возврат модели
	string GetCode() { return this->code; } // Возврат кода
	double GetPrice() { return this->price; } // Возврат цены
	int GetNumberOf() { return this->numberOf; } // Возврат количества

	void SetInfo(const string code, const string brand, const string model, const double price, const int numberOf); // Инициализация
	void OutputInfo(); // Вывод информации
	void Decrease(int number) { this->numberOf -= number; } // Вычитание из количества
	void Increase(int number) { this->numberOf += number; } // Прибавление к количеству

	friend istream& operator>>(istream& stream, Car& obj); // Перегрузка оператора >>
	friend ostream& operator<<(ostream& stream, const Car& obj); // Перегрузка оператора <<
	void operator=(const Car& obj) { SetInfo(obj.code, obj.brand, obj.model, obj.price, obj.numberOf); } // Перегрузка оператора =
	bool operator<(const Car& obj); // Перегрузка оператора <

};

