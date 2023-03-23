#include "ProcessingData.h"


void DataProcessing::checkCode(string& str, int lenth)
{
	int controller;
	string BufForWriting;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	do {
		controller = 0;
		string str = "Введите код (";
		str += to_string(lenth);
		str += " цифр): ";
		customizationGrey(str);
		getline(cin, BufForWriting);
		if (BufForWriting.size() == lenth)
		{
			for (register int i = 0; BufForWriting[i] != '\0'; i++)
			{
				if (!isdigit(BufForWriting[i]))
				{
					DataProcessing::OutputErrors("Использован запрещенный символ!");
					controller = -1;
					break;
				}
			}
		}
		else
		{
			string error = "Длина должна быть " + to_string(lenth) + " символов!";
			DataProcessing::OutputErrors(error);
			controller = -1;
		}
	} while (controller == -1);
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	str = BufForWriting;
}

int DataProcessing::enterInt()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	int value, counter = 0;
	char* BufForWriting = new char[256];
	cin.clear();
	cin.getline(BufForWriting, 256, '\n');
	for (int i = 0; BufForWriting[i] != '\0'; i++)
		if (isdigit(BufForWriting[i]))
			counter++;
	if (strlen(BufForWriting) != counter ||
		(BufForWriting[0] == '0' && strlen(BufForWriting) > 1)) // в числе первый символ не ноль
		value = -1;
	else value = atoi(BufForWriting);
	delete[] BufForWriting;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	return value;
}
int DataProcessing::checkInterval(int min, int max)
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	int value;
	value = enterInt();
	while (value < min || value > max)
	{
		string str = "Число должно быть от ";
		str += to_string(min);
		str += " до ";
		str += to_string(max);
		DataProcessing::OutputErrors(str);
		value = enterInt();
	}
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	return value;
}
double DataProcessing::enterDouble()
{
	while (true)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		int controller1 = 0, controller2 = 0;
		double value;
		char* BufForWriting = new char[100];
		try
		{
			cin.clear(); cin.getline(BufForWriting, 100, '\n');
			for (int i = 0; BufForWriting[i] != '\0'; i++)
			{
				if (isdigit(BufForWriting[i]))
					controller1++;
				if (BufForWriting[i] == ',')
					controller2++;
			}
			if (strlen(BufForWriting) != (controller1 + controller2) ||
				(BufForWriting[0] == '0' && BufForWriting[1] != ',') || // если первый 0, следующая должна быть ,
				(BufForWriting[0] == ',') || 
				controller2 > 1 || // , должна быть одна
				strlen(BufForWriting) == 0)
			{
				throw MyException("Ошибка ввода, повторите ввод: ", typeid(value).name());
			}
			else value = atof(BufForWriting);
		}
		catch (MyException& ex)
		{
			DataProcessing::OutputErrors("[Тип должен быть " + ex.GetValueState() + "]");
			DataProcessing::OutputErrors(ex.what());
			continue;
		}
		delete[] BufForWriting;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		return value;
	}
}
double DataProcessing::checkInterval(double min, double max)
{
	double value;
	while (true)
	{
		value = DataProcessing::enterDouble();
		if (value < min || value > max) {
			string str = "Число должно быть от " + to_string(min) + " до " + to_string(max);
			DataProcessing::OutputErrors(str);
		}
		else
			break;
	}
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	return value;
}

void DataProcessing::OutputErrors(string error)
{
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << error << endl;
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void DataProcessing::customizationBlue(string str)
{
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << str << endl;
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void DataProcessing::customizationGreen(string str)
{
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << str << endl;
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void DataProcessing::customizationGrey(string str)
{
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << str;
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

string DataProcessing::enterPasswordWithStars()
{
	string password;
	char c;

	while (true) {
		int i = 0;
		while ((c = _getch()) != 13) // 13 - код клавиши enter
		{
			if (c == 8) { // 8 - код клавиши backspace
				if (i == 0)
					continue;
				cout << (char)8 << ' ' << (char)8;
				if (!password.empty())
					password.pop_back();
				i--;
				continue;
			}
			password += c;
			_putch('*');
			i++;
		}
		if (i < 5 || i>11) {
			DataProcessing::OutputErrors("\nПароль должен быть больше 4 символов и меньше 11");
			customizationGrey("Введите пароль: ");
			password = "";
		}
		else
			break;
	}
	return password;

}

string DataProcessing::getSha1(const std::string& p_arg)
{
	boost::uuids::detail::sha1 sha1;
	sha1.process_bytes(p_arg.data(), p_arg.size());
	unsigned hash[5] = { 0 };
	sha1.get_digest(hash);
	char buf[41] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		sprintf(buf + (i << 3), "%08x", hash[i]);
	}
	return string(buf);
}
string DataProcessing::getSalt()
{
	boost::uuids::random_generator gen;
	boost::uuids::uuid salt = gen();
	//remove the '-' character  
	std::string ssalt = boost::uuids::to_string(salt);
	ssalt.erase(std::remove(ssalt.begin(), ssalt.end(), '-'), ssalt.end());
	return ssalt;
}

