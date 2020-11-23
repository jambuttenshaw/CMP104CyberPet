#pragma once

#include <windows.h>

class Input
{
public:
	Input();
	~Input();

private:
	HANDLE m_ConsoleHandle = nullptr;

	// save the old console mode so we can revert back upon program end
	DWORD m_OldConsoleMode = 0;
};

