#include "Input.h"

#include <iostream>

Input::Input()
{
	// assign the console handle
	m_ConsoleHandle = GetStdHandle(STD_INPUT_HANDLE);

	// set the console mode to receive input from keyboard and mouse
	GetConsoleMode(m_ConsoleHandle, &m_OldConsoleMode); // save the old mode
	DWORD consoleMode = m_OldConsoleMode | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(m_ConsoleHandle, consoleMode);
}

Input::~Input()
{
	// revert back to old console mode
	SetConsoleMode(m_ConsoleHandle, m_OldConsoleMode);
}

int Input::PollEvents()
{
	// get all events from the event queue and mark them as read
	ReadConsoleInput(m_ConsoleHandle, m_InputRecordBuffer, 128, &m_NumInputRecords);
	return m_NumInputRecords;
}

int Input::GetEventQueueLength()
{
	GetNumberOfConsoleInputEvents(m_ConsoleHandle, &m_NumInputRecords);
	return m_NumInputRecords;
}
