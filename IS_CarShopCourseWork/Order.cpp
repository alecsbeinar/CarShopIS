#include "Order.h"

void Order::SetCode(Container<Order>& obj)
{
	int controller;
	string code;
	do {
		controller = 0;
		DataProcessing::checkCode(code, 5);
		for (int i = 0; i < obj.getSize(); i++)
		{
			if (code == obj[i].code)
			{
				DataProcessing::OutputErrors("Данный код занят!");

				controller = -1;
				break;
			}
		}
	} while (controller == -1);
	this->code = code;
}

void Order::SetInfo(const string code, const string CarCode, const string loginManager, const Date& date, const int numberOf)
{
	this->code = code;
	this->CarCode = CarCode;
	this->loginManager = loginManager;
	this->date = date;
	this->numberOf = numberOf;
}

bool Order::operator<(const Order& obj)
{
	if (this->date < obj.date)
		return true;
	else return false;
}

istream& operator>>(istream& stream, Order& obj)
{
	string code, CarCode, loginManager;
	Date date;
	int numberOf;

	if (stream >> code >> CarCode >> loginManager >> date >> numberOf)
		obj.SetInfo(code, CarCode, loginManager, date, numberOf);
	return stream;
}

ostream& operator<<(ostream& stream, const Order& obj)
{
	stream << obj.code << " " << obj.CarCode << " " << obj.loginManager << " " << obj.date << " " << obj.numberOf;
	return stream;
}
