#include "RenderAPI.h"

#include <vector>

#include <chrono>
#include <iostream>

RenderAPI::RenderAPI()
{

}

RenderAPI::~RenderAPI()
{

}

void RenderAPI::Init()
{
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetCursorVisibility(false);
}

// displaying characters on the console is done using
// from https://docs.microsoft.com/en-us/windows/console/writeconsoleoutputcharacter
// using cout was much less performant

void RenderAPI::Submit(wchar_t** imageData, Vector2i dimensions, Vector2i position)
{
	for (int y = 0; y < (dimensions.y > m_MaxConsoleHeight ? m_MaxConsoleHeight : dimensions.y); y++)
	{
		for (int x = 0; x < dimensions.x; x++)
		{
			DWORD dw;
			WriteConsoleOutputCharacter(m_ConsoleHandle, &imageData[y][x], 1, { (short)(position.x + x), (short)(position.y + y) }, &dw);
		}
	}
}

void RenderAPI::Clear(Vector2i origin, Vector2i dimensions, wchar_t clearChar)
{
	std::vector<wchar_t> line(dimensions.x, clearChar);
	for (int y = 0; y < (dimensions.y > m_MaxConsoleHeight ? m_MaxConsoleHeight : dimensions.y); y++)
	{
		DWORD dw;
		WriteConsoleOutputCharacter(m_ConsoleHandle, &line[0], dimensions.x, { (short)origin.x, (short)(origin.y + y) }, &dw);
	}
	
}

void RenderAPI::ClearAll()
{
	Vector2i dim = GetConsoleDimensions();
	int size = dim.x * dim.y;
	DWORD dw;
	FillConsoleOutputCharacter(m_ConsoleHandle, ' ', size, { 0, 0 }, &dw);
}

Vector2i RenderAPI::GetConsoleDimensions()
{
	// from https://docs.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo
	// and https://docs.microsoft.com/en-us/windows/console/console-screen-buffer-info-str
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(m_ConsoleHandle, &consoleInfo);

	return Vector2i(consoleInfo.dwSize.X, consoleInfo.dwSize.Y);
}

int RenderAPI::GetConsoleWidth()
{
	return GetConsoleDimensions().x;
}

int RenderAPI::GetConsoleHeight()
{
	return GetConsoleDimensions().y;
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
