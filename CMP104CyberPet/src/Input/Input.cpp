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

void Input::HandleEvents()
{
	// retrieve events from the buffer
	PollEvents();

	// iterate through each event
	for (int i = 0; i < m_NumInputRecords; i++)
	{
		switch (m_InputRecordBuffer[i].EventType)
		{
		case KEY_EVENT:						if (m_KeyEventFunc != nullptr) m_KeyEventFunc(m_InputRecordBuffer[i].Event.KeyEvent); break;
		case MOUSE_EVENT:					if (m_MouseEventFunc != nullptr) m_MouseEventFunc(m_InputRecordBuffer[i].Event.MouseEvent); break;
		case WINDOW_BUFFER_SIZE_EVENT:		if (m_WindowResizeFunc != nullptr) m_WindowResizeFunc(m_InputRecordBuffer[i].Event.WindowBufferSizeEvent); break;
		case MENU_EVENT:					if (m_MenuEventFunc != nullptr) m_MenuEventFunc(m_InputRecordBuffer[i].Event.MenuEvent); break;
		case FOCUS_EVENT:					if (m_FocusEventFunc != nullptr) m_FocusEventFunc(m_InputRecordBuffer[i].Event.FocusEvent); break;
		}
	}
}

int Input::GetEventQueueLength()
{
	GetNumberOfConsoleInputEvents(m_ConsoleHandle, &m_NumInputRecords);
	return m_NumInputRecords;
}
