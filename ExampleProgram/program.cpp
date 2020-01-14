#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <Windows.h>
#include <stdlib.h>

DWORD procId;

int main()
{
	procId = GetCurrentProcessId();
	int value1 = 100;
	int value2 = 32;
	std::string str1;
	while (true)
	{
		std::cout << "pid: " << procId << std::endl;
		std::cout << "value1: " << value1 << std::endl;
		std::cout << "value2: " << value2 << std::endl;
		std::cout << "value1 address: " << &value1 << std::endl;
		std::cout << "value2 address: " << &value2 << std::endl;
		Sleep(1500);
		system("cls");
	}
	exit(0);
}

