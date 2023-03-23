// �������������� ������� �������������� ��������
#include "ContainersInfo.h"
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ����������

int main() {
	// ��������� �������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	SetConsoleTitle(L"���������� ������������� ���������");

	Store store;
	store.readData(); // �������� ������ � �������� �� �����
	menu::welcomeMenu(string(store.getName())); // �������������� ����


	while (true)
	{
		system("cls");
		use.readUsers(); // ��������� ������� ������� �� �����
		vector<string> menu_authorization = { "�����������", "�����������", "����� �� ���������" };
		string name_menu = "������������� ������� - " + string(store.getName());
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




