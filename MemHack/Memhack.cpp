#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <Psapi.h>
#include <cstdlib>

typedef unsigned long u32;

HANDLE WindowHandle = 0x0;

//These must be changed every time ExampleProgram is run
DWORD value1Addr = 0x00EFF73C;
DWORD value2Addr = 0x00EFF730;
DWORD procID = 7224;

u32 buf; 
u32 buf2; 

std::string GetLastErrorAsString()
{
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string();

	LPSTR msgBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msgBuffer, 0, NULL);
	std::string message(msgBuffer, size);
	LocalFree(msgBuffer);
	return message;
}

void Error()
{
	std::cout << "\n\nFailed to read/write to memory!" << std::endl;
	std::cout << "Error Message: " << std::endl;
	std::string err = GetLastErrorAsString();
	std::cout << err << std::endl;
	std::cin.get();
	std::cin.get();
	exit(EXIT_FAILURE);
}

int WPMWrite()
{
	WindowHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	if (WriteProcessMemory(WindowHandle, (LPVOID)value1Addr, &buf, sizeof(DWORD), NULL) == 0)
	{
		return 0;
	}
	if (WriteProcessMemory(WindowHandle, (LPVOID)value2Addr, &buf2, sizeof(DWORD), NULL) == 0)
	{
		return 0;
	}
	CloseHandle(WindowHandle);
	return 1;
}

template<typename T> T RPMRead(SIZE_T addr)
{
	T buffer;
	WindowHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	if (ReadProcessMemory(WindowHandle, (LPCVOID)addr, &buffer, sizeof(T), NULL) == 0)
	{
		Error();
		return NULL;
	}
	return buffer;
}

int main()
{
	std::string input;

	std::cout << "Memory Hacker V1\n";
	std::cout << "================\n";
	std::cout << "Enter value to inject into Value #1: ";
	std::cin >> input;
	buf = std::stoul(input, nullptr, 0);

	std::cout << "\nEnter value to inject into Value #2: ";
	std::cin >> input;
	buf2 = std::stoul(input, nullptr, 0);
	
	WPMWrite();
	system("cls");

	while (true)
	{
		std::cout << "Memory Hacker V1\n";
		std::cout << "================\n";
		std::cout << "Current PID: " << procID << std::endl;
		std::cout << "Value 1: " << RPMRead<DWORD>(value1Addr) << std::endl;
		std::cout << "Value 2: " << RPMRead<DWORD>(value2Addr) << std::endl;
		std::cout << "\nEnter a new number to inject and reload." << std::endl;
		std::cin >> input;
		buf = std::stoul(input, nullptr, 0);
		buf2 = std::stoul(input, nullptr, 0);
		if (WPMWrite() == 0)
		{
			Error();
		}
		system("cls");
	}

	return 0;
}



