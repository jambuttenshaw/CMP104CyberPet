#include "InputAPI.h"

// constructor
InputAPI::InputAPI()
{
	// assign the console handle
	// we want the standard input handle
	m_ConsoleHandle = GetStdHandle(STD_INPUT_HANDLE);

	// set the console mode to receive input from keyboard and mouse

	// save the old mode so we can load it in again later
	GetConsoleMode(m_ConsoleHandle, &m_OldConsoleMode);

	// create the new console mode,
	// we want to enable window and mouse input and nothing else
	DWORD consoleMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	// assign the new console mode to the console
	SetConsoleMode(m_ConsoleHandle, consoleMode);
}

// destructor
InputAPI::~InputAPI()
{
	// revert back to old console mode
	SetConsoleMode(m_ConsoleHandle, m_OldConsoleMode);
}

int InputAPI::PollEvents()
{
	// ReadConsoleInput will wait until the length of the queue is greater than 0
	// before returning from the function
	// but we dont want it holding up our program by waiting for the user to do something
	// so if theres no events to process we just return 0
	if (GetEventQueueLength())
	{
		// get all events from the event queue and mark them as read
		// referenced from
		// https://docs.microsoft.com/en-us/windows/console/readconsoleinput

		// we pass in the console handle, a pointer to the array that we want to event records written in to,
		// the length of the array, and a reference to a variable to hold the number of event records that
		// were actually written
		ReadConsoleInput(m_ConsoleHandle, m_InputRecordBuffer, 128, &m_NumInputRecords);

		// then return the number of events that were actually written
		return m_NumInputRecords;
	} 
	else
	{
		return 0;
	}
}

void InputAPI::HandleEvents()
{
	// first of all retrieve events from the buffer before we work through them
	PollEvents();

	// iterate through each event
	for (unsigned int i = 0; i < m_NumInputRecords; i++)
	{
		// we want to call different event callbacks depending on the type of the event
		// we also need to check that the event callback function is not null; which could happen if an event callback was not assigned
		// we dont want to attempt to invoke null

		// then just pass in the event record into the event callback function and consider it handled
		switch (m_InputRecordBuffer[i].EventType)
		{
		case KEY_EVENT:					
			if (m_KeyEventCallback != nullptr) m_KeyEventCallback(&m_InputRecordBuffer[i].Event.KeyEvent); break;
		case MOUSE_EVENT:				
			if (m_MouseEventCallback != nullptr) m_MouseEventCallback(&m_InputRecordBuffer[i].Event.MouseEvent); break;
		case WINDOW_BUFFER_SIZE_EVENT:	
			if (m_WindowResizeEventCallback != nullptr) m_WindowResizeEventCallback(&m_InputRecordBuffer[i].Event.WindowBufferSizeEvent); break;
		case MENU_EVENT:				
			if (m_MenuEventCallback != nullptr) m_MenuEventCallback(&m_InputRecordBuffer[i].Event.MenuEvent); break;
		case FOCUS_EVENT:				
			if (m_FocusEventCallback != nullptr) m_FocusEventCallback(&m_InputRecordBuffer[i].Event.FocusEvent); break;
		}
	}
}

// gets how many events there are in the windows event queue, but doesn't copy them out or mark them as read
int InputAPI::GetEventQueueLength()
{
	// referenced from
	// https://docs.microsoft.com/en-us/windows/console/getnumberofconsoleinputevents
	GetNumberOfConsoleInputEvents(m_ConsoleHandle, &m_NumInputRecords);
	return m_NumInputRecords;
}
