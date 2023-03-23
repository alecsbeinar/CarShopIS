#pragma once

#include "Container.h"
#include "User.h"
#include "Car.h"
#include "Order.h"
#include "Menu.h"
#include <fstream>
#include <conio.h>
#include <map>

const string FILE_USERS = "Users.txt"; // Название файла с учетными записями
const string FILE_Cars = "Cars.txt"; // Название файла с машинами
const string FILE_ORDERS = "Orders.txt"; // Название файла с учетными записями
const string FILE_REPORTS = "Reports.txt"; // Название файла с отчетами



class UseCases
{
private:

	Container<User> containerUser; // Контейнер с учетными записями
	Container<Car> containerCar; // Контейнер с машинами
	Container<Order> containerOrder; // Контейнер с заказами

	Container<User> BackUpcontainerUser; 
	Container<Car> BackUpcontainerCar; 
	Container<Order> BackUpcontainerOrder; 
	map<string, int> mp = { {FILE_USERS, 1}, {FILE_Cars, 2}, {FILE_ORDERS, 3} };

public:
	Container<User>& getVecUser() { return this->containerUser; } // Возвращения вектора пользователей
	int authorization(int& user_id); // Авторизация
	void registration(const string status); // Регистрация нового пользователя
	void outputCapUsers(); // Вывод шапки таблицы пользователей
	void outputAllUsers(); // Вывод таблицы пользователей
	void readUsers(); // Считывание из файла пользователей
	void readUsers(Container<User>& ContUs);
	void writeUsers(); // Запись пользователей в файл
	void delUser(); // Удаление пользователя из контейнера
	int controlUser(); // Проверка на удаления пользователя
	void searchFiltrUser(); // Меню поиска-фильтрации пользователей
	void editUser(int user_id); // Изменение данных о пользователях
	User& findUser(const string login); // Поиск пользователя

	void addCars(); // Добавление машины
	void outputCapCars(); // Вывод шапки таблицы машин
	void outputAllCars(); // Вывод всех машин
	void readCars(); // Считвание из файла машин
	void readCars(Container<Car>& ContCar);
	void writeCars(); // Запись машин в файл
	void delCars(); // Удаление машин из контейнера
	int controlCars(); // Проверочное условие
	void searchFiltrCars(); // Меню поиска-фильтрации машин
	void editCars(); // Изменение данных о товарах
	Car& findCar(const string code); // Поиск товара

	void addOrder(int user_id); // Добавление заказа
	void outputCapOrder(); // Вывод шапки таблицы заказов
	void outputOneOrder(int index); // Вывод одного заказа
	void outputAllOrder(); // Вывод всез заказов
	void readOrder(); // Считывание из файла данных
	void readOrder(Container<Order>& ContOrd);
	void writeOrder(); // Запись данныз в файл
	void delOrder(int user_id);  // Удаление заказа из контейнера
	int controlOrder(int user_id); // Проверочное условие
	void searchFiltrOrder(); // Меню поиска-фильтрации заказа
	void editOrder(int user_id); // Изменение данных о заказе

	void report(); // Создание отчета
	void writeReportFile(int month, int year); // Запись отчета в файл

	void UndoLastAction(const string FILE_NAME); // Отмена последнего действия
	void ClearAllBackUp(); //очистка всех сохраненных данных

};

static UseCases use;

