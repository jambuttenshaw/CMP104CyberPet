#include "Input.h"

Input::Input()
{
	// assign the console handle
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// set the console mode to receive input from keyboard and mouse
	GetConsoleMode(m_ConsoleHandle, &m_OldConsoleMode); // save the old mode
	DWORD consoleMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(m_ConsoleHandle, consoleMode);
}

Input::~Input()
{
	// revert back to old console mode
	SetConsoleMode(m_ConsoleHandle, m_OldConsoleMode);
}
