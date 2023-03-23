#include "Menu.h"

//������ ������ ����
int menu::chooseMenu(vector<string> T, string name_menu)
{
	system("cls");
	char aT = 0;
	char c;
	while (true)
	{
		SetConsoleCursorPosition(h, { 0,0 });
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << name_menu << endl;
		for (char i = 0; i < size(T); i++)
		{

			if (i == aT) {
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << " =>" << T[i] << "<=" << endl;
			}
			else {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << T[i] << "     " << endl;
			}
		}
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
		cout << "\n����������: ESC - �����, ENTER - �����, ��������� �����-���� - ��� ������������" << endl;
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case ESC:
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			return -1;
		case UP:
			if (aT > 0)
				--aT;
			break;
		case DOWN:
			if (aT < size(T) - 1)
				++aT;
			break;
		case ENTER:
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			system("cls");
			return aT + 1;
			break;

		default:
			cout << "" << (char)c << endl;

		}
	}
}

// ���� ��������������
void menu::adminMenu(int user_id, Store& stor)
{
	use.readUsers();
	use.readOrder();
	use.readCars();
	vector<string> points_menu = { "������ � �������","������ � �������� ��������","��������� ������ � ��������","�������������� ������������ ������", "������ ���������� ����", "����� �� ��������" };
	string name_menu = "���� ��������������";
	int step_edit = 0;
	Store SaveStore;
	while (true) {
		switch (chooseMenu(points_menu, name_menu)) {
		case 1:
		{
			workWithDataMenu(user_id);
			break;
		}
		case 2:
		{
			workWithUsers(user_id);
			break;
		}
		case 3:
		{
			SaveStore.readData();
			stor.editInfo(user_id);
			step_edit = 3;
			break;
		}
		case 4:
		{
			use.editUser(user_id);
			step_edit = 4;
			break;
		}
		case 5:
		{
			switch (step_edit)
			{
			case 3:
			{
				stor.UndoLastAction(SaveStore);
				break;
			}
			case 4:
			{
				use.UndoLastAction(FILE_USERS);
				break;
			}
			default:
				DataProcessing::OutputErrors("������� ��������� �� �����������");
				system("pause");
			}

			break;
		}
		case 6:
		{
			use.ClearAllBackUp();
			return;
		}
		case -1:
		{
			use.ClearAllBackUp();
			return;
		}
		}
	}
}

// ���������������� ����
void menu::userMenu(int user_id, Store stor)
{
	use.readUsers(); // ��������� ������� ������� �� �����
	use.readCars(); // ��������� ������ �������� �� �����
	use.readOrder(); // ��������� ����������� ������

	vector<string> points_menu = { "�������� ���������","����� � ���������� ���������", "������������� ������������ ������","�������� ������ � ��������", "������ ���������� ����", "����� �� ��������" };
	string name_menu = "���� ������������";
	while (true) {
		switch (chooseMenu(points_menu, name_menu)) {
		case 1:
		{
			use.outputAllCars();
			system("pause");
			break;
		}
		case 2:
		{
			use.searchFiltrCars();
			break;
		}
		case 3:
		{
			use.editUser(user_id);
			break;
		}
		case 4:
		{
			stor.outputInfo();
			system("pause");
			break;
		}
		case 5:
		{
			use.UndoLastAction(FILE_USERS);
			break;
		}
		case 6:
		{
			use.ClearAllBackUp();
			return;
		}
		case -1:
		{
			use.ClearAllBackUp();
			return;
		}
		}
	}
}

// ���� ���������
void menu::managerMenu(int user_id, Store stor)
{
	use.readUsers();
	use.readOrder();
	use.readCars();
	vector<string> points_menu = { "������ � �������","�������� ������ � ��������","�������������� ������������ ������", "������ ���������� ����", "����� �� ��������" };
	string name_menu = "���� ���������";
	while (true) {
		switch (chooseMenu(points_menu, name_menu)) {
		case 1:
		{
			workWithDataMenu(user_id);
			break;
		}
		case 2:
		{
			stor.outputInfo();
			system("pause");
			break;
		}
		case 3:
		{
			use.editUser(user_id);
			break;
		}
		case 4:
		{
			use.UndoLastAction(FILE_USERS);
			break;
		}
		case 5:
		{
			use.ClearAllBackUp();
			return;
		}
		case -1:
		{
			use.ClearAllBackUp();
			return;
		}
		}
	}
}

// ���� ������ � �������
void menu::workWithDataMenu(int user_id)
{
	vector<string> points_menu = { "������ � ����������","������ � ��������","������������ ������ �� ������","�����" };
	string name_menu = "���� ������ � �������";
	while (true) {
		switch (chooseMenu(points_menu, name_menu)) {
		case 1:
		{
			workWithCarsMenu();
			break;
		}
		case 2:
		{
			workWithOrderMenu(user_id);
			break;
		}
		case 3:
		{
			use.report();
			break;
		}
		case 4:
		{
			return;
		}
		case -1:
			return;
		}
	}
}

// ���� ������ � ��������
void menu::workWithCarsMenu()
{
	vector<string> points_menu = { "���������� ����� ������","�������������� ���������� � ������","�������� �����","�������� �����","����� � ����������", "������ ���������� ����", "�����" };
	string name_menu = "���� ������ � ����������";
	while (true) {
		switch (chooseMenu(points_menu, name_menu)) {
		case 1:
		{
			use.addCars();
			break;
		}
		case 2:
		{
			use.editCars();
			break;
		}
		case 3:
		{
			use.outputAllCars();
			system("pause");
			break;
		}
		case 4:
		{
			use.delCars();
			break;
		}
		case 5:
		{
			use.searchFiltrCars();
			break;
		}
		case 6:
		{
			use.UndoLastAction(FILE_Cars);
			break;
		}
		case 7:
			return;
		case -1:
			return;
		}
	}
}

// ������ � ��������
void menu::workWithOrderMenu(int user_id)
{
	vector<string> points_menu = { "���������� ������ ������","�������������� ������","�������� ������������� �������","�������� ������","����� � ����������", "������ ���������� ����", "�����" };
	string name_menu = "���� ������ � ��������";
	while (true) {
		switch (chooseMenu(points_menu, name_menu)) {
		case 1:
		{
			use.addOrder(user_id);
			break;
		}
		case 2:
		{
			use.editOrder(user_id);
			break;
		}
		case 3:
		{
			use.outputAllOrder();
			system("pause");
			break;
		}
		case 4:
		{
			use.delOrder(user_id);
			break;
		}
		case 5:
		{
			use.searchFiltrOrder();
			break;
		}
		case 6:
		{
			use.UndoLastAction(FILE_ORDERS);
			break;
		}
		case 7:
			return;
		case -1:
			return;
		}
	}
}

// ���� ������ � �������� ��������
void menu::workWithUsers(int user_id)
{
	vector<string> points_menu = { "���������� ���������","�������� ������ � �������������","�������� ������������","����� � ���������� �������������", "������ ���������� ����", "�����" };
	string name_menu = "���� ������ � �������� ��������";
	while (true) {
		switch (chooseMenu(points_menu, name_menu)) {
		case 1:
		{
			use.registration("MANAGER");
			break;
		}
		case 2:
		{
			use.outputAllUsers();
			system("pause");
			break;
		}
		case 3:
		{
			use.delUser();
			break;
		}
		case 4:
		{
			use.searchFiltrUser();
			break;
		}
		case 5:
		{
			use.UndoLastAction(FILE_USERS);
			break;
		}
		case 6:
			return;
		case -1:
			return;
		}
	}
}

// �������������� ��������
void menu::welcomeMenu(string name_store)
{
	system("cls");
	string name = "����� ���������� � ������������� ������� - " + name_store;
	SetConsoleCursorPosition(h, { 37,10 });
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	for (int i = 0; i < size(name); i++) {
		cout << name[i];
		Sleep(40);
	}
	Sleep(200);
}

void menu::completionMenu()
{
	system("cls");
	string name = "�� ����� ������\n";
	SetConsoleCursorPosition(h, { 55,10 });
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	for (int i = 0; i < size(name); i++) {
		cout << name[i];
		Sleep(40);
	}
	Sleep(600);
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}
