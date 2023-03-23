#include "Car.h"

void Car::SetCode(Container<Car>& obj)
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
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
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
}

void Car::SetInfo(const string code, const string brand, const string model, const double price, const int numberOf)
{
	this->brand = brand;
	this->model = model;
	this->code = code;
	this->price = price;
	this->numberOf = numberOf;
}

void Car::OutputInfo()
{
	cout << setw(13) << this->code << "|" << setw(19) << this->brand << "|" << setw(20) << this->model << "|" << setw(20) << this->price << "|" << setw(15) << this->numberOf << "|";
}

bool Car::operator<(const Car& obj)
{
	if (this->price < obj.price)
		return true;
	else return false;
}

istream& operator>>(istream& stream, Car& obj)
{
	string code, model, brand;
	double price;
	int numberOf;
	if (stream >> code >> brand >> model >> price >> numberOf)
	{
		replace(model.begin(), model.end(), '_', ' ');
		replace(brand.begin(), brand.end(), '_', ' ');
	}
		
	obj.SetInfo(code, brand, model, price, numberOf);
	return stream;
}

ostream& operator<<(ostream& stream, const Car& obj)
{
	string brand, model;
	brand = obj.brand;
	model = obj.model;
	replace(brand.begin(), brand.end(), ' ', '_');
	replace(model.begin(), model.end(), ' ', '_');
	stream << obj.code << " " << brand << " " << model << " " << obj.price << " " << obj.numberOf;
	return stream;
}
