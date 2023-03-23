#pragma once
#include <iostream>
#include <string>
using namespace std;

class MyException : public exception
{
public:
	MyException(const char* msg, string value) : exception(msg)
	{
		this->value = value;
	}

	string GetValueState()
	{
		return value;
	}

private:
	string value;
};