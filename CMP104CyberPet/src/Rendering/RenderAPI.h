#pragma once

#include "../Core/MathsUtility.h"

#include <Windows.h>

// the render api is the interface between the program and the windows console
// everything that gets put on screen goes through here
class RenderAPI
{
public:
	// constructor and destructor
	RenderAPI();
	~RenderAPI();

	// init function, since we may not want all the initialising
	// to happen when the render api is created but instead when we are
	// ready to initialize it
	void Init();

	// image data is a 2D array of characters
	// SubmitImageData sends this array of characters, of the dimensions specified, to the position specified on the console
	void SubmitImageData(wchar_t** imageData, Vector2i dimensions, Vector2i position);
	// submit text data takes in a c-style wide string and the length of that string, and writes that text at the specified position on the console
	void SubmitTextData(const wchar_t* text, int length, Vector2i position);
	// Clear would maybe be more appropriately named 'Fill', as it fills an area at the position and of the dimensions with the same character
	void Clear(Vector2i origin, Vector2i dimensions, wchar_t clearChar);

	// since the console dimensions don't often change, we only want to update the stored value for the console dimensions
	// when we need to do. No point in checking the console dimensions every frame when theyre going to be the same 99% of the time
	void UpdateConsoleDimensions();
	// we can also set the console dimensions using this overload, this is useful if the new console dimensions are given to us in an event callback
	void UpdateConsoleDimensions(int x, int y);
	// returns a vector of the console dimensions containing both the width and height
	inline Vector2i GetConsoleDimensions() { return m_ConsoleDimensions; }
	// get only the width of the console
	int GetConsoleWidth();
	// get only the height of the console
	int GetConsoleHeight();

	// a quick toggle to set whether the cursor is visible in the console or not
	void SetCursorVisibility(bool toggle);

	// by default the console's height is not just what is visible without scrolling down,
	// so we may want to fix the height of the displayable area on the console
	void FixMaxConsoleHeight(int maxHeight) { m_MaxConsoleHeight = maxHeight; }

private:
	// sets the cursor to a specific position on the console screen
	void SetCursorPosition(int x = 0, int y = 0);
	// we can also specify the position as a vector
	inline void SetCursorPosition(Vector2i pos) { SetCursorPosition(pos.x, pos.y); }

private:
	// the handle to the console,
	// which is in essence a pointer to the console
	HANDLE m_ConsoleHandle = nullptr;
	
	// the stored dimensions of the console
	Vector2i m_ConsoleDimensions;

	// what the height of the display area of the console is fixed to
	// by default I chose 24, as that is almost the size of the screen
	// visible by default
	// space underneath the display area is used for debugging info
	int m_MaxConsoleHeight = 24;
};

