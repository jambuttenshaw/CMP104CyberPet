#include "RenderAPI.h"

#include <vector>

// in the constructor we just want to initialize the console dimenions as 0
// well retrieve the console dimensions from windows in init
RenderAPI::RenderAPI()
	: m_ConsoleDimensions(Vector2i({ 0, 0 }))
{
}

// destructor
// set the state of the console back to the way it was when the program started
RenderAPI::~RenderAPI()
{
	// return the cursor position to the origin
	SetCursorPosition(0, 0);
	// and make the cusror visible again
	SetCursorVisibility(true);
}

void RenderAPI::Init()
{
	// get the handle to the console
	// were wanting the standard output console handle,
	// as the rendererapi only deals with output to the console
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// retrieve and store the console dimensions from windows
	UpdateConsoleDimensions();

	// we want to hide the cursor as we dont want it flashing about on screen
	SetCursorVisibility(false);
	// and we want to set the cursor position to below the display area of the console
	// so if we output any debug info it is not obscured by the graphics displayed on screen
	SetCursorPosition({ 0, m_MaxConsoleHeight + 1 });
}

// displaying characters on the console is done using
// from https://docs.microsoft.com/en-us/windows/console/writeconsoleoutputcharacter
// using cout was much less performant

void RenderAPI::SubmitImageData(wchar_t** imageData, Vector2i dimensions, Vector2i position)
{
	// windows will write into this variable with the number of characters that were actually written
	// when we make the function call to write characters to the console
	// we don't need to do anything with this information,
	// but windows still requires us to give it a reference to a variable to write to
	DWORD numCharsWritten;

	// windows handles if the image is outside the bounds of the console for us

	// iterate for the dimensions of the image
	for (int y = 0; y < dimensions.y; y++)
	{
		for (int x = 0; x < dimensions.x; x++)
		{
			// write the current character to the console
			// WriteConsoleOutputCharacter takes in the console handle,
			// the memory address of the data to be written, the number of characters to write,
			// and a COORD object specifying where to write the characters
			// it also requires an output variable for num chars written, as explained above
			WriteConsoleOutputCharacter(m_ConsoleHandle, &imageData[y][x], 1, { (short)(position.x + x), (short)(position.y + y) }, &numCharsWritten);
		}
	}
}

void RenderAPI::SubmitTextData(const wchar_t* text, int length, Vector2i position)
{
	// again the numCharsWritten is required by windows
	DWORD numCharsWritten;
	// pass in the console handle, a pointer to the start of the text we want to write, the length of the text and the position to write it at
	WriteConsoleOutputCharacter(m_ConsoleHandle, text, length, { (short)position.x, (short)position.y }, &numCharsWritten);
}

void RenderAPI::Clear(Vector2i origin, Vector2i dimensions, wchar_t clearChar)
{
	// fills the specified area with the specified character

	// we still need a place to output the number of characters written
	DWORD numCharsWritten;

	// create a vector of characters that is the length of 1 line in the specified area
	// we cant use an array as we dont know the dimenions of the array at compile time so c++ wont allow it
	// the array is populated by the clear char
	std::vector<wchar_t> lineChar(dimensions.x, clearChar);
	// iterate for the number of rows to clear
	for (int y = 0; y < dimensions.y; y++)
	{
		// then fill each row with the clear character
		WriteConsoleOutputCharacter(m_ConsoleHandle, &lineChar[0], dimensions.x, { (short)origin.x, (short)(origin.y + y) }, &numCharsWritten);
	}
	
}

void RenderAPI::UpdateConsoleDimensions()
{
	// from https://docs.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo
	// and https://docs.microsoft.com/en-us/windows/console/console-screen-buffer-info-str

	// create a screen buffer info object for holding the data about the console
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	// get the info about the console by passing the console handle and the reference to our screen buffer info object
	GetConsoleScreenBufferInfo(m_ConsoleHandle, &consoleInfo);

	// then we can just retrieve the console dimensions from the screen buffer object
	m_ConsoleDimensions = { consoleInfo.dwSize.X, consoleInfo.dwSize.Y };
}

void RenderAPI::UpdateConsoleDimensions(int x, int y)
{
	// if we already know the dimensions of the console and want to update them in the renderapi, then we can use this function
	// which just assigns the console dimensions as the 2 int parameters
	m_ConsoleDimensions = { x, y };
}

// return the x component of the console dimensions
int RenderAPI::GetConsoleWidth()
{
	return m_ConsoleDimensions.x;
}

// return the y component of the console dimensions
int RenderAPI::GetConsoleHeight()
{
	return m_ConsoleDimensions.y;
}


// sets the console position to the x and y coordinate specified
void RenderAPI::SetCursorPosition(int x, int y)
{
	// from https://docs.microsoft.com/en-us/windows/console/setconsolecursorposition
	// takes in the console handle and a COORD object specifying the position
	SetConsoleCursorPosition(m_ConsoleHandle, {(short)x, (short)y});
}


void RenderAPI::SetCursorVisibility(bool toggle)
{
	// from https://docs.microsoft.com/en-us/windows/console/console-cursor-info-str
	// an object to hold the info about the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	// populate the cursor info object by using GetConsoleCursorInfo
	GetConsoleCursorInfo(m_ConsoleHandle, &cursorInfo);

	// then we can change the data in the cursor info object
	cursorInfo.bVisible = toggle; // set the cursor visibility
	// assign the modified cursor info back into the console
	SetConsoleCursorInfo(m_ConsoleHandle, &cursorInfo);
}
