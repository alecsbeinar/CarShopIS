#include "Store.h"
#include "Menu.h"

void Store::setInfo()
{
	system("cls");
	DataProcessing::customizationBlue("ВВЕДИТЕ ДАННЫЕ О МАГАЗИНЕ");
	DataProcessing::customizationGrey("Название магазина: "); setName();
	cout << "Адрес" << endl; setAdd();
	cout << "ФИО директора" << endl; setDirectorFIO();
	cout << "Дата открытия" << endl; setOpeningDate();

}
void Store::outputInfo()
{
	DataProcessing::customizationBlue("ИНФОРМАЦИЯ ОБ АВТОМОБИЛЬНОМ МАГАЗИНЕ");
	cout << "Название магазина: \"" << this->name << "\"" << endl;
	cout << "Местонахождение: " << this->address.OutputAllInfo() << endl;
	cout << "ФИО директора: " << this->directorFIO.OutputAllInfo() << endl;
	cout << "Дата открытия: " << this->openingDate.OutputAllInfo() << endl;
}
void Store::readData()
{
	string name;
	Address add;
	FullName directorFIO;
	Date openingDate;
	ifstream fin(FILE_STORE);
	if (fin >> name >> add >> directorFIO >> openingDate)
	{
		replace(name.begin(), name.end(), '_', ' ');

		this->name = name;
		this->address = add;
		this->directorFIO = directorFIO;
		this->openingDate = openingDate;
	}
	else {
		setInfo();
		writeInfo();
	}
}
void Store::writeInfo()
{
	ofstream fout(FILE_STORE, ios_base::trunc);
	string name = this->name;
	replace(name.begin(), name.end(), ' ', '_');
	fout << name << " " << this->address << " " << this->directorFIO << " " << this->openingDate << endl;
	fout.close();
}
void Store::editInfo(int user_id)
{
	if (user_id == 0)
	{
		while (1)
		{
			system("cls");
			string name_menu = "ДАННЫЕ МАГАЗИНА, ВЫБЕРИТЕ ДАННЫЕ ДЛЯ ИЗМЕНЕНИЯ";
			vector<string> points_menu = { "Название: " + string(this->name), "Местонахождение: " + this->address.OutputAllInfo(), "ФИО директора: " + this->directorFIO.OutputAllInfo(), "Дата открытия: " + this->openingDate.OutputAllInfo() };

			switch (menu::chooseMenu(points_menu, name_menu))
			{
			case 1:
				DataProcessing::customizationGrey("Введите новое название: "); setName();
				writeInfo();
				DataProcessing::customizationGreen("Название магазина успешно изменено!");
				system("pause");
				break;

			case 2:
				cout << "Введите новый адресс" << endl; setAdd();
				writeInfo();
				DataProcessing::customizationGreen("Адресс магазина успешно измен!");
				system("pause");
				break;
			case 3:
				cout << "Введите ФИО нового директора" << endl; setDirectorFIO();
				writeInfo();
				DataProcessing::customizationGreen("ФИО директора успешно изменено!");
				system("pause");
				break;
			case 4:
				cout << "Введите другую дату открытия" << endl; setOpeningDate();
				writeInfo();
				DataProcessing::customizationGreen("Дата открытия успешно изменена!");
				system("pause");
				break;
			case -1:
				return;
			default: break;
			}

		}
	}
	else
	{
		system("cls");
		DataProcessing::OutputErrors("Доступно только для главного админа программы!");
		system("pause");
	}
}

void Store::UndoLastAction(Store& SaveStore)
{
	DataProcessing::customizationGrey("Подтвердить отмену? (1 - ДА / 2- НЕТ): ");
	int controller = DataProcessing::checkInterval(1, 2);
	if (controller == 1)
	{
		if (Equel(*this, SaveStore))
			DataProcessing::OutputErrors("Не совершены никакие шаги");
		else
		{
			SaveStore.writeInfo();
			readData();
			DataProcessing::customizationGreen("Шаг отменен");
		}
		system("pause");
	}
}

