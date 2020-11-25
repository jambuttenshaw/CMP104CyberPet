#pragma once

#include "Events.h"

#include <vector>
#include <functional>
#include <windows.h>

class InputAPI
{
public:
	InputAPI();
	~InputAPI();

	// returns the number of events read from the queue
	int PollEvents();
	void HandleEvents();

	inline INPUT_RECORD* GetEventQueueStart() { return &m_InputRecordBuffer[0]; }

	int GetEventQueueLength();

	inline void SetEventCallback(const std::function<void(INPUT_RECORD*)>& callback) { m_EventCallback = callback; }

private:
	// handle to the console
	HANDLE m_ConsoleHandle = nullptr;
	// save the old console mode so we can revert back upon program end
	DWORD m_OldConsoleMode = 0;

	// a buffer to hold input records that have not yet been handled
	INPUT_RECORD m_InputRecordBuffer[128]; // more than large enough to hold all the inputs that will need processed in a single frame
	DWORD m_NumInputRecords = 0; // the number of input records to be processed this frame

private:
	// EVENT CALLBACK FUNCTION
	std::function<void(INPUT_RECORD*)> m_EventCallback;
};
