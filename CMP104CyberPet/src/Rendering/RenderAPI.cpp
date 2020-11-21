#include "RenderAPI.h"

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

void RenderAPI::Submit(char** imageData)
{
	// move cursor to coordinates of image
	// draw each row of the image
}

void RenderAPI::Clear(char clearChar)
{
	// reset cursor position to 0, 0
	SetCursorPosition();

	// fill the entire console with 0's
	Vector2i dim = GetConsoleDimensions();
	for (int y = 0; y < (dim.y > m_MaxConsoleHeight ? m_MaxConsoleHeight : dim.y); y++)
	{
		for (int x = 0; x < dim.x; x++)
		{
			std::cout << clearChar;
		}
		std::cout << std::endl;
	}
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
