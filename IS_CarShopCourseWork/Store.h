#pragma once
#include "BasicData.h"
#include <fstream>

const string FILE_STORE = "Store.txt";

// Магазин
class Store
{
private:

	string name; // Название
	Address address; // Адрес
	FullName directorFIO; // ФИО директора
	Date openingDate; // Дата открытия

public:

	Store() {
		name = "";
	};
	void setName() { getline(cin, this->name); } // Установка имя
	void setAdd() { this->address.SetInfo(); } // Установка адреса
	void setDirectorFIO() { this->directorFIO.SetInfo(); } // Установа ФИО директора
	void setOpeningDate() { this->openingDate.SetInfo(); } // Установка даты открытия

	string getName() { return this->name; } // Возврат названия

	void setInfo(); // Установка данных
	void outputInfo(); // Вывод информации
	void readData(); // Считывание из файла данных
	void writeInfo(); // Запис данных в файл
	void editInfo(int user_id); // Изменение данных

	void UndoLastAction(Store& SaveStore);

	friend bool Equel(Store& ob, const Store& obj) { return ob.name == obj.name && ob.address == obj.address && ob.directorFIO == obj.directorFIO && ob.openingDate == obj.openingDate; }
};

