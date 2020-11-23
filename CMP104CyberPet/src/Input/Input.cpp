#include "Input.h"

#include <iostream>

Input::Input()
{
	// assign the console handle
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// set the console mode to receive input from keyboard and mouse
	GetConsoleMode(m_ConsoleHandle, &m_OldConsoleMode); // save the old mode
	DWORD consoleMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(m_ConsoleHandle, consoleMode);


	std::vector<INPUT_RECORD> m_InputRecordBuffer(128);
}

void Input::Poll()
{
	ReadConsoleInput(m_ConsoleHandle, &m_InputRecordBuffer[0], 128, &m_NumInputRecords);
	std::cout << "Num events read into buffer: " << m_NumInputRecords << std::endl;
}

Input::~Input()
{
	// revert back to old console mode
	SetConsoleMode(m_ConsoleHandle, m_OldConsoleMode);
}
