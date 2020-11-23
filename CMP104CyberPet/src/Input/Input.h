#pragma once

#include <vector>
#include <windows.h>

class Input
{
public:
	Input();
	~Input();

	void Poll();

private:
	// handle to the console
	HANDLE m_ConsoleHandle = nullptr;
	// save the old console mode so we can revert back upon program end
	DWORD m_OldConsoleMode = 0;

	// a buffer to hold input records that have not yet been handled
	std::vector<INPUT_RECORD> m_InputRecordBuffer; // more than large enough to hold all the inputs that will need processed in a single frame
	DWORD m_NumInputRecords = 0; // the number of input records to be processed this frame
};

