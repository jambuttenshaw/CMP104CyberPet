#pragma once

#include "InputAPI.h"

class Input
{
public:
	inline static void Init() {}
	inline static void Shutdown()
	{
		delete s_InputAPI;
	}

	inline static int PollEvents() { return s_InputAPI->PollEvents(); }
	inline static void HandleEvents() { s_InputAPI->HandleEvents(); }

	inline static INPUT_RECORD* GetEventQueueStart() { return s_InputAPI->GetEventQueueStart(); }

	inline static int GetEventQueueLength() { return s_InputAPI->GetEventQueueLength(); }

	inline static void SetKeyEventCallback(void (*callback)(KEY_EVENT_RECORD)) { s_InputAPI->SetKeyEventCallback(callback); }
	inline static void SetMouseEventCallback(void (*callback)(MOUSE_EVENT_RECORD)) { s_InputAPI->SetMouseEventCallback(callback); }
	inline static void SetWindowResizeCallback(void (*callback)(WINDOW_BUFFER_SIZE_RECORD)) { s_InputAPI->SetWindowResizeCallback(callback); }
	inline static void SetMenuEventCallback(void (*callback)(MENU_EVENT_RECORD)) { s_InputAPI->SetMenuEventCallback(callback); }
	inline static void SetFocusEventCallback(void (*callback)(FOCUS_EVENT_RECORD)) { s_InputAPI->SetFocusEventCallback(callback); }

private:
	static InputAPI* s_InputAPI;
};