#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <process.h>
#include <vector>
#include "ContainersInfo.h"
#include "User.h"
#include "Store.h"

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13

using namespace std;
extern HANDLE h;

namespace menu
{

	void welcomeMenu(string); // Вывод приветствия 
	void completionMenu(); // Вывод последнего меню
	int chooseMenu(vector <string> T, string name_menu); // Шаблон вывода меню

	void adminMenu(int user_id, Store& stor); // Меню администратора
	void userMenu(int user_id, Store stor); // Меню пользователя
	void managerMenu(int user_id, Store stor); // Меню менеджера

	void workWithDataMenu(int user_id); // Меню работы с данными
	void workWithCarsMenu(); // Меню работы с машинами
	void workWithOrderMenu(int user_id); // Меню работы с заказами
	void workWithUsers(int user_id); // Меню работы с учетными записями

}