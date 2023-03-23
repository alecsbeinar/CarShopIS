#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <process.h>
#include <vector>
#include "ContainersInfo.h"
#include "User.h"
#include "Store.h"

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13

using namespace std;
extern HANDLE h;

namespace menu
{

	void welcomeMenu(string); // ����� ����������� 
	void completionMenu(); // ����� ���������� ����
	int chooseMenu(vector <string> T, string name_menu); // ������ ������ ����

	void adminMenu(int user_id, Store& stor); // ���� ��������������
	void userMenu(int user_id, Store stor); // ���� ������������
	void managerMenu(int user_id, Store stor); // ���� ���������

	void workWithDataMenu(int user_id); // ���� ������ � �������
	void workWithCarsMenu(); // ���� ������ � ��������
	void workWithOrderMenu(int user_id); // ���� ������ � ��������
	void workWithUsers(int user_id); // ���� ������ � �������� ��������

}