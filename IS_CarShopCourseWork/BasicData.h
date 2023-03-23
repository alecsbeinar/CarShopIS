#pragma once
#include "ProcessingData.h"

// Абстрактный класс
class BasicInfo
{
public:
	virtual void SetInfo() = 0;
	virtual string OutputAllInfo() = 0;
};

// Класс ФИО
class FullName : public BasicInfo
{
private:

	string surname; // Фамилия
	string name; // Имя
	string patronymic; // Отчество
	string fullName; // ФИО

public:

	FullName() {
		surname = "";
		name = "";
		patronymic = "";
		fullName = "";
	} // Конструктор

	void SetSurname() { getline(cin, this->surname); } // Ввод Фамилии
	void SetName() { getline(cin, this->name); } // Ввод Имени
	void SetPatronymic() { getline(cin, this->patronymic); } // Ввод Отчества

	void SetInfo(const string surname, const string name, const string patronymic); // Установка параметров
	void SetInfo() override; // Установка параметров

	string getSurname() { return this->surname; } // Возврат Фамилии
	string GetName() { return this->name; } // Возврат Иммени
	string GetPatronymic() { return this->patronymic; } // Возврат Отчества

	string OutputAllInfo() override; // Возврат всей информации

	friend istream& operator>>(istream& stream, FullName& obj); // Перегрузка оператора >>
	friend ostream& operator<<(ostream& stream, const FullName& obj); // Перегрузка оператора <<
	void operator=(const FullName& obj) { FullName::SetInfo(obj.surname, obj.name, obj.patronymic); } // Перегрузка оператора =
	bool operator==(const FullName& obj) { return surname == obj.surname && name == obj.name && patronymic == obj.patronymic; }
};

// Класс Адрес
class Address : public BasicInfo
{
private:

	string city; // Город
	string street; // Улица
	string house; // Дом
	string fullAddress; // Полный адрес

public:

	Address() {
		city = "";
		street = "";
		house = "";
		fullAddress = "";
	} // Конструктор

	void SetCity() { getline(cin, this->city); } // Ввод города
	void SetStreet() { getline(cin, this->street); } // Ввод улицы
	void SetHouse() { getline(cin, this->house); } // Ввод дома

	void SetInfo(const string city, const string street, const string house); // Установка всей информации
	void SetInfo() override; // Установка параметров

	string GetCity() { return this->city; } // Возврат города
	string GetStreet() { return this->street; } // Возврат улицы
	string GetHouse() { return this->house; } // Возврат дома

	string OutputAllInfo() override; // Вывод всей информации

	friend istream& operator>>(istream& stream, Address& obj); // Перегрузка оператора >>
	friend ostream& operator<<(ostream& stream, const Address& obj); // Перегрузка оператора <<
	void operator=(const Address& obj) { SetInfo(obj.city, obj.street, obj.house); } // Перегрузка оператора =
	bool operator==(const Address& obj) { return city == obj.city && street == obj.street && house == obj.house; }
};

// Дата
class Date : public BasicInfo
{
private:

	int day; // День
	int month; // Месяц
	int year; // Год
	string fullDate; // Полная дата

public:

	Date() : day(0), month(0), year(0), fullDate("") { } // Конструктор

	void SetDay() { this->day = DataProcessing::checkInterval(1, 31); } // Установка даты
	void SetMonth() { this->month = DataProcessing::checkInterval(1, 12); } // Установка месяца
	void SetYear(int min, int max) { this->year = DataProcessing::checkInterval(min, max); } // Установка года

	void SetInfo(int day, int month, int year) { this->day = day; this->month = month; this->year = year; } // Установка данных
	void SetInfo() override; // Установка данных

	int GetDay() { return this->day; } // Возврат дня
	int GetMonth() { return this->month; } // Возврат месяца
	int GetYear() { return this->year; } // Возврат года

	string OutputAllInfo() override; // Возврат полной даты

	friend istream& operator>>(istream& stream, Date& obj); // Перегрузка оператора >>
	friend ostream& operator<<(ostream& stream, const Date& obj); // Перегрузка оператора <<
	void operator=(const Date& obj); // Перегрузка оператора =
	bool operator<=(const Date& obj); // Перегрузка оператора <=
	bool operator>=(const Date& obj); // Перегрузка оператора >=
	bool operator<(const Date& obj); // Перегрузка оператора <
	bool operator==(const Date& obj); // Перегрузка оператора ==

};