#include "Store.h"
#include "Menu.h"

void Store::setInfo()
{
	system("cls");
	DataProcessing::customizationBlue("������� ������ � ��������");
	DataProcessing::customizationGrey("�������� ��������: "); setName();
	cout << "�����" << endl; setAdd();
	cout << "��� ���������" << endl; setDirectorFIO();
	cout << "���� ��������" << endl; setOpeningDate();

}
void Store::outputInfo()
{
	DataProcessing::customizationBlue("���������� �� ������������� ��������");
	cout << "�������� ��������: \"" << this->name << "\"" << endl;
	cout << "���������������: " << this->address.OutputAllInfo() << endl;
	cout << "��� ���������: " << this->directorFIO.OutputAllInfo() << endl;
	cout << "���� ��������: " << this->openingDate.OutputAllInfo() << endl;
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
			string name_menu = "������ ��������, �������� ������ ��� ���������";
			vector<string> points_menu = { "��������: " + string(this->name), "���������������: " + this->address.OutputAllInfo(), "��� ���������: " + this->directorFIO.OutputAllInfo(), "���� ��������: " + this->openingDate.OutputAllInfo() };

			switch (menu::chooseMenu(points_menu, name_menu))
			{
			case 1:
				DataProcessing::customizationGrey("������� ����� ��������: "); setName();
				writeInfo();
				DataProcessing::customizationGreen("�������� �������� ������� ��������!");
				system("pause");
				break;

			case 2:
				cout << "������� ����� ������" << endl; setAdd();
				writeInfo();
				DataProcessing::customizationGreen("������ �������� ������� �����!");
				system("pause");
				break;
			case 3:
				cout << "������� ��� ������ ���������" << endl; setDirectorFIO();
				writeInfo();
				DataProcessing::customizationGreen("��� ��������� ������� ��������!");
				system("pause");
				break;
			case 4:
				cout << "������� ������ ���� ��������" << endl; setOpeningDate();
				writeInfo();
				DataProcessing::customizationGreen("���� �������� ������� ��������!");
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
		DataProcessing::OutputErrors("�������� ������ ��� �������� ������ ���������!");
		system("pause");
	}
}

void Store::UndoLastAction(Store& SaveStore)
{
	DataProcessing::customizationGrey("����������� ������? (1 - �� / 2- ���): ");
	int controller = DataProcessing::checkInterval(1, 2);
	if (controller == 1)
	{
		if (Equel(*this, SaveStore))
			DataProcessing::OutputErrors("�� ��������� ������� ����");
		else
		{
			SaveStore.writeInfo();
			readData();
			DataProcessing::customizationGreen("��� �������");
		}
		system("pause");
	}
}

