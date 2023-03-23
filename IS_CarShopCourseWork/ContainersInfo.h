#pragma once

#include "Container.h"
#include "User.h"
#include "Car.h"
#include "Order.h"
#include "Menu.h"
#include <fstream>
#include <conio.h>
#include <map>

const string FILE_USERS = "Users.txt"; // �������� ����� � �������� ��������
const string FILE_Cars = "Cars.txt"; // �������� ����� � ��������
const string FILE_ORDERS = "Orders.txt"; // �������� ����� � �������� ��������
const string FILE_REPORTS = "Reports.txt"; // �������� ����� � ��������



class UseCases
{
private:

	Container<User> containerUser; // ��������� � �������� ��������
	Container<Car> containerCar; // ��������� � ��������
	Container<Order> containerOrder; // ��������� � ��������

	Container<User> BackUpcontainerUser; 
	Container<Car> BackUpcontainerCar; 
	Container<Order> BackUpcontainerOrder; 
	map<string, int> mp = { {FILE_USERS, 1}, {FILE_Cars, 2}, {FILE_ORDERS, 3} };

public:
	Container<User>& getVecUser() { return this->containerUser; } // ����������� ������� �������������
	int authorization(int& user_id); // �����������
	void registration(const string status); // ����������� ������ ������������
	void outputCapUsers(); // ����� ����� ������� �������������
	void outputAllUsers(); // ����� ������� �������������
	void readUsers(); // ���������� �� ����� �������������
	void readUsers(Container<User>& ContUs);
	void writeUsers(); // ������ ������������� � ����
	void delUser(); // �������� ������������ �� ����������
	int controlUser(); // �������� �� �������� ������������
	void searchFiltrUser(); // ���� ������-���������� �������������
	void editUser(int user_id); // ��������� ������ � �������������
	User& findUser(const string login); // ����� ������������

	void addCars(); // ���������� ������
	void outputCapCars(); // ����� ����� ������� �����
	void outputAllCars(); // ����� ���� �����
	void readCars(); // ��������� �� ����� �����
	void readCars(Container<Car>& ContCar);
	void writeCars(); // ������ ����� � ����
	void delCars(); // �������� ����� �� ����������
	int controlCars(); // ����������� �������
	void searchFiltrCars(); // ���� ������-���������� �����
	void editCars(); // ��������� ������ � �������
	Car& findCar(const string code); // ����� ������

	void addOrder(int user_id); // ���������� ������
	void outputCapOrder(); // ����� ����� ������� �������
	void outputOneOrder(int index); // ����� ������ ������
	void outputAllOrder(); // ����� ���� �������
	void readOrder(); // ���������� �� ����� ������
	void readOrder(Container<Order>& ContOrd);
	void writeOrder(); // ������ ������ � ����
	void delOrder(int user_id);  // �������� ������ �� ����������
	int controlOrder(int user_id); // ����������� �������
	void searchFiltrOrder(); // ���� ������-���������� ������
	void editOrder(int user_id); // ��������� ������ � ������

	void report(); // �������� ������
	void writeReportFile(int month, int year); // ������ ������ � ����

	void UndoLastAction(const string FILE_NAME); // ������ ���������� ��������
	void ClearAllBackUp(); //������� ���� ����������� ������

};

static UseCases use;

