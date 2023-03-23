#include "ContainersInfo.h"

int UseCases::authorization(int& user_id)
{
	string login;
	string password;
	int controller = 1;
	while (controller == 1) {
		system("cls");
		DataProcessing::customizationBlue("�����������");
		DataProcessing::customizationGrey("������� �����: ");
		cin >> login;
		DataProcessing::customizationGrey("������� ������: ");
		password = DataProcessing::enterPasswordWithStars();
		for (int i = 0; i < containerUser.getSize(); i++) {
			if (login == containerUser[i].getLogin() && DataProcessing::getSha1(password + containerUser[i].getSalt()) == containerUser[i].getPassword()) {
				system("cls");
				user_id = i;
				if (containerUser[i].getStatus() == "USER")
					return 0;
				else if (containerUser[i].getStatus() == "ADMIN")
					return 1;
				else
					return 2;
			}
		}

		DataProcessing::OutputErrors("\n�������� ����� ��� ������!");
		DataProcessing::customizationGrey("����������� ��� ���? (1 - �� / 2 - ���): ");
		controller = DataProcessing::checkInterval(1, 2);

	}
}
void UseCases::registration(const string status)
{
	User obj(status);
	obj.setInfo(this->containerUser);
	this->containerUser.add(obj);
	writeUsers();
	DataProcessing::customizationGreen("����������� ������ �������");
	system("pause");
}
void UseCases::outputCapUsers()
{
	cout << "\n|=============================================================================================|"
		<< "\n|                                       ~������� ������~                                      |"
		<< "\n|=============================================================================================|"
		<< "\n|  �  |      �����     |     ����     |       ���        |   ���� ��������   | ����� �������� |"
		<< "\n|=============================================================================================|\n";

}
void UseCases::outputAllUsers()
{
	outputCapUsers();
	int counter = 0;
	for (auto i : this->containerUser)
	{
		cout << "|" << setw(5) << left << ++counter << "|"; i.outputInfo(); cout << endl;
	}
	cout << "|=============================================================================================|\n";

}
void UseCases::readUsers()
{
	this->containerUser.clear();
	ifstream fin(FILE_USERS);
	while (1)
	{
		User obj;
		if (fin >> obj)
		{
			this->containerUser.add(obj);
		}
		else break;
	}
	fin.close();
	if (this->containerUser.getSize() == 0)
		registration("ADMIN");
}
void UseCases::readUsers(Container<User>& ContUs)
{
	ContUs.clear();
	ifstream fin(FILE_USERS);
	while (1)
	{
		User obj;
		if (fin >> obj)
		{
			ContUs.add(obj);
		}
		else break;
	}
	fin.close();
}
void UseCases::writeUsers()
{
	readUsers(this->BackUpcontainerUser);

	ofstream fout(FILE_USERS, ios_base::trunc);
	for (register int i = 0; i < this->containerUser.getSize(); i++)
		fout << this->containerUser[i] << endl;
	fout.close();
}
void UseCases::delUser()
{
	int choise;
	while (1)
	{
		system("cls");
		outputAllUsers();
		DataProcessing::customizationGrey("������� ����� ������, ������� ������ ������� (0 - ��������� �����): ");
		choise = controlUser();
		if (choise == 0)
			break;
		else if (choise == 1)
		{
			system("cls");
			DataProcessing::OutputErrors("������ ������� ������� ������ ��� ������� �� �����!");
			system("pause");
		}
		else
		{
			DataProcessing::customizationGrey("����������� ��������? (1 - �� / 2- ���): ");
			int controller = DataProcessing::checkInterval(1, 2);
			if (controller == 1) {
				this->containerUser.del(choise - 1);
				writeUsers();
				DataProcessing::customizationGreen("������ ������� �������");
				system("pause");
			}

		}
	}
}
int UseCases::controlUser()
{
	int choise;
	do {
		choise = DataProcessing::checkInterval(0, this->containerUser.getSize());
		if (choise != 0 && choise != 1)
		{
			for (int i = 0; i < this->containerOrder.getSize(); i++)
			{
				if (this->containerUser[choise - 1].getLogin() == this->containerOrder[i].getLoginManager())
				{
					DataProcessing::OutputErrors("������ ������� ������ ������!!!\n��� �������� ����� ������������ ����� ������� ��� ��� ������������� ������: ");
					choise = -1;
					break;
				}
			}
		}
	} while (choise == -1);
	return choise;
}
void UseCases::searchFiltrUser()
{
	string BufForWriting;
	Date min, max;
	while (1)
	{
		vector <string> points_menu = { "����� �� �������", "����� �� ������", "����� �� �������", "����� �� ��������", "����� �� ����", "���������� �� ����", "�����" };
		string name_menu = "���������� � ����������";
		int choise = menu::chooseMenu(points_menu, name_menu);
		if (choise == -1)
			return;
		if (choise == 6)
		{
			Container<User> vecBuf;
			vecBuf = this->containerUser;
			containerUser.sort();
			cout << "\t\t\t\t    ~��������������� ������~";
			outputAllUsers();
			this->containerUser = vecBuf;
			system("pause");
		}
		else if (choise == 7)
			break;
		else
		{
			switch (choise)
			{
			case 1: DataProcessing::customizationGrey("������� ������: "); break;
			case 2: DataProcessing::customizationGrey("������� �����: "); break;
			case 3:	DataProcessing::customizationGrey("������� �������: "); break;
			case 4: DataProcessing::customizationGrey("������� ����� ��������: "); break;
			case 5:
				cout << "\t����������� ��������" << endl;
				min.SetInfo();
				while (1)
				{
					cout << "\t������������ ��������" << endl;
					max.SetInfo();
					if (min <= max)
						break;
					else cout << "��� ������ ��������, ���������� ��� ���!" << endl;
				}
				break;
			}
			if (choise != 5)
				cin >> BufForWriting;
			int controller = -1, counter = 0;
			for (register int i = 0; i < this->containerUser.getSize(); i++)
			{
				switch (choise)
				{
				case 1:
					if (BufForWriting == this->containerUser[i].getStatus())
						controller = 0;
					else
						controller = -1;
					break;
				case 2:
					if (BufForWriting == this->containerUser[i].getLogin())
						controller = 0;
					else
						controller = -1;
					break;
				case 3:
					if (BufForWriting == this->containerUser[i].getFIO().getSurname())
						controller = 0;
					else
						controller = -1;
					break;
				case 4:
					if (BufForWriting == this->containerUser[i].getNumberTelephone())
						controller = 0;
					else
						controller = -1;
					break;
				case 5:
					if (this->containerUser[i].getBirthday() >= min && this->containerUser[i].getBirthday() <= max)
						controller = 0;
					else controller = -1;
					break;
				}
				if (controller == 0)
				{
					counter++;
					if (counter == 1) {
						cout << "\t\t\t\t    ~��������� ������������~";
						outputCapUsers();
					}
					cout.setf(ios::left);
					cout << "|" << setw(5) << counter << "|"; this->containerUser[i].outputInfo(); cout << endl;
				}
			}
			if (counter > 0)
				cout << "|=============================================================================================|\n";
			if (counter == 0) DataProcessing::OutputErrors("������ �� �������!");
			system("pause");
		}
	}
}
void UseCases::editUser(int user_id)
{
	string old_password, new_login;
	while (1)
	{
		system("cls");
		string name_menu = "���� ������, �������� ������ ��� ���������";
		vector<string> points_menu = { "������: ******", "�����: " + string(this->containerUser[user_id].getLogin()), "���: " + string(this->containerUser[user_id].getFIO().OutputAllInfo()), "���� ��������: " + string(this->containerUser[user_id].getBirthday().OutputAllInfo()), "����� ��������: " + string(this->containerUser[user_id].getNumberTelephone()) };

		switch (menu::chooseMenu(points_menu, name_menu))
		{
		case 1:
			DataProcessing::customizationGrey("������� ������ ������: ");
			cin >> old_password;
			if (DataProcessing::getSha1(old_password + containerUser[user_id].getSalt()) == containerUser[user_id].getPassword())
			{
				this->containerUser[user_id].setPassword();
				DataProcessing::customizationGreen("������ ������� �������!\n");
				this->writeUsers();
				system("pause");
			}
			else
			{
				DataProcessing::OutputErrors("�������� ������ ������!\n");
				system("pause");
			}
			break;

		case 2:
			this->containerUser[user_id].setLogin(this->containerUser);
			DataProcessing::customizationGreen("����� ������� �������!\n");
			this->writeUsers();
			system("pause");
			break;
		case 3:
			DataProcessing::customizationBlue("���");
			this->containerUser[user_id].setFIO();
			DataProcessing::customizationGreen("��� ������� ��������!\n");
			this->writeUsers();
			system("pause");
			break;
		case 4:
			DataProcessing::customizationBlue("���� ��������");
			this->containerUser[user_id].setBirthday();
			DataProcessing::customizationGreen("���� �������� ������� ��������!\n");
			system("pause");
			this->writeUsers();
			break;
		case 5:
			this->containerUser[user_id].setNumberTelephone();
			DataProcessing::customizationGreen("����� �������� ������� �������!\n");
			this->writeUsers();
			system("pause");
			break;
		case -1:
			return;
		default: break;
		}

	}
}
User& UseCases::findUser(const string login)
{
	int controller = -1;
	for (register int i = 0; i < this->containerUser.getSize(); i++)
	{
		if (this->containerUser[i].getLogin() == login)
		{
			controller = 0;
			return this->containerUser[i];
		}
	}
	if (controller == -1)
		return this->containerUser[0];
}

void UseCases::addCars()
{
	system("cls");
	DataProcessing::customizationBlue("���������� ����� ������");
	Car obj;
	obj.SetCode(this->containerCar);
	
	DataProcessing::customizationGrey("�����: "); obj.SetBrand();
	DataProcessing::customizationGrey("������: "); obj.SetModel();
	DataProcessing::customizationGrey("����(USD): "); obj.SetPrice();
	DataProcessing::customizationGrey("���-��(� �������): "); obj.SetNumberOf();
	this->containerCar.add(obj);
	writeCars();
	DataProcessing::customizationGreen("����� ������� ��������");
	system("pause");
}
void UseCases::outputCapCars()
{
	cout << "\n|=================================================================================================|"
		<< "\n|                                        ~��������� ��������~                                     |"
		<< "\n|=================================================================================================|"
		<< "\n|  �  |     ���     |       �����       |       ������       |     ����(USD)      |   � �������   |"
		<< "\n|=================================================================================================|\n";

}
void UseCases::outputAllCars()
{
	if (this->containerCar.getSize() > 0)
	{
		cout.setf(ios::left);
		outputCapCars();
		int counter = 0;
		for (auto i : this->containerCar)
		{
			cout << "|" << setw(5) << ++counter << "|"; 
			i.OutputInfo(); 
			cout << endl;
		}
		cout << "|=================================================================================================|" << endl;
	}
	else DataProcessing::OutputErrors("��� �������");
}
void UseCases::readCars()
{
	this->containerCar.clear();
	ifstream fin(FILE_Cars);
	while (1)
	{
		Car obj;
		if (fin >> obj)
			this->containerCar.add(obj);
		else break;
	}
	fin.close();
}
void UseCases::readCars(Container<Car>& ContCar)
{
	ContCar.clear();
	ifstream fin(FILE_Cars);
	while (1)
	{
		Car obj;
		if (fin >> obj)
			ContCar.add(obj);
		else break;
	}
	fin.close();
}
void UseCases::writeCars()
{
	readCars(this->BackUpcontainerCar);

	ofstream fout(FILE_Cars, ios_base::trunc);
	for (int i = 0; i < this->containerCar.getSize(); i++)
		fout << this->containerCar[i] << endl;
	fout.close();
}
void UseCases::delCars()
{
	if (this->containerCar.getSize() > 0)
	{
		int choise;
		while (1)
		{
			system("cls");
			outputAllCars();
			DataProcessing::customizationGrey("������� ����� ������, ������� ������ ������� (0 - ��������� �����): ");
			choise = controlCars();
			if (choise == 0)
				break;
			else
			{
				DataProcessing::customizationGrey("����������� ��������? (1 - �� / 2- ���): ");
				int controller = DataProcessing::checkInterval(1, 2);
				if (controller == 1) {
					this->containerCar.del(choise - 1);
					writeCars();
					DataProcessing::customizationGreen("������ ������� ������");
					system("pause");
				}

			}
		}
	}
	else { DataProcessing::OutputErrors("��� �������"); system("pause"); }

}
int UseCases::controlCars()
{
	int choise;
	do {
		choise = DataProcessing::checkInterval(0, this->containerCar.getSize());
		if (choise != 0 && this->containerOrder.getSize() > 0)
		{
			for (int i = 0; i < this->containerOrder.getSize(); i++)
			{
				if (this->containerCar[choise - 1].GetCode() == this->containerOrder[i].GetCarCode())
				{
					DataProcessing::OutputErrors("������ ������� ������ ������!!! ��� �������� ������ ������ ����� �������\n��� ������ � ������ ����� ���������: ");
					choise = -1;
					break;
				}
			}
		}
	} while (choise == -1);
	return choise;
}
void UseCases::searchFiltrCars()
{
	if (this->containerCar.getSize() > 0)
	{
		string BufForWriting, brand, model;
		double min = 0, max = 0;
		while (1)
		{
			system("cls");
			vector<string> points_menu = { "����� �� ���� ������","����� �� �������� ������","���������� �� ����","���������� �� ����", "�����" };
			string name_menu = "���� ������ � ����������";
			int choise = menu::chooseMenu(points_menu, name_menu);
			if (choise == -1)
				return;
			if (choise == 4)
			{
				Container<Car> vecBuf;
				vecBuf = this->containerCar;
				containerCar.sort();
				outputAllCars();
				this->containerCar = vecBuf;
				system("pause");
			}
			else if (choise == 5)
				break;
			else
			{
				switch (choise)
				{
				case 1: DataProcessing::customizationGrey("������� ��� ������: "); cin >> BufForWriting; break;
				case 2: 
				{
					DataProcessing::customizationGrey("������� ����� ������: ");
					cin >> brand;
					DataProcessing::customizationGrey("������� ������ ������: ");
					cin >> model;
					break;
				}
				case 3:
					DataProcessing::customizationGrey("������� ����������� �������� ����: "); min = DataProcessing::checkInterval(0.00, 1000000.00);
					DataProcessing::customizationGrey("������� ������������ �������� ����: "); max = DataProcessing::checkInterval(min, 1000001.00);
					break;
				}
				int controller = -1, counter = 0;
				for (int i = 0; i < this->containerCar.getSize(); i++)
				{
					switch (choise)
					{
					case 1:
						if (this->containerCar[i].GetCode() == BufForWriting)
							controller = 0;
						else
							controller = 1;
						break;
					case 2:
						if (this->containerCar[i].GetBrand() == brand && this->containerCar[i].GetModel() == model)
							controller = 0;
						else
							controller = 1;
						break;
					case 3:
						if (this->containerCar[i].GetPrice() >= min && this->containerCar[i].GetPrice() <= max)
							controller = 0;
						else controller = -1;
						break;
					}
					if (controller == 0)
					{
						counter++;
						if (counter == 1) {
							cout << "\t\t\t\t   ~��������� ������~";
							outputCapCars();
						}

						cout << "|" << setw(5) << counter << "|"; this->containerCar[i].OutputInfo(); cout << endl;

					}

				}

				if (counter == 0)
					DataProcessing::OutputErrors("������ �� �������");
				else
					cout << "|=================================================================================================|" << endl;
				system("pause");
			}
		}

	}
	else { DataProcessing::OutputErrors("��� �������\n"); system("pause"); }

}
void UseCases::editCars()
{
	int choise;
	if (this->containerCar.getSize() > 0)
	{
		while (1)
		{
			system("cls");
			outputAllCars();
			DataProcessing::customizationGrey("������� ����� ������, ������� ������ ������������� (0 - ��������� �����): ");
			choise = DataProcessing::checkInterval(0, this->containerCar.getSize());
			if (choise != 0)
			{
				vector <string> points_menu = { "�����", "������", "����", "����������", "�����" };
				string name_menu = "�������� ��������������";
				switch (menu::chooseMenu(points_menu, name_menu))
				{
				case 1:
					system("cls");
					DataProcessing::customizationGrey("������� ����� �������� �����: ");
					this->containerCar[choise - 1].SetBrand();
					DataProcessing::customizationGreen("����� ������� ��������");
					system("pause");
					writeCars();
					break;
				case 2:
					system("cls");
					DataProcessing::customizationGrey("������� ����� �������� ������: ");
					this->containerCar[choise - 1].SetModel();
					DataProcessing::customizationGreen("������ ������� ��������");
					system("pause");
					writeCars();
					break;
				case 3:
					system("cls");
					DataProcessing::customizationGrey("������� ����� ����(USD): ");
					this->containerCar[choise - 1].SetPrice();
					DataProcessing::customizationGreen("���� ������� ��������");
					system("pause");
					writeCars();
					break;
				case 4:
					system("cls");
					DataProcessing::customizationGrey("������� ����� ����������: ");
					this->containerCar[choise - 1].SetNumberOf();
					DataProcessing::customizationGreen("���������� ������� ��������");
					system("pause");
					writeCars();
					break;
				default: break;
				}
			}
			else break;
		}
	}
	else { DataProcessing::OutputErrors("��� �������"); system("pause"); }

}
Car& UseCases::findCar(const string code)
{
	int controller = -1;
	for (register int i = 0; i < this->containerCar.getSize(); i++)
	{
		if (this->containerCar[i].GetCode() == code)
		{
			controller = 0;
			return this->containerCar[i];
		}
	}
	if (controller == -1)
		return this->containerCar[0];
}


void UseCases::addOrder(int user_id)
{
	try {
		if (this->containerCar.getSize() == 0)
			throw 1;
		int controller = -1;
		for (int i = 0; i < this->containerCar.getSize(); i++)
		{
			if (this->containerCar[i].GetNumberOf() > 0)
			{
				controller = 0;
				break;
			}
		}
		if (controller == 0)
		{
			int choise = 0;
			system("cls");
			DataProcessing::customizationBlue("���������� ������");
			Order obj;
			obj.SetLoginManager(this->containerUser[user_id].getLogin());
			obj.SetCode(this->containerOrder);
			outputAllCars();
			DataProcessing::customizationGrey("�������� ������ ������: ");
			choise = DataProcessing::checkInterval(1, this->containerCar.getSize());
			if (this->containerCar[choise - 1].GetNumberOf() == 0) {
				DataProcessing::OutputErrors("������ ����� ����������� � �������");
				system("pause");
				return;
			}
			obj.SetCarCode(this->containerCar[choise - 1].GetCode());
			DataProcessing::customizationGrey("���-�� ��. ���������: ");
			obj.SetNumberOf(this->containerCar[choise - 1].GetNumberOf());
			this->containerCar[choise - 1].Decrease(obj.GetNumberOf());
			cout << "���� �������" << endl;
			obj.SetDate();
			this->containerOrder.add(obj);
			writeOrder();
			writeCars();
			DataProcessing::customizationGreen("����� ������� ��������");
			system("pause");
		}
		else { system("cls"); DataProcessing::OutputErrors("�� ������ ��� �� ����� ������� ���������"); system("pause"); }
	}

	catch (int) {
		system("cls");
		DataProcessing::OutputErrors("�������� ���� �� ���� ��� ���������");
		system("pause");
	}
}
void UseCases::outputCapOrder()
{
	cout << "\n|===================================================================================================================================|"
		<< "\n|                                                      ~������������� ������~                                                       |"
		<< "\n|===================================================================================================================================|"
		<< "\n| � |��� ������|����� ���������|  ��� ���������  |��� ������| �������� ����� | �������� ������ | ����� ���� | ���-�� | ���� ������� |"
		<< "\n|===================================================================================================================================|\n";
}
void UseCases::outputOneOrder(int index)
{
	cout << setw(10) << this->containerOrder[index].GetCode() << "|" << setw(15) << this->containerOrder[index].getLoginManager() << "|"
		<< setw(17) << findUser(this->containerOrder[index].getLoginManager()).getFIO().OutputAllInfo() << "|"
		<< setw(10) << this->containerOrder[index].GetCarCode() << "|"
		<< setw(16) << findCar(this->containerOrder[index].GetCarCode()).GetBrand() << "|"
		<< setw(17) << findCar(this->containerOrder[index].GetCarCode()).GetModel() << "|"
		<< setw(12) << findCar(this->containerOrder[index].GetCarCode()).GetPrice() * this->containerOrder[index].GetNumberOf() << "|"
		<< setw(8) << this->containerOrder[index].GetNumberOf() << "|" << setw(14) << this->containerOrder[index].GetDate().OutputAllInfo() << "|";
}
void UseCases::outputAllOrder()
{
	try
	{
		if (this->containerOrder.getSize() == 0)
			throw 1;
		cout.setf(ios::left);
		outputCapOrder();
		for (register int i = 0; i < this->containerOrder.getSize(); i++)
		{
			cout << "|" << setw(3) << i + 1 << "|"; outputOneOrder(i); cout << endl;
		}
		cout << "|===================================================================================================================================|\n";
	}
	catch (int) {
		DataProcessing::OutputErrors("��� �������");
	}
}
void UseCases::readOrder()
{
	this->containerOrder.clear();
	ifstream fin(FILE_ORDERS);
	while (1)
	{
		Order obj;
		if (fin >> obj)
			this->containerOrder.add(obj);
		else break;
	}
	fin.close();
}
void UseCases::readOrder(Container<Order>& ContOrd)
{
	ContOrd.clear();
	ifstream fin(FILE_ORDERS);
	while (1)
	{
		Order obj;
		if (fin >> obj)
			ContOrd.add(obj);
		else break;
	}
	fin.close();
}
void UseCases::writeOrder()
{
	readOrder(this->BackUpcontainerOrder);

	ofstream fout(FILE_ORDERS, ios_base::trunc);
	for (register int i = 0; i < this->containerOrder.getSize(); i++)
		fout << this->containerOrder[i] << endl;
	fout.close();
}
void UseCases::delOrder(int user_id)
{
	try
	{
		if (this->containerOrder.getSize() == 0)
			throw 1;
		int choise;
		while (1)
		{
			system("cls");
			outputAllOrder();
			DataProcessing::customizationGrey("������� ����� ������, ������� ������ ������� (0 - ��������� �����): ");
			choise = controlOrder(user_id);
			if (choise == 0)
				break;
			else
			{
				DataProcessing::customizationGrey("����������� ��������? (1 - �� / 2- ���): ");
				int controller = DataProcessing::checkInterval(1, 2);
				if (controller == 1) {
					this->containerOrder.del(choise - 1);
					writeOrder();
					DataProcessing::customizationGreen("����� ������� ������");
					system("pause");
					return;
				}
			}
		}
	}
	catch (int) { DataProcessing::OutputErrors("��� �������"); system("pause"); }
}
int UseCases::controlOrder(int user_id)
{
	int choise;
	do {
		choise = DataProcessing::checkInterval(0, this->containerOrder.getSize());
		if (choise != 0 && user_id != 0 && this->containerOrder[choise - 1].getLoginManager() != this->containerUser[user_id].getLogin())
		{
			DataProcessing::OutputErrors("������������� ������ ������ ���������� ����� �������/������������� ������ ������� ����� ���������!");
			choise = -1;
		}
	} while (choise == -1);
	return choise;
}
void UseCases::searchFiltrOrder()
{
	try
	{
		if (this->containerOrder.getSize() == 0)
			throw 1;
		string BufForWriting;
		Date min, max;
		while (1)
		{
			vector <string> points_menu = { "����� �� ���� ������", "����� �� ���� ��������", "����� �� ������� ���������", "���������� �� ���� ���������� ������","���������� �� ���� ���������� ������", "�����" };
			string name_menu = "�������� ������ � ����������";
			int choise = menu::chooseMenu(points_menu, name_menu);
			if (choise == -1)
				return;
			if (choise == 5)
			{
				Container<Order> vecBuf;
				vecBuf = this->containerOrder;
				containerOrder.sort();
				outputAllOrder();
				this->containerOrder = vecBuf;
				system("pause");
			}
			else if (choise == 6)
				break;
			else
			{
				switch (choise)
				{
				case 1: DataProcessing::customizationGrey("������� ��� ������: "); cin >> BufForWriting; break;
				case 2:
					outputAllCars();
					DataProcessing::customizationGrey("�������� ������ �������: ");
					BufForWriting = this->containerCar[DataProcessing::checkInterval(1, this->containerCar.getSize()) - 1].GetCode();
					break;
				case 3: DataProcessing::customizationGrey("������� ���������: "); cin >> BufForWriting; break;
				case 4:
					DataProcessing::customizationGrey("����������� ��������: ");
					min.SetInfo();
					while (1)
					{
						DataProcessing::customizationGrey("������������ ��������: ");
						max.SetInfo();
						if (min <= max)
							break;
						else DataProcessing::OutputErrors("��� ������ ��������, ���������� ��� ���!");
					}
					break;
				}
				int controller = -1, counter = 0;
				for (int i = 0; i < this->containerOrder.getSize(); i++)
				{
					switch (choise)
					{
					case 1:
						if (this->containerOrder[i].GetCode() == BufForWriting)
							controller = 0;
						else
							controller = 1;
						break;
					case 2:
						if (this->containerOrder[i].GetCarCode() == BufForWriting)
							controller = 0;
						else
							controller = 1;
						break;
					case 3:

						if (findUser(this->containerOrder[i].getLoginManager()).getFIO().getSurname() == BufForWriting)
							controller = 0;
						else
							controller = 1;
						break;
					case 4:
						if (this->containerOrder[i].GetDate() >= min && this->containerOrder[i].GetDate() <= max)
							controller = 0;
						else controller = -1;
						break;
					}
					if (controller == 0)
					{
						counter++;
						if (counter == 1) {
							cout << "\t\t\t\t\t          ~��������� ������~";
							outputCapOrder();
						}
						cout << "|" << setw(3) << counter << "|"; outputOneOrder(i); cout << endl;

					}
				}

				if (counter == 0)
					DataProcessing::OutputErrors("������ �� �������");
				else
					cout << "|===================================================================================================================================|\n";
				system("pause");
			}
		}

	}
	catch (int) { DataProcessing::OutputErrors("��� �������"); system("pause"); }
}
void UseCases::editOrder(int user_id)
{
	int choise;
	int choiseDevice = 0;
	try
	{
		if (this->containerOrder.getSize() == 0)
			throw 1;
		while (1)
		{
			system("cls");
			outputAllOrder();
			DataProcessing::customizationGrey("������� ����� ������, ������� ������ ������������� (0 - ��������� �����): ");
			choise = controlOrder(user_id);
			if (choise != 0)
			{
				vector<string> points_menu = { "�������", "���������� ������ ���������", "���� ���������� ������", "�����" };
				string name_menu = "�������� ��������������";
				switch (menu::chooseMenu(points_menu, name_menu))
				{
				case 1:
				{
					findCar(this->containerOrder[choise - 1].GetCarCode()).Increase(this->containerOrder[choise - 1].GetNumberOf());
					outputAllCars();
					DataProcessing::customizationGrey("�������� ������: ");
					choiseDevice = DataProcessing::checkInterval(1, this->containerCar.getSize());
					if (this->containerCar[choiseDevice - 1].GetNumberOf() == 0) {
						DataProcessing::OutputErrors("������ ����� ����������� � �������");
						system("pause");
						break;
					}
					this->containerOrder[choise - 1].SetCarCode(this->containerCar[choiseDevice - 1].GetCode());
					DataProcessing::customizationGrey("��� - �� ��.���������: ");
					this->containerOrder[choise - 1].SetNumberOf(this->containerCar[choise - 1].GetNumberOf());
					writeOrder();
					writeCars();
					DataProcessing::customizationGreen("������� ������� �������");
					system("pause");
					break;
				}
				case 2: {
					findCar(this->containerOrder[choise - 1].GetCarCode()).Increase(this->containerOrder[choise - 1].GetNumberOf());
					string str = "���-�� ��. ��������� (������� ";
					str += to_string(findCar(this->containerOrder[choise - 1].GetCarCode()).GetNumberOf());
					str += " ��.): ";
					DataProcessing::customizationGrey(str);
					this->containerOrder[choise - 1].SetNumberOf(findCar(this->containerOrder[choise - 1].GetCarCode()).GetNumberOf());
					writeOrder();
					writeCars();
					DataProcessing::customizationGreen("���������� ������� ��������");
					system("pause");
					break;
				}

				case 3:
				{
					DataProcessing::customizationBlue("���� ����������");
					this->containerOrder[choise - 1].SetDate();
					writeOrder();
					DataProcessing::customizationGreen("���� ������� ��������");
					system("pause");
					break;
				}
				default: break;
				}
			}
			else break;
		}
	}
	catch (int) { DataProcessing::OutputErrors("��� �������"); system("pause"); }
}

void UseCases::report()
{
	try
	{
		if (this->containerOrder.getSize() == 0)
			throw 1;
		int month, year;
		system("cls");
		DataProcessing::customizationBlue("������������ ��������� ������");
		DataProcessing::customizationGrey("������� �����(1 - 12): "); month = DataProcessing::checkInterval(1, 12);
		DataProcessing::customizationGrey("������� ��� : "); year = DataProcessing::checkInterval(1990, 2022);
		system("cls");
		int counter = 0; double sum = 0.0;
		Container<int> counterDevice(this->containerCar.getSize(), 0);
		Container<double> counterUser(this->containerUser.getSize(), 0.0);
		for (register int i = 0; i < this->containerOrder.getSize(); i++)
		{
			if (this->containerOrder[i].GetDate().GetMonth() == month && this->containerOrder[i].GetDate().GetYear() == year)
			{
				counter++;
				if (counter == 1) {
					cout << "\t\t\t\t\t      ~����� �� ������ (����� - " << to_string(month) << ", ��� - " << to_string(year) << ")~";
					outputCapOrder();
				}
				cout.setf(ios::left);
				cout << "|" << setw(3) << counter << "|"; outputOneOrder(i); cout << endl;
				sum += findCar(this->containerOrder[i].GetCarCode()).GetPrice() * this->containerOrder[i].GetNumberOf();
				for (register int j = 0; j < this->containerCar.getSize(); j++)
				{
					if (this->containerCar[j].GetCode() == this->containerOrder[i].GetCarCode())
						counterDevice[j] += this->containerCar[j].GetNumberOf();
				}
				for (register int k = 0; k < this->containerUser.getSize(); k++)
				{
					if (this->containerUser[k].getLogin() == this->containerOrder[i].getLoginManager())
						counterUser[k] += findCar(this->containerOrder[i].GetCarCode()).GetPrice() * this->containerOrder[i].GetNumberOf();
				}
			}
		}
		if (counter > 0)
		{
			cout << "|===================================================================================================================================|\n";
			cout << "����� ������� �� �����(USD):" << sum << endl << endl;
			int index1 = counterDevice.findMax();
			cout << "�������� ����������� ������ � ��������:" << endl;
			cout << "���: " << this->containerCar[index1].GetCode() << endl;
			cout << "�����: " << this->containerCar[index1].GetBrand() << endl;
			cout << "������: " << this->containerCar[index1].GetModel() << endl;
			cout << "���������(USD): " << this->containerCar[index1].GetPrice() << endl << endl;
			int index2 = counterUser.findMax();
			cout << "������ �������� ������ (������ ������� �� " << counterUser[index2] << " USD): " << endl;
			cout << "�����: " << this->containerUser[index2].getLogin() << endl;
			cout << "���: " << this->containerUser[index2].getFIO().OutputAllInfo() << endl << endl;
			DataProcessing::customizationGrey("\n������� �������� ����� � ����? (1 - �� / 2- ���): ");
			int controller = DataProcessing::checkInterval(1, 2);
			if (controller == 1) {
				writeReportFile(month, year);
			}
		}
		else cout << "� ������ ������ �� ���� �������������� �������!!!" << endl;
		system("pause");
	}
	catch (int) { DataProcessing::OutputErrors("�� ������� ������� ��� ������������ ������"); system("pause"); }
}
void UseCases::writeReportFile(int month, int year)
{
	ofstream fout(FILE_REPORTS, ios_base::app);
	int counter = 0; double sum = 0.0;
	Container<int> counterDevice(this->containerCar.getSize(), 0);
	Container<double> counterUser(this->containerUser.getSize(), 0.0);
	for (register int i = 0; i < this->containerOrder.getSize(); i++)
	{
		if (this->containerOrder[i].GetDate().GetMonth() == month && this->containerOrder[i].GetDate().GetYear() == year)
		{
			counter++;
			if (counter == 1) {
				fout << "\t\t\t\t\t      ~����� �� ������ (����� - " << to_string(month) << ", ��� - " << to_string(year) << ")~";
				fout << "\n|===================================================================================================================================|"
					<< "\n|                                                       ~������������� ������~                                                      |"
					<< "\n|===================================================================================================================================|"
					<< "\n| � |��� ������|����� ���������|  ��� ���������  |��� ������| �������� ����� | �������� ������ | ����� ���� | ���-�� | ���� ������� |"
					<< "\n|===================================================================================================================================|\n";
			}
			cout.setf(ios::left);
			fout << "|" << setw(3) << counter << "|" << setw(10) << this->containerOrder[i].GetCode() << "|"
				<< setw(15) << this->containerOrder[i].getLoginManager() << "|"
				<< setw(17) << findUser(this->containerOrder[i].getLoginManager()).getFIO().OutputAllInfo() << "|"
				<< setw(10) << this->containerOrder[i].GetCarCode() << "|"
				<< setw(16) << findCar(this->containerOrder[i].GetCarCode()).GetBrand() << "|"
				<< setw(17) << findCar(this->containerOrder[i].GetCarCode()).GetModel() << "|"
				<< setw(12) << findCar(this->containerOrder[i].GetCarCode()).GetPrice() * this->containerOrder[i].GetNumberOf() << "|"
				<< setw(8) << this->containerOrder[i].GetNumberOf() << "|" << setw(14) << this->containerOrder[i].GetDate().OutputAllInfo() << "|" << endl;
			sum += findCar(this->containerOrder[i].GetCarCode()).GetPrice() * this->containerOrder[i].GetNumberOf();
			for (register int j = 0; j < this->containerCar.getSize(); j++)
			{
				if (this->containerCar[j].GetCode() == this->containerOrder[i].GetCarCode())
					counterDevice[j] += this->containerCar[j].GetNumberOf();
			}
			for (register int k = 0; k < this->containerUser.getSize(); k++)
			{
				if (this->containerUser[k].getLogin() == this->containerOrder[i].getLoginManager())
					counterUser[k] += findCar(this->containerOrder[i].GetCarCode()).GetPrice() * this->containerOrder[i].GetNumberOf();
			}
		}
	}
	if (counter > 0)
	{
		fout << "|===================================================================================================================================|\n";
		fout << "����� ������� �� �����(USD):" << sum << endl << endl;
		int index1 = counterDevice.findMax();
		fout << "�������� ����������� ������ � ��������:" << endl;
		fout << "���: " << this->containerCar[index1].GetCode() << endl;
		fout << "�����: " << this->containerCar[index1].GetBrand() << endl;
		fout << "������: " << this->containerCar[index1].GetModel() << endl;
		fout << "���������(USD): " << this->containerCar[index1].GetPrice() << endl << endl;
		int index2 = counterUser.findMax();
		fout << "������ �������� ������ (������ ������� �� " << counterUser[index2] << " USD): " << endl;
		fout << "�����: " << this->containerUser[index2].getLogin() << endl;
		fout << "���: " << this->containerUser[index2].getFIO().OutputAllInfo() << endl << endl;
		DataProcessing::customizationGreen("����� ������� ������� � ����");
	}
	fout.close();
}

void UseCases::UndoLastAction(const string FILE_NAME)
{
	DataProcessing::customizationGrey("����������� ������? (1 - �� / 2- ���): ");
	int controller = DataProcessing::checkInterval(1, 2);
	bool flag = true;
	if (controller == 1)
	{
		switch (mp[FILE_NAME])
		{
		case 1:
		{
			if (this->BackUpcontainerUser.getSize()) {
				this->containerUser = this->BackUpcontainerUser;
				writeUsers();
			}
			else
				flag = false;
			break;
		}
		case 2:
		{
			if (this->BackUpcontainerCar.getSize()) {
				this->containerCar = this->BackUpcontainerCar;
				writeCars();
			}
			else
				flag = false;
			break;
		}
		case 3:
		{
			if (this->BackUpcontainerOrder.getSize()) {
				this->containerOrder = this->BackUpcontainerOrder;
				writeOrder();
			}
			else
				flag = false;
			break;
		}
		}

		if (flag)
			DataProcessing::customizationGreen("��� �������");
		else
			DataProcessing::OutputErrors("�� ��������� ������� ����");

		system("pause");
	}
}

void UseCases::ClearAllBackUp()
{
	this->BackUpcontainerCar.clear();
	this->BackUpcontainerOrder.clear();
	this->BackUpcontainerUser.clear();
}
