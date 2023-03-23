#include "User.h"

void User::setLogin(Container<User>& obj)
{
	string new_login;
	while (true) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		DataProcessing::customizationGrey("������� �����: ");
		int prov = 0;
		getline(cin, new_login);
		// �������� �� ������������ �����
		for (int i = 0; i < new_login.size(); i++) {
			if ((new_login[i] < 'a' || new_login[i] > 'z') && (new_login[i] < 'A' || new_login[i] > 'Z') && (new_login[i] < '0' || new_login[i] > '9')) {
				prov = 1;
			}
		}
		if (new_login.size() < 4)
		{
			DataProcessing::OutputErrors("����� ������ ���� ������� 4 ��������, ��������� ����");
			continue;
		}
		//�������� �� �������� ������
		for (int i = 0; i < obj.getSize(); i++) {
			if (new_login == obj[i].login) prov = 3;
		}

		if (prov == 3) {

			DataProcessing::OutputErrors("����� ����� ��� ����������, ��������� ����");

		}
		else
			if (prov == 0) { this->login = new_login; return; }
			else {
				DataProcessing::OutputErrors("����� ����� ��������� ����� ���������� �������� � �����, ��������� ����");
			}
	}

}

void User::setPassword()
{
	string pass;
	while (true) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		DataProcessing::customizationGrey("������� ������: ");
		int prov = 0, kolchi = 0, kolsym = 0;
		getline(cin, pass);
		// �������� �� ������������ �����
		for (int i = 0; i < pass.size(); i++) {
			if ((pass[i] < 'a' || pass[i] > 'z') && (pass[i] < 'A' || pass[i] > 'Z') && (pass[i] < '0' || pass[i] > '9')) {
				prov = 1;
			}
			if ((pass[i] >= 'a' && pass[i] <= 'z') || (pass[i] >= 'A' && pass[i] <= 'Z')) {
				kolsym++;
			}
			if (pass[i] >= '0' && pass[i] <= '9') {
				kolchi++;
			}
		}
		if (prov == 0 && kolchi >= 1 && pass.size() > 4 && kolsym >= 1) {
			this->salt = DataProcessing::getSalt();
			this->salted_hash_password = DataProcessing::getSha1(pass + salt);
			return;
		}
		else {
			DataProcessing::OutputErrors("������ ������ �������� �� ���� � ��������� ���� � ���� ������ 4 ��������, ��������� ����");
		}
	}
}
void User::setInfo(const string status, const string login, const string password, const string salt)
{
	this->status = status;
	this->login = login;
	this->salted_hash_password = password;
	this->salt = salt;
}
void User::setInfo(Container<User>& obj)
{
	system("cls");
	DataProcessing::customizationBlue("����������� ������ ������������");
	cout << "���" << endl; Human::setFIO();
	cout << "���� ��������" << endl; Human::setBirthday();
	Human::setNumberTelephone();
	setLogin(obj);
	setPassword();
}

void User::outputInfo()
{
	cout << setw(16) << this->login << "|" << setw(14) << this->status << "|";
	Human::outputInfo();
}

bool User::operator<(User& obj)
{
	if (this->getBirthday() < obj.getBirthday())
		return true;
	else return false;
}

istream& operator>>(istream& stream, User& obj)
{
	string status;
	string login, password, salt, number_telephone;
	FullName FIO; Date birth;
	if (stream >> status >> login >> password >> salt >> FIO >> birth >> number_telephone)
	{
		obj.User::setInfo(status, login, password, salt);
		obj.Human::setInfo(FIO, birth, number_telephone);
	}
	return stream;
}
ostream& operator<<(ostream& stream, User& obj)
{
	stream << obj.getStatus() << " " << obj.getLogin() << " " << obj.getPassword() << " " << obj.getSalt()
		<< " " << obj.Human::getFIO() << " " << obj.Human::getBirthday() << " " << obj.Human::getNumberTelephone();
	return stream;
}

void Human::setNumberTelephone()
{
	while (true) {
		bool flag = false;
		string number_teleph;
		DataProcessing::customizationGrey("������� ����� �������� (+375 __ _______): ");
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> number_teleph;
		if (number_teleph[0] != '+' || number_teleph[1] != '3' || number_teleph[2] != '7' || number_teleph[3] != '5') {
			DataProcessing::OutputErrors("����� �������� ������ ���������� � \"+375\", ���������� ������ ��� ���");
			continue;
		}
		if (number_teleph.size() != 13) {
			DataProcessing::OutputErrors("����� �������� ������ ���� ������ � 13 ��������, ���������� ������ ��� ���");
			continue;
		}
		for (int i = 1; i < number_teleph.size(); i++) {
			if (number_teleph[i] < '0' || number_teleph[i]>'9')
				flag = true;
		}
		if (flag) {
			DataProcessing::OutputErrors("����� �������� ������ �������� �� ����, ���������� ������ ��� ���");
			continue;
		}
		this->number_telephone = number_teleph;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		break;
	}
}
void Human::setInfo(const FullName& FIO, const Date& birth, string number_telephone)
{
	this->FIO = FIO;
	this->birthday = birth;
	this->number_telephone = number_telephone;
}
void Human::outputInfo()
{
	cout << setw(18) << this->FIO.OutputAllInfo() << "|"
		<< setw(19) << this->birthday.OutputAllInfo() << "|"
		<< setw(16) << this->number_telephone << "|";
}