#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <Psapi.h>
#include <cstdlib>

typedef unsigned long u32;

HANDLE WindowHandle = 0x0;

//DWORD BaseAddress = xxx;
DWORD livesAddr = BaseAddress + 0x1C;
DWORD levelAddr = BaseAddress + 0x34;

//DWORD procID = xxx;

u32 level;
u32 money = 21474800;
u32 lives = 21474800;

int LevelTeleport()
{
	WindowHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	if (WriteProcessMemory(WindowHandle, (LPVOID)levelAddr, &level, sizeof(DWORD), NULL) == 0)
	{
		return 0;
	}
	std::cout << "[BTD] Sent DWORD " << level << " to " << levelAddr << std::endl;
	CloseHandle(WindowHandle);
	return 1;
}

int WPMWrite()
{
	WindowHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
	if (WriteProcessMemory(WindowHandle, (LPVOID)BaseAddress, &money, sizeof(DWORD), NULL) == 0)
	{
		return 0;
	}

	if (WriteProcessMemory(WindowHandle, (LPVOID)livesAddr, &lives, sizeof(DWORD), NULL) == 0)
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
		std::cout << "[BTD] Failed to write to memory." << std::endl;
		return NULL;
	}
	return buffer;
}

void Inject()
{
	int spaceCounter = 0;
	while (true)
	{
		std::cout << "BTD3 Memory Hacker" << std::endl;
		std::cout << "==================" << std::endl;
		std::cout << "[BTD] Level: " << RPMRead<int>(levelAddr) << std::endl;
		std::cout << "[BTD] Money: $" << RPMRead<int>(BaseAddress) << std::endl;
		std::cout << "[BTD] Lives: " << RPMRead<int>(livesAddr) << std::endl;
		if (spaceCounter > 0 && spaceCounter < 2000)
		{
			std::cout << "[BTD] Sent DWORD 0x147ADF0 to " << livesAddr << std::endl;
			std::cout << "[BTD] Sent DWORD 0x147ADF0 to " << BaseAddress;
			spaceCounter++;
		}
		
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (WPMWrite() == 1)
			{
				std::cout << "[BTD] Sent DWORD 0x147ADF0 to " << livesAddr << std::endl;
				std::cout << "[BTD] Sent DWORD 0x147ADF0 to " << BaseAddress;
				spaceCounter = 1;
			}
			else
			{
				std::cout << "[BTD] Failed to write to memory!" << std::endl;
			}
			
		}
		Sleep(200);
		system("cls");
	}
}

int main()
{
	std::string input;
	
	SetConsoleTitle(_T("BTD3 Memory Hacker"));
	std::cout << "BTD3 Memory Hacker" << std::endl;
	std::cout << "==================" << std::endl;
	std::cout << "Level: " << RPMRead<int>(levelAddr) << std::endl;
	std::cout << "Money: $" << RPMRead<int>(BaseAddress) << std::endl;
	std::cout << "Lives: " << RPMRead<int>(livesAddr) << std::endl;
	std::cout << "Enter level to teleport to: ";
	std::cin >> input;
	level = std::stoul(input, nullptr, 0);
	LevelTeleport();
	
	Inject();
	system("pause");
	return 0;
}





