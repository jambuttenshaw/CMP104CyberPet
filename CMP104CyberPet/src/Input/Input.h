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

	inline static void SetEventCallback(const std::function<void(INPUT_RECORD*)>& func) { s_InputAPI->SetEventCallback(func); }

private:
	static InputAPI* s_InputAPI;
};