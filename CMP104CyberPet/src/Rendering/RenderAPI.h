#pragma once

#include "../Core/MathsUtility.h"

#include <Windows.h>

class RenderAPI
{
public:
	RenderAPI();
	~RenderAPI();

	void Init();

	void SubmitImageData(wchar_t** imageData, Vector2i dimensions, Vector2i position);
	void SubmitTextData(const wchar_t* text, int length, Vector2i position);
	void Clear(Vector2i origin, Vector2i dimensions, wchar_t clearChar);
	void ClearAll();

	
	void UpdateConsoleDimensions();
	void UpdateConsoleDimensions(int x, int y);
	inline Vector2i GetConsoleDimensions() { return m_ConsoleDimensions; }
	int GetConsoleWidth();
	int GetConsoleHeight();

	void SetCursorVisibility(bool toggle);

	void FixMaxConsoleHeight(int maxHeight) { m_MaxConsoleHeight = maxHeight; }

private:
	void SetCursorPosition(int x = 0, int y = 0);
	inline void SetCursorPosition(Vector2i pos) { SetCursorPosition(pos.x, pos.y); }

private:
	HANDLE m_ConsoleHandle = nullptr;

	Vector2i m_ConsoleDimensions;

	int m_MaxConsoleHeight = 24;
};

