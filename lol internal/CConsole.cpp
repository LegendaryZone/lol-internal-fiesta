#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "CConsole.h"

using namespace std;

void CConsole::startConsole()
{
	AllocConsole();                                 // Alloc memory and create console  

	HWND hwnd = ::GetConsoleWindow();
	if (hwnd != NULL)
	{
		HMENU hMenu = ::GetSystemMenu(hwnd, FALSE);
		if (hMenu != NULL)
		{
			DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
			DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
		}
	}

	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);   // ----------------------------------------------
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);  //  Make iostream library use our console handle
														// ----------------------------------------------
	SetConsoleTitleA("Konzolka");   // Set console name to a custom one
}

void CConsole::stopConsole()
{
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);
	FreeConsole();  // Free allocated memory and remove console
}
