#pragma once

#include "../Core/MathsUtility.h"

#include <Windows.h>

class RenderAPI
{
public:
	RenderAPI();
	~RenderAPI();

	void Init();

	void Submit(char** imageData, Vector2i dimensions, Vector2i position);
	void Clear(Vector2i origin, Vector2i dimensions, char clearChar);
	
	Vector2i GetConsoleDimensions();
	int GetConsoleWidth();
	int GetConsoleHeight();

	void SetCursorVisibility(bool toggle);

	void FixMaxConsoleHeight(int maxHeight) { m_MaxConsoleHeight = maxHeight; }

private:
	void SetCursorPosition(int x = 0, int y = 0);
	inline void SetCursorPosition(Vector2i pos) { SetCursorPosition(pos.x, pos.y); }

private:
	HANDLE m_ConsoleHandle = nullptr;

	int m_MaxConsoleHeight = 20;
};

