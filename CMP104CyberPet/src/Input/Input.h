#pragma once

#include "Events.h"

#include <vector>
#include <windows.h>

class Input
{
public:
	Input();
	~Input();

	// returns the number of events read from the queue
	int PollEvents();
	void HandleEvents();

	inline INPUT_RECORD* GetEventQueueStart() { return &m_InputRecordBuffer[0]; }

	int GetEventQueueLength();

	inline void SetKeyEventCallback(void (*callback)(KEY_EVENT_RECORD)) { m_KeyEventFunc = callback; }
	inline void SetMouseEventCallback(void (*callback)(MOUSE_EVENT_RECORD)) { m_MouseEventFunc = callback; }
	inline void SetWindowResizeCallback(void (*callback)(WINDOW_BUFFER_SIZE_RECORD)) { m_WindowResizeFunc = callback; }
	inline void SetMenuEventCallback(void (*callback)(MENU_EVENT_RECORD)) { m_MenuEventFunc = callback; }
	inline void SetFocusEventCallback(void (*callback)(FOCUS_EVENT_RECORD)) { m_FocusEventFunc = callback; }

private:
	// handle to the console
	HANDLE m_ConsoleHandle = nullptr;
	// save the old console mode so we can revert back upon program end
	DWORD m_OldConsoleMode = 0;

	// a buffer to hold input records that have not yet been handled
	INPUT_RECORD m_InputRecordBuffer[128]; // more than large enough to hold all the inputs that will need processed in a single frame
	DWORD m_NumInputRecords = 0; // the number of input records to be processed this frame

private:
	// EVENT CALLBACK FUNCTIONS
	void (*m_KeyEventFunc)(KEY_EVENT_RECORD) = nullptr;
	void (*m_MouseEventFunc)(MOUSE_EVENT_RECORD) = nullptr;
	void (*m_WindowResizeFunc)(WINDOW_BUFFER_SIZE_RECORD) = nullptr;
	void (*m_MenuEventFunc)(MENU_EVENT_RECORD) = nullptr;
	void (*m_FocusEventFunc)(FOCUS_EVENT_RECORD) = nullptr;
};

