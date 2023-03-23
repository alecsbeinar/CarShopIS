#pragma once
#include "BasicData.h"
#include "Container.h"
#include <iomanip>

class Order
{
private:

	string code; // Код заказа
	string CarCode; // Код товара
	string loginManager; // Логин менеджера
	Date date; // Дата реализации
	int numberOf; // Количество

public:

	Order() {
		code = "";
		CarCode = "";
		loginManager = "";
		numberOf = 0;
	} // Конструктор

	void SetCode(Container<Order>& obj); // Ввод логина
	void SetCarCode(const string code) { this->CarCode = code; } // Ввод кода товара
	void SetLoginManager(const string login) { this->loginManager = login; } // Ввод логина менеджера
	void SetDate() { this->date.SetInfo(); } // Ввод даты
	void SetNumberOf(int max) { this->numberOf = DataProcessing::checkInterval(1, max); } // Ввод количества
	
	string GetCode() { return this->code; } // Возврат кода
	string GetCarCode() { return this->CarCode; } // Возврат кода товара
	string getLoginManager() { return this->loginManager; } // Возврат логина менеджера
	Date& GetDate() { return this->date; } // Возврат даты
	int GetNumberOf() { return this->numberOf; } // Возврат количества

	void SetInfo(const string code, const string CarCode, const string loginManager, const Date& date, const int numberOf); // Инициализация

	friend istream& operator>>(istream& stream, Order& obj); // Перегрузка оператора >>
	friend ostream& operator<<(ostream& stream, const Order& obj); // Перегрузка оператора <<
	void operator=(const Order& obj) { SetInfo(obj.code, obj.CarCode, obj.loginManager, obj.date, obj.numberOf); } // Перегрузка оператора =
	bool operator<(const Order& obj); // Перегрузка оператора <
};