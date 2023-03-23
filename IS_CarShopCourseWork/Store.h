#pragma once
#include "BasicData.h"
#include <fstream>

const string FILE_STORE = "Store.txt";

// �������
class Store
{
private:

	string name; // ��������
	Address address; // �����
	FullName directorFIO; // ��� ���������
	Date openingDate; // ���� ��������

public:

	Store() {
		name = "";
	};
	void setName() { getline(cin, this->name); } // ��������� ���
	void setAdd() { this->address.SetInfo(); } // ��������� ������
	void setDirectorFIO() { this->directorFIO.SetInfo(); } // �������� ��� ���������
	void setOpeningDate() { this->openingDate.SetInfo(); } // ��������� ���� ��������

	string getName() { return this->name; } // ������� ��������

	void setInfo(); // ��������� ������
	void outputInfo(); // ����� ����������
	void readData(); // ���������� �� ����� ������
	void writeInfo(); // ����� ������ � ����
	void editInfo(int user_id); // ��������� ������

	void UndoLastAction(Store& SaveStore);

	friend bool Equel(Store& ob, const Store& obj) { return ob.name == obj.name && ob.address == obj.address && ob.directorFIO == obj.directorFIO && ob.openingDate == obj.openingDate; }
};

