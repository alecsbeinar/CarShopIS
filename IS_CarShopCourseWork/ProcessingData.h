#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include "MyException.h"



extern HANDLE h;
using namespace std;

// ��������� ������
class DataProcessing
{
public:

	static void checkCode(string& str, int lenth); // �������� ����

	static int enterInt(); // ���� int
	static int checkInterval(int min, int max); // ���� int � ��������

	static double enterDouble(); // ���� double
	static double checkInterval(double min, double max); // ���� double � ��������

	static void OutputErrors(string error); // ������������ ������ ������
	static void customizationBlue(string str); // ������������ ������ � ����� ����
	static void customizationGreen(string str); // ������������ ������ � ������� ����
	static void customizationGrey(string str); // ������������ ������ � ����� ����

	static string enterPasswordWithStars(); // ���� ������ �����������

	static string getSha1(const std::string& p_arg); // �����������
	static string getSalt(); // ��������� ����

};