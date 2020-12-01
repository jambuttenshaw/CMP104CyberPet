#include "RenderAPI.h"

#include <vector>

#include <chrono>
RenderAPI::RenderAPI()
	: m_ConsoleDimensions(Vector2i({ 0, 0 }))
{
	
}

RenderAPI::~RenderAPI()
{
	SetCursorPosition(0, 0);
	SetCursorVisibility(true);
}

void RenderAPI::Init()
{
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	UpdateConsoleDimensions();

	SetCursorVisibility(false);
	SetCursorPosition({ 0, m_MaxConsoleHeight + 1 });
}

// displaying characters on the console is done using
// from https://docs.microsoft.com/en-us/windows/console/writeconsoleoutputcharacter
// using cout was much less performant

void RenderAPI::SubmitImageData(wchar_t** imageData, Vector2i dimensions, Vector2i position)
{
	DWORD dw;

	// work out what section of the image is actually on screen
	// the things we need to know: where to start each row, how many to draw from each row, where to start each column, how many to draw from each column

	for (int y = 0; y < dimensions.y; y++)
	{
		for (int x = 0; x < dimensions.x; x++)
		{
			WriteConsoleOutputCharacter(m_ConsoleHandle, &imageData[y][x], 1, { (short)(position.x + x), (short)(position.y + y) }, &dw);
		}
	}
}

void RenderAPI::SubmitTextData(const wchar_t* text, int length, Vector2i position)
{
	DWORD dw;
	WriteConsoleOutputCharacter(m_ConsoleHandle, text, length, { (short)position.x, (position.y > m_MaxConsoleHeight ? (short)m_MaxConsoleHeight : (short)position.y) }, &dw);
}

void RenderAPI::Clear(Vector2i origin, Vector2i dimensions, wchar_t clearChar)
{
	DWORD dw;
	std::vector<wchar_t> line(dimensions.x, clearChar);
	for (int y = 0; y < ((dimensions.y + origin.y) > m_MaxConsoleHeight ? m_MaxConsoleHeight - origin.y : dimensions.y); y++)
	{
		WriteConsoleOutputCharacter(m_ConsoleHandle, &line[0], dimensions.x, { (short)origin.x, (short)(origin.y + y) }, &dw);
	}
	
}

void RenderAPI::ClearAll()
{
	DWORD dw;
	FillConsoleOutputCharacter(m_ConsoleHandle, ' ', m_ConsoleDimensions.x * m_ConsoleDimensions.y, { 0, 0 }, &dw);
}

void RenderAPI::UpdateConsoleDimensions()
{
	// from https://docs.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo
	// and https://docs.microsoft.com/en-us/windows/console/console-screen-buffer-info-str
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(m_ConsoleHandle, &consoleInfo);

	m_ConsoleDimensions = { consoleInfo.dwSize.X, consoleInfo.dwSize.Y };
}

void RenderAPI::UpdateConsoleDimensions(int x, int y)
{
	m_ConsoleDimensions = { x, y };
}

int RenderAPI::GetConsoleWidth()
{
	return m_ConsoleDimensions.x;
}

int RenderAPI::GetConsoleHeight()
{
	return m_ConsoleDimensions.y;
}


void RenderAPI::SetCursorPosition(int x, int y)
{
	// from https://docs.microsoft.com/en-us/windows/console/setconsolecursorposition
	SetConsoleCursorPosition(m_ConsoleHandle, {(short)x, (short)y});
}


void RenderAPI::SetCursorVisibility(bool toggle)
{
	// from https://docs.microsoft.com/en-us/windows/console/console-cursor-info-str
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(m_ConsoleHandle, &cursorInfo);

	cursorInfo.bVisible = toggle; // set the cursor visibility
	SetConsoleCursorInfo(m_ConsoleHandle, &cursorInfo);
}
