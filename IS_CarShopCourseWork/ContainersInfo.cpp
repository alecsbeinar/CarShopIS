#include "ContainersInfo.h"

int UseCases::authorization(int& user_id)
{
	string login;
	string password;
	int controller = 1;
	while (controller == 1) {
		system("cls");
		DataProcessing::customizationBlue("АВТОРИЗАЦИЯ");
		DataProcessing::customizationGrey("Введите логин: ");
		cin >> login;
		DataProcessing::customizationGrey("Введите пароль: ");
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

		DataProcessing::OutputErrors("\nНеверный логин или пароль!");
		DataProcessing::customizationGrey("Попробовать еще раз? (1 - ДА / 2 - НЕТ): ");
		controller = DataProcessing::checkInterval(1, 2);

	}
}
void UseCases::registration(const string status)
{
	User obj(status);
	obj.setInfo(this->containerUser);
	this->containerUser.add(obj);
	writeUsers();
	DataProcessing::customizationGreen("Регистрация прошла успешно");
	system("pause");
}
void UseCases::outputCapUsers()
{
	cout << "\n|=============================================================================================|"
		<< "\n|                                       ~УЧЕТНЫЕ ЗАПИСИ~                                      |"
		<< "\n|=============================================================================================|"
		<< "\n|  №  |      Логин     |     Роль     |       ФИО        |   День рождения   | Номер телефона |"
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
		DataProcessing::customizationGrey("Введите номер записи, которую хотите удалить (0 - вернуться назад): ");
		choise = controlUser();
		if (choise == 0)
			break;
		else if (choise == 1)
		{
			system("cls");
			DataProcessing::OutputErrors("Нельзя удалить учетную запись под которой вы зашли!");
			system("pause");
		}
		else
		{
			DataProcessing::customizationGrey("Подтвердить удаление? (1 - ДА / 2- НЕТ): ");
			int controller = DataProcessing::checkInterval(1, 2);
			if (controller == 1) {
				this->containerUser.del(choise - 1);
				writeUsers();
				DataProcessing::customizationGreen("Запись успешно удалена");
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
					DataProcessing::OutputErrors("Нельзя удалить данную запись!!!\nДля удаление этого пользователя нужно удалить все его реализованные заказы: ");
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
		vector <string> points_menu = { "Поиск по статусу", "Поиск по логину", "Поиск по фамилии", "Поиск по телефону", "Поиск по дате", "Сортировка по дате", "Назад" };
		string name_menu = "ФИЛЬТРАЦИЯ И СОРТИРОВКА";
		int choise = menu::chooseMenu(points_menu, name_menu);
		if (choise == -1)
			return;
		if (choise == 6)
		{
			Container<User> vecBuf;
			vecBuf = this->containerUser;
			containerUser.sort();
			cout << "\t\t\t\t    ~ОТСОРТИРОВАННЫЕ ДАННЫЕ~";
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
			case 1: DataProcessing::customizationGrey("Введите статус: "); break;
			case 2: DataProcessing::customizationGrey("Введите логин: "); break;
			case 3:	DataProcessing::customizationGrey("Введите фамилию: "); break;
			case 4: DataProcessing::customizationGrey("Введите номер телефона: "); break;
			case 5:
				cout << "\tМинимальное значение" << endl;
				min.SetInfo();
				while (1)
				{
					cout << "\tМаксимальное значение" << endl;
					max.SetInfo();
					if (min <= max)
						break;
					else cout << "Нет такого варианта, попробуйте еще раз!" << endl;
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
						cout << "\t\t\t\t    ~НАЙДЕННЫЕ ПОЛЬЗОВАТЕЛИ~";
						outputCapUsers();
					}
					cout.setf(ios::left);
					cout << "|" << setw(5) << counter << "|"; this->containerUser[i].outputInfo(); cout << endl;
				}
			}
			if (counter > 0)
				cout << "|=============================================================================================|\n";
			if (counter == 0) DataProcessing::OutputErrors("Ничего не найдено!");
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
		string name_menu = "ВАШИ ДАННЫЕ, ВЫБЕРИТЕ ДАННЫЕ ДЛЯ ИЗМЕНЕНИЯ";
		vector<string> points_menu = { "Пароль: ******", "Логин: " + string(this->containerUser[user_id].getLogin()), "ФИО: " + string(this->containerUser[user_id].getFIO().OutputAllInfo()), "Дата рождения: " + string(this->containerUser[user_id].getBirthday().OutputAllInfo()), "Номер телефона: " + string(this->containerUser[user_id].getNumberTelephone()) };

		switch (menu::chooseMenu(points_menu, name_menu))
		{
		case 1:
			DataProcessing::customizationGrey("Введите старый пароль: ");
			cin >> old_password;
			if (DataProcessing::getSha1(old_password + containerUser[user_id].getSalt()) == containerUser[user_id].getPassword())
			{
				this->containerUser[user_id].setPassword();
				DataProcessing::customizationGreen("Пароль успешно изменен!\n");
				this->writeUsers();
				system("pause");
			}
			else
			{
				DataProcessing::OutputErrors("Неверный старый пароль!\n");
				system("pause");
			}
			break;

		case 2:
			this->containerUser[user_id].setLogin(this->containerUser);
			DataProcessing::customizationGreen("Логин успешно изменен!\n");
			this->writeUsers();
			system("pause");
			break;
		case 3:
			DataProcessing::customizationBlue("ФИО");
			this->containerUser[user_id].setFIO();
			DataProcessing::customizationGreen("ФИО успешно изменено!\n");
			this->writeUsers();
			system("pause");
			break;
		case 4:
			DataProcessing::customizationBlue("ДАТА РОЖДЕНИЯ");
			this->containerUser[user_id].setBirthday();
			DataProcessing::customizationGreen("Дата рождения успешно изменена!\n");
			system("pause");
			this->writeUsers();
			break;
		case 5:
			this->containerUser[user_id].setNumberTelephone();
			DataProcessing::customizationGreen("Номер телефона успешно изменен!\n");
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
	DataProcessing::customizationBlue("ДОБАВЛЕНИЕ НОВОЙ МАШИНЫ");
	Car obj;
	obj.SetCode(this->containerCar);
	
	DataProcessing::customizationGrey("Марка: "); obj.SetBrand();
	DataProcessing::customizationGrey("Модель: "); obj.SetModel();
	DataProcessing::customizationGrey("Цена(USD): "); obj.SetPrice();
	DataProcessing::customizationGrey("Кол-во(в наличии): "); obj.SetNumberOf();
	this->containerCar.add(obj);
	writeCars();
	DataProcessing::customizationGreen("Товар успешно добавлен");
	system("pause");
}
void UseCases::outputCapCars()
{
	cout << "\n|=================================================================================================|"
		<< "\n|                                        ~ПРОДУКЦИЯ МАГАЗИНА~                                     |"
		<< "\n|=================================================================================================|"
		<< "\n|  №  |     Код     |       Марка       |       Модель       |     Цена(USD)      |   В наличии   |"
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
	else DataProcessing::OutputErrors("Нет записей");
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
			DataProcessing::customizationGrey("Введите номер машины, которую хотите удалить (0 - вернуться назад): ");
			choise = controlCars();
			if (choise == 0)
				break;
			else
			{
				DataProcessing::customizationGrey("Подтвердить удаление? (1 - ДА / 2- НЕТ): ");
				int controller = DataProcessing::checkInterval(1, 2);
				if (controller == 1) {
					this->containerCar.del(choise - 1);
					writeCars();
					DataProcessing::customizationGreen("Машина успешно удален");
					system("pause");
				}

			}
		}
	}
	else { DataProcessing::OutputErrors("Нет записей"); system("pause"); }

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
					DataProcessing::OutputErrors("Нельзя удалить данную запись!!! Для удаление данной записи нужно удалить\nвсе заказы с данным видом продукции: ");
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
			vector<string> points_menu = { "Поиск по коду машины","Поиск по названию машины","Фильтрация по цене","Сортировка по цене", "Назад" };
			string name_menu = "МЕНЮ ПОИСКА И ФИЛЬТРАЦИИ";
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
				case 1: DataProcessing::customizationGrey("Введите код машины: "); cin >> BufForWriting; break;
				case 2: 
				{
					DataProcessing::customizationGrey("Введите марку машины: ");
					cin >> brand;
					DataProcessing::customizationGrey("Введите модель машины: ");
					cin >> model;
					break;
				}
				case 3:
					DataProcessing::customizationGrey("Введите минимальное занчение цены: "); min = DataProcessing::checkInterval(0.00, 1000000.00);
					DataProcessing::customizationGrey("Введите максимальное значение цены: "); max = DataProcessing::checkInterval(min, 1000001.00);
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
							cout << "\t\t\t\t   ~НАЙДЕННЫЕ МАШИНЫ~";
							outputCapCars();
						}

						cout << "|" << setw(5) << counter << "|"; this->containerCar[i].OutputInfo(); cout << endl;

					}

				}

				if (counter == 0)
					DataProcessing::OutputErrors("Ничего не найдено");
				else
					cout << "|=================================================================================================|" << endl;
				system("pause");
			}
		}

	}
	else { DataProcessing::OutputErrors("Нет записей\n"); system("pause"); }

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
			DataProcessing::customizationGrey("Введите номер записи, которую хотите редактировать (0 - вернуться назад): ");
			choise = DataProcessing::checkInterval(0, this->containerCar.getSize());
			if (choise != 0)
			{
				vector <string> points_menu = { "Марка", "Модель", "Цена", "Количество", "Назад" };
				string name_menu = "КРИТЕРИИ РЕДАКТИРОВАНИЯ";
				switch (menu::chooseMenu(points_menu, name_menu))
				{
				case 1:
					system("cls");
					DataProcessing::customizationGrey("Введите новое название марки: ");
					this->containerCar[choise - 1].SetBrand();
					DataProcessing::customizationGreen("Марка успешно изменена");
					system("pause");
					writeCars();
					break;
				case 2:
					system("cls");
					DataProcessing::customizationGrey("Введите новое название модели: ");
					this->containerCar[choise - 1].SetModel();
					DataProcessing::customizationGreen("Модель успешно изменена");
					system("pause");
					writeCars();
					break;
				case 3:
					system("cls");
					DataProcessing::customizationGrey("Введите новую цену(USD): ");
					this->containerCar[choise - 1].SetPrice();
					DataProcessing::customizationGreen("Цена успешно изменена");
					system("pause");
					writeCars();
					break;
				case 4:
					system("cls");
					DataProcessing::customizationGrey("Введите новое количество: ");
					this->containerCar[choise - 1].SetNumberOf();
					DataProcessing::customizationGreen("Количество успешно изменено");
					system("pause");
					writeCars();
					break;
				default: break;
				}
			}
			else break;
		}
	}
	else { DataProcessing::OutputErrors("Нет записей"); system("pause"); }

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
			DataProcessing::customizationBlue("ДОБАВЛЕНИЕ ЗАКАЗА");
			Order obj;
			obj.SetLoginManager(this->containerUser[user_id].getLogin());
			obj.SetCode(this->containerOrder);
			outputAllCars();
			DataProcessing::customizationGrey("Выберите нужную машину: ");
			choise = DataProcessing::checkInterval(1, this->containerCar.getSize());
			if (this->containerCar[choise - 1].GetNumberOf() == 0) {
				DataProcessing::OutputErrors("Данный товар отсутствует в наличии");
				system("pause");
				return;
			}
			obj.SetCarCode(this->containerCar[choise - 1].GetCode());
			DataProcessing::customizationGrey("Кол-во ед. продукции: ");
			obj.SetNumberOf(this->containerCar[choise - 1].GetNumberOf());
			this->containerCar[choise - 1].Decrease(obj.GetNumberOf());
			cout << "Дата продажи" << endl;
			obj.SetDate();
			this->containerOrder.add(obj);
			writeOrder();
			writeCars();
			DataProcessing::customizationGreen("Заказ успешно добавлен");
			system("pause");
		}
		else { system("cls"); DataProcessing::OutputErrors("На складе нет ни одной еденицы продукции"); system("pause"); }
	}

	catch (int) {
		system("cls");
		DataProcessing::OutputErrors("Добавьте хотя бы один вид продукции");
		system("pause");
	}
}
void UseCases::outputCapOrder()
{
	cout << "\n|===================================================================================================================================|"
		<< "\n|                                                      ~РЕАЛИЗОВАННЫЕ ЗАКАЗЫ~                                                       |"
		<< "\n|===================================================================================================================================|"
		<< "\n| № |Код заказа|Логин менеджера|  ФИО менеджера  |Код машины| Название марки | Название модели | Сумма чека | Кол-во | Дата продажи |"
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
		DataProcessing::OutputErrors("Нет записей");
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
			DataProcessing::customizationGrey("Введите номер записи, которую хотите удалить (0 - вернуться назад): ");
			choise = controlOrder(user_id);
			if (choise == 0)
				break;
			else
			{
				DataProcessing::customizationGrey("Подтвердить удаление? (1 - ДА / 2- НЕТ): ");
				int controller = DataProcessing::checkInterval(1, 2);
				if (controller == 1) {
					this->containerOrder.del(choise - 1);
					writeOrder();
					DataProcessing::customizationGreen("Заказ успешно удален");
					system("pause");
					return;
				}
			}
		}
	}
	catch (int) { DataProcessing::OutputErrors("Нет записей"); system("pause"); }
}
int UseCases::controlOrder(int user_id)
{
	int choise;
	do {
		choise = DataProcessing::checkInterval(0, this->containerOrder.getSize());
		if (choise != 0 && user_id != 0 && this->containerOrder[choise - 1].getLoginManager() != this->containerUser[user_id].getLogin())
		{
			DataProcessing::OutputErrors("Реализованные заказы других менеджеров может удалять/редактировать только главный админ программы!");
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
			vector <string> points_menu = { "Поиск по коду заказа", "Поиск по коду продукта", "Поиск по фамилии менеджера", "Фильтрация по дате реализации заказа","Сортировка по дате реализации заказа", "Назад" };
			string name_menu = "КРИТЕРИИ ПОИСКА И ФИЛЬТРАЦИИ";
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
				case 1: DataProcessing::customizationGrey("Введите код заказа: "); cin >> BufForWriting; break;
				case 2:
					outputAllCars();
					DataProcessing::customizationGrey("Выберите нужный продукт: ");
					BufForWriting = this->containerCar[DataProcessing::checkInterval(1, this->containerCar.getSize()) - 1].GetCode();
					break;
				case 3: DataProcessing::customizationGrey("Фамилия менеджера: "); cin >> BufForWriting; break;
				case 4:
					DataProcessing::customizationGrey("Минимальное значение: ");
					min.SetInfo();
					while (1)
					{
						DataProcessing::customizationGrey("Максимальное значение: ");
						max.SetInfo();
						if (min <= max)
							break;
						else DataProcessing::OutputErrors("Нет такого варианта, попробуйте еще раз!");
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
							cout << "\t\t\t\t\t          ~НАЙДЕННЫЕ ЗАКАЗЫ~";
							outputCapOrder();
						}
						cout << "|" << setw(3) << counter << "|"; outputOneOrder(i); cout << endl;

					}
				}

				if (counter == 0)
					DataProcessing::OutputErrors("Ничего не найдено");
				else
					cout << "|===================================================================================================================================|\n";
				system("pause");
			}
		}

	}
	catch (int) { DataProcessing::OutputErrors("Нет записей"); system("pause"); }
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
			DataProcessing::customizationGrey("Введите номер записи, которую хотите редактировать (0 - вернуться назад): ");
			choise = controlOrder(user_id);
			if (choise != 0)
			{
				vector<string> points_menu = { "Продукт", "Количество единиц продукции", "Дата реализации заказа", "Назад" };
				string name_menu = "КРИТЕРИИ РЕДАКТИРОВАНИЯ";
				switch (menu::chooseMenu(points_menu, name_menu))
				{
				case 1:
				{
					findCar(this->containerOrder[choise - 1].GetCarCode()).Increase(this->containerOrder[choise - 1].GetNumberOf());
					outputAllCars();
					DataProcessing::customizationGrey("Выберите машину: ");
					choiseDevice = DataProcessing::checkInterval(1, this->containerCar.getSize());
					if (this->containerCar[choiseDevice - 1].GetNumberOf() == 0) {
						DataProcessing::OutputErrors("Данный товар отсутствует в наличии");
						system("pause");
						break;
					}
					this->containerOrder[choise - 1].SetCarCode(this->containerCar[choiseDevice - 1].GetCode());
					DataProcessing::customizationGrey("Кол - во ед.продукции: ");
					this->containerOrder[choise - 1].SetNumberOf(this->containerCar[choise - 1].GetNumberOf());
					writeOrder();
					writeCars();
					DataProcessing::customizationGreen("Продукт успешно изменен");
					system("pause");
					break;
				}
				case 2: {
					findCar(this->containerOrder[choise - 1].GetCarCode()).Increase(this->containerOrder[choise - 1].GetNumberOf());
					string str = "Кол-во ед. продукции (имеется ";
					str += to_string(findCar(this->containerOrder[choise - 1].GetCarCode()).GetNumberOf());
					str += " ед.): ";
					DataProcessing::customizationGrey(str);
					this->containerOrder[choise - 1].SetNumberOf(findCar(this->containerOrder[choise - 1].GetCarCode()).GetNumberOf());
					writeOrder();
					writeCars();
					DataProcessing::customizationGreen("Количество успешно изменено");
					system("pause");
					break;
				}

				case 3:
				{
					DataProcessing::customizationBlue("ДАТА РЕАЛИЗАЦИИ");
					this->containerOrder[choise - 1].SetDate();
					writeOrder();
					DataProcessing::customizationGreen("Дата успешно изменена");
					system("pause");
					break;
				}
				default: break;
				}
			}
			else break;
		}
	}
	catch (int) { DataProcessing::OutputErrors("Нет записей"); system("pause"); }
}

void UseCases::report()
{
	try
	{
		if (this->containerOrder.getSize() == 0)
			throw 1;
		int month, year;
		system("cls");
		DataProcessing::customizationBlue("ФОРМИРОВАНИЕ МЕСЯЧНОГО ОТЧЕТА");
		DataProcessing::customizationGrey("Введите месяц(1 - 12): "); month = DataProcessing::checkInterval(1, 12);
		DataProcessing::customizationGrey("Введите год : "); year = DataProcessing::checkInterval(1990, 2022);
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
					cout << "\t\t\t\t\t      ~ОТЧЕТ ЗА ПЕРИОД (месяц - " << to_string(month) << ", год - " << to_string(year) << ")~";
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
			cout << "ОБЩАЯ ВЫРУЧКА ЗА МЕСЯЦ(USD):" << sum << endl << endl;
			int index1 = counterDevice.findMax();
			cout << "НАИБОЛЕЕ ПРОДАВАЕМАЯ МАШИНА В МАГАЗИНЕ:" << endl;
			cout << "Код: " << this->containerCar[index1].GetCode() << endl;
			cout << "Марка: " << this->containerCar[index1].GetBrand() << endl;
			cout << "Модель: " << this->containerCar[index1].GetModel() << endl;
			cout << "Стоймость(USD): " << this->containerCar[index1].GetPrice() << endl << endl;
			int index2 = counterUser.findMax();
			cout << "ЛУЧШИЙ РАБОТНИК МЕСЯЦА (продал товаров на " << counterUser[index2] << " USD): " << endl;
			cout << "Логин: " << this->containerUser[index2].getLogin() << endl;
			cout << "ФИО: " << this->containerUser[index2].getFIO().OutputAllInfo() << endl << endl;
			DataProcessing::customizationGrey("\nЖелаете записать отчет в файл? (1 - ДА / 2- НЕТ): ");
			int controller = DataProcessing::checkInterval(1, 2);
			if (controller == 1) {
				writeReportFile(month, year);
			}
		}
		else cout << "В данном месяце не было реализованнных заказов!!!" << endl;
		system("pause");
	}
	catch (int) { DataProcessing::OutputErrors("Не хватает записей для формирования отчета"); system("pause"); }
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
				fout << "\t\t\t\t\t      ~ОТЧЕТ ЗА ПЕРИОД (месяц - " << to_string(month) << ", год - " << to_string(year) << ")~";
				fout << "\n|===================================================================================================================================|"
					<< "\n|                                                       ~РЕАЛИЗОВАННЫЕ ЗАКАЗЫ~                                                      |"
					<< "\n|===================================================================================================================================|"
					<< "\n| № |Код заказа|Логин менеджера|  ФИО менеджера  |Код машины| Название марки | Название модели | Сумма чека | Кол-во | Дата продажи |"
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
		fout << "ОБЩАЯ ВЫРУЧКА ЗА МЕСЯЦ(USD):" << sum << endl << endl;
		int index1 = counterDevice.findMax();
		fout << "НАИБОЛЕЕ ПРОДАВАЕМАЯ МАШИНА В МАГАЗИНЕ:" << endl;
		fout << "Код: " << this->containerCar[index1].GetCode() << endl;
		fout << "Марка: " << this->containerCar[index1].GetBrand() << endl;
		fout << "Модель: " << this->containerCar[index1].GetModel() << endl;
		fout << "Стоймость(USD): " << this->containerCar[index1].GetPrice() << endl << endl;
		int index2 = counterUser.findMax();
		fout << "ЛУЧШИЙ РАБОТНИК МЕСЯЦА (продал товаров на " << counterUser[index2] << " USD): " << endl;
		fout << "Логин: " << this->containerUser[index2].getLogin() << endl;
		fout << "ФИО: " << this->containerUser[index2].getFIO().OutputAllInfo() << endl << endl;
		DataProcessing::customizationGreen("Отчет успешно записан в файл");
	}
	fout.close();
}

void UseCases::UndoLastAction(const string FILE_NAME)
{
	DataProcessing::customizationGrey("Подтвердить отмену? (1 - ДА / 2- НЕТ): ");
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
			DataProcessing::customizationGreen("Шаг отменен");
		else
			DataProcessing::OutputErrors("Не совершены никакие шаги");

		system("pause");
	}
}

void UseCases::ClearAllBackUp()
{
	this->BackUpcontainerCar.clear();
	this->BackUpcontainerOrder.clear();
	this->BackUpcontainerUser.clear();
}
