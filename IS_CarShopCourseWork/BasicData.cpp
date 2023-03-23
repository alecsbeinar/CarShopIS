#include "BasicData.h"

void FullName::SetInfo(const string surname, const string name, const string patronymic)
{
	this->name = name;
	this->surname = surname;
	this->patronymic = patronymic;
}
void FullName::SetInfo()
{
	DataProcessing::customizationGrey("Фамилия: "); SetSurname();
	DataProcessing::customizationGrey("Имя: "); SetName();
	DataProcessing::customizationGrey("Отчество: "); SetPatronymic();
}
string FullName::OutputAllInfo()
{
	string full;
	full = this->surname;
	full = full + ' ' + this->name[0] + '.' + this->patronymic[0] + '.';
	this->fullName = full;
	return this->fullName;
}
istream& operator>>(istream& stream, FullName& obj)
{
	string surname, name, patronymic;
	if (stream >> surname >> name >> patronymic)
		obj.SetInfo(surname, name, patronymic);
	return stream;
}
ostream& operator<<(ostream& stream, const FullName& obj)
{
	stream << obj.surname << " " << obj.name << " " << obj.patronymic;
	return stream;
}

void Address::SetInfo(const string city, const string street, const string house)
{
	this->city = city;
	this->street = street;
	this->house = house;
}
void Address::SetInfo()
{
	DataProcessing::customizationGrey("Город: "); SetCity();
	DataProcessing::customizationGrey("Улица: "); SetStreet();
	DataProcessing::customizationGrey("Номер дома: "); SetHouse();
}
string Address::OutputAllInfo()
{
	string full;
	full = "г." + this->city + ", " + this->street + " " + this->house;
	this->fullAddress = full;
	return this->fullAddress;
}
istream& operator>>(istream& stream, Address& obj)
{
	string city, street, house;
	if (stream >> city >> street >> house) {
		replace(city.begin(), city.end(), '_', ' ');
		replace(street.begin(), street.end(), '_', ' ');
		replace(house.begin(), house.end(), '_', ' ');
		obj.SetInfo(city, street, house);
	}

	return stream;
}
ostream& operator<<(ostream& stream, const Address& obj)
{
	string city = obj.city;
	string house = obj.house;
	string street = obj.street;
	replace(city.begin(), city.end(), ' ', '_');
	replace(house.begin(), house.end(), ' ', '_');
	replace(street.begin(), street.end(), ' ', '_');
	stream << city << " " << street << " " << house;
	return stream;
}

void Date::SetInfo()
{
	DataProcessing::customizationGrey("День: "); SetDay();
	DataProcessing::customizationGrey("Месяц: "); SetMonth();
	DataProcessing::customizationGrey("Год: "); SetYear(1950, 2022);
}
string Date::OutputAllInfo()
{
	char date[11];
	char day[3], month[3], year[5];
	strcpy(date, _itoa(this->day, day, 10));
	if (date[1] == '\0')
		date[1] = ' ';
	date[2] = '.'; date[3] = '\0';
	strcat(date, _itoa(this->month, month, 10));
	if (date[4] == '\0')
		date[4] = ' ';
	date[5] = '.'; date[6] = '\0';
	strcat(date, _itoa(this->year, year, 10));
	this->fullDate = date;
	return this->fullDate;
}
void Date::operator=(const Date& obj)
{
	this->day = obj.day;
	this->month = obj.month;
	this->year = obj.year;
}
bool Date::operator<=(const Date& obj)
{
	if ((this->year < obj.year) ||
		(this->year == obj.year && this->month < obj.month) ||
		(this->year == obj.year && this->month == obj.month && this->day <= obj.day)) {
		return true;
	}
	else return false;
}
bool Date::operator>=(const Date& obj)
{
	if ((this->year > obj.year) ||
		(this->year == obj.year && this->month > obj.month) ||
		(this->year == obj.year && this->month == obj.month && this->day >= obj.day)) {
		return true;
	}
	else return false;
}
bool Date::operator<(const Date& obj)
{
	if ((this->year < obj.year) ||
		(this->year == obj.year && this->month < obj.month) ||
		(this->year == obj.year && this->month == obj.month && this->day < obj.day)) {
		return true;
	}
	else return false;
}
bool Date::operator==(const Date& obj)
{
	if (obj.year == this->year && obj.month == this->month && obj.day == this->day)
		return true;
	else return false;
}
istream& operator>>(istream& stream, Date& obj)
{
	int day, month, year;
	if (stream >> day >> month >> year)
		obj.SetInfo(day, month, year);
	stream.get();
	return stream;
}
ostream& operator<<(ostream& stream, const Date& obj)
{
	stream << obj.day << " " << obj.month << " " << obj.year;
	return stream;
}