#pragma once
#include "Container.h"
#include "BasicData.h"
#include <iomanip>

extern HANDLE h;

// Человек
class Human
{
private:

	FullName FIO; // ФИО
	Date birthday; // Дата рождения
	string number_telephone; // Номер телефона

public:

	Human() {} // Конструктор

	void setFIO() { this->FIO.SetInfo(); } // Установка ФИО
	void setBirthday() { this->birthday.SetInfo(); } // Установка дня рождения
	void setNumberTelephone(); // Установка номера телефона

	FullName& getFIO() { return this->FIO; } // Возврат ФИО
	Date& getBirthday() { return this->birthday; } // Возврат дня рождения
	string getNumberTelephone() { return this->number_telephone; } // Возврат номера телефона

	void setInfo(const FullName& FIO, const Date& birth, string number_telephone); // Установка данных
	void outputInfo(); // Вывод данных

	void operator=(const Human& obj) { setInfo(obj.FIO, obj.birthday, obj.number_telephone); } // Перегрузка оператора =

};

// Пользователь
class User : public Human
{
private:
	// В программе реализованы 3 статуса: Администратор, пользователь, менеджер
	string status; // Статус пользователя
	string login; // Логин пользователя
	string salted_hash_password; // Хешированный пароль
	string salt;  // Соль для хеширования

public:

	User() :Human() {
		status = "";
		login = "";
		salted_hash_password = "";
		salt = "";
	} // Конструктор
	User(string status)
	{
		login = "";
		salted_hash_password = "";
		salt = "";
		this->status = status;
	} // Конструктор

	void setLogin(Container<User>& obj); // Ввод логина
	void setPassword(); // Ввод пароля

	string getStatus() { return this->status; } // Возврат статуса
	string getLogin() { return this->login; } // Возврат логина
	string getPassword() { return this->salted_hash_password; } // Возврат пароля
	string getSalt() { return this->salt; } // Возврат 'соли'

	void setInfo(Container<User>& obj); // Установка данных
	void setInfo(const string status, const string login, const string password, const string salt); // Установка данных
	void outputInfo(); // Вывод данных

	friend istream& operator>>(istream& stream, User& obj); // Перегрузка оператора >>
	friend ostream& operator<<(ostream& stream, User& obj); // Перегрузка оператора <<
	void operator=(const User& obj) { setInfo(obj.status, obj.login, obj.salted_hash_password, obj.salt); Human::operator=(obj); } // Перегрузка оператора =
	bool operator<(User& obj); // Перегрузка оператора <

};

