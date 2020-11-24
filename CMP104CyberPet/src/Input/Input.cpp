#include "Input.h"

#include <iostream>

Input::Input()
{
	// assign the console handle
	m_ConsoleHandle = GetStdHandle(STD_INPUT_HANDLE);

	// set the console mode to receive input from keyboard and mouse
	GetConsoleMode(m_ConsoleHandle, &m_OldConsoleMode); // save the old mode
	DWORD consoleMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(m_ConsoleHandle, consoleMode);
}

Input::~Input()
{
	// revert back to old console mode
	SetConsoleMode(m_ConsoleHandle, m_OldConsoleMode);
}

int Input::PollEvents()
{
	if (GetEventQueueLength())
	{
		// get all events from the event queue and mark them as read
		ReadConsoleInput(m_ConsoleHandle, m_InputRecordBuffer, 128, &m_NumInputRecords);
		return m_NumInputRecords;
	} 
	else
	{
		return 0;
	}
}

int Input::GetEventQueueLength()
{
	GetNumberOfConsoleInputEvents(m_ConsoleHandle, &m_NumInputRecords);
	return m_NumInputRecords;
}
