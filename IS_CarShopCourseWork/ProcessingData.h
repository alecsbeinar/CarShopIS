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

// Обработка данных
class DataProcessing
{
public:

	static void checkCode(string& str, int lenth); // Проверка кода

	static int enterInt(); // Ввод int
	static int checkInterval(int min, int max); // Ввод int в пределах

	static double enterDouble(); // Ввод double
	static double checkInterval(double min, double max); // Ввод double в пределах

	static void OutputErrors(string error); // Кастомизация вывода ошибок
	static void customizationBlue(string str); // Кастомизация вывода в синий цвет
	static void customizationGreen(string str); // Кастомизация вывода в зеленый цвет
	static void customizationGrey(string str); // Кастомизация вывода в серый цвет

	static string enterPasswordWithStars(); // Ввод пароля звездочками

	static string getSha1(const std::string& p_arg); // Хеширование
	static string getSalt(); // Генерация соли

};