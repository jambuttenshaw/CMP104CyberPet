#pragma once

#include <vector>
#include <functional>
#include <windows.h>

class InputAPI
{
public:
	// constructor and destructor
	InputAPI();
	~InputAPI();

	// returns the number of events read from the queue
	// and stores the event records read from the windows console event queue in the input api's event buffer
	int PollEvents();

	// processes the events queue
	// by calling the relevant callback function for each event
	void HandleEvents();

	// returns a pointer to the start of the event queue
	// this is useful for iterating through the event queue outside of the input api
	inline INPUT_RECORD* GetEventQueueStart() { return &m_InputRecordBuffer[0]; }

	// returns the number of events that are currently in the buffer that havent been handled yet
	int GetEventQueueLength();

	// functions for setting the event callback  function
	// when an event occurs, the input api will call the event callback function for that type of event
	// and pass the event record into the callback function
	// this is useful as I can specify my own function to handle the event when it occurs
	// and it will automatically get called by the input api

	// there is one overload of the set event callback function for each type of event
	inline void SetEventCallback(const std::function<void(KEY_EVENT_RECORD*)>& callback) { m_KeyEventCallback = callback; }
	inline void SetEventCallback(const std::function<void(MOUSE_EVENT_RECORD*)>& callback) { m_MouseEventCallback = callback; }
	inline void SetEventCallback(const std::function<void(WINDOW_BUFFER_SIZE_RECORD*)>& callback) { m_WindowResizeEventCallback = callback; }
	inline void SetEventCallback(const std::function<void(MENU_EVENT_RECORD*)>& callback) { m_MenuEventCallback = callback; }
	inline void SetEventCallback(const std::function<void(FOCUS_EVENT_RECORD*)>& callback) { m_FocusEventCallback = callback; }

private:
	// windows data types are used here
	// as we are dealing with the console's api

	// handle to the console
	HANDLE m_ConsoleHandle = nullptr;

	// save the old console mode so we can revert back upon program end
	// as we have to modify the console mode
	DWORD m_OldConsoleMode = 0;

	// a buffer to hold input records that have not yet been handled
	INPUT_RECORD m_InputRecordBuffer[128]; // more than large enough to hold all the inputs that will need processed in a single frame
	DWORD m_NumInputRecords = 0; // the number of input records to be processed this frame

private:
	// EVENT CALLBACK FUNCTION
	// std::function holds a reference to a function, so we can assign a function to
	// these members of the inputapi and then execute them later
	// each function returns void and takes an input record as a parameter
	std::function<void(KEY_EVENT_RECORD*)> m_KeyEventCallback;
	std::function<void(MOUSE_EVENT_RECORD*)> m_MouseEventCallback;
	std::function<void(WINDOW_BUFFER_SIZE_RECORD*)> m_WindowResizeEventCallback;
	std::function<void(MENU_EVENT_RECORD*)> m_MenuEventCallback;
	std::function<void(FOCUS_EVENT_RECORD*)> m_FocusEventCallback;
};

