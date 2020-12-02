#pragma once

#include "InputAPI.h"

/*
The reason I have used a class consisting of only static members
instead of just directly creating an instance of the input api in main
is that I want other objects in the game to be able to access
the members of the input api, such as setting event callbacks or 
if I was to expand the API to be able to get an instant read on key states

For reference on how reading the console's events worked,
I mostly referred to these pages:
https://docs.microsoft.com/en-us/windows/console/readconsoleinput
https://docs.microsoft.com/en-us/windows/console/input-record-str
https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events
*/

class Input
{
public:
	// we dont need to do anything to initialze the input api, its all handled
	// in the constructor of InputAPI
	inline static void Init() {}
	// when the input system shuts down we delete the input api object
	inline static void Shutdown()
	{
		delete s_InputAPI;
	}

	// PollEvents retrieves all the unprocessed events in the console's event queue from windows,
	// and stores them in the InputAPI's own event buffer for processing and sending to callback
	// it returns the number of events that were read from the windows event queue and placed into the event buffer
	inline static int PollEvents() { return s_InputAPI->PollEvents(); }
	// HandleEvents goes through the input api's event buffer, and calls the event callback function for each type of event
	inline static void HandleEvents() { s_InputAPI->HandleEvents(); }

	// returns a pointer to the start of the event queue
	// this is useful for iterating through the event queue outside of the input api
	inline static INPUT_RECORD* GetEventQueueStart() { return s_InputAPI->GetEventQueueStart(); }

	// returns the number of events that are currently in the buffer that havent been handled yet
	inline static int GetEventQueueLength() { return s_InputAPI->GetEventQueueLength(); }

	// functions for setting the event callback  function
	// when an event occurs, the input api will call the event callback function for that type of event
	// and pass the event record into the callback function
	// this is useful as I can specify my own function to handle the event when it occurs
	// and it will automatically get called by the input api

	// there is one overload of the set event callback function for each type of event
	inline static void SetEventCallback(const std::function<void(KEY_EVENT_RECORD*)>& func) { s_InputAPI->SetEventCallback(func); }
	inline static void SetEventCallback(const std::function<void(MOUSE_EVENT_RECORD*)>& func) { s_InputAPI->SetEventCallback(func); }
	inline static void SetEventCallback(const std::function<void(WINDOW_BUFFER_SIZE_RECORD*)>& func) { s_InputAPI->SetEventCallback(func); }
	inline static void SetEventCallback(const std::function<void(MENU_EVENT_RECORD*)>& func) { s_InputAPI->SetEventCallback(func); }
	inline static void SetEventCallback(const std::function<void(FOCUS_EVENT_RECORD*)>& func) { s_InputAPI->SetEventCallback(func); }

private:
	// a static reference to the input api object
	static InputAPI* s_InputAPI;
};