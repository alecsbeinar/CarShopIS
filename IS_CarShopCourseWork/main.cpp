// Информационная система автомобильного магазина
#include "ContainersInfo.h"
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор

int main() {
	// Настройки консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	SetConsoleTitle(L"Управление автомобильным магазином");

	Store store;
	store.readData(); // Считывем данные о магазине из файла
	menu::welcomeMenu(string(store.getName())); // Приветственное меню


	while (true)
	{
		system("cls");
		use.readUsers(); // Считываем учетные записии из файла
		vector<string> menu_authorization = { "Авторизация", "Регистрация", "Выход из программы" };
		string name_menu = "АВТОМОБИЛЬНЫЙ МАГАЗИН - " + string(store.getName());
		switch (menu::chooseMenu(menu_authorization, name_menu))
		{
		case 1:
		{
			int user_id = -1;
			switch (use.authorization(user_id))
			{
			case 0:
			{
				menu::userMenu(user_id, store);
				break;
			}
			case 1:
			{
				menu::adminMenu(user_id, store);
				break;
			}
			case 2:
			{
				menu::managerMenu(user_id, store);
				break;
			}
			}
			break;
		}
		case 2:
		{
			use.registration("USER");
			break;
		}
		case 3:
		{
			menu::completionMenu();
			return 0;
		}
		case -1:
		{
			menu::completionMenu();
			return 0;
		}
		}
	}
}




