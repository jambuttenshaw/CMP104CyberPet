#pragma once

#include <windows.h>

class EventDispatcher
{
public:
	EventDispatcher(INPUT_RECORD& e)
		: m_Event(e)
	{
	}

	bool Dispatch(int eventType, void func(INPUT_RECORD))
	{
		if ((int)m_Event.EventType == eventType)
		{
			func(m_Event);
		}
	}

private:
	INPUT_RECORD m_Event;
};
