#pragma once

#include <vector>
#include "RenderAPI.h"
#include "Image.h"
#include "../Core/Sprite.h"

/*
The reason I have used a class consisting of only static members
instead of just directly creating an instance of the renderer in main
is that I want other objects in the game to be able to access
features of the renderer, such as retrieving the console dimensions

Therefore making this static 'interface' to the renderer means that the renderer isn't owned
by any specific object in the game, so any sprite can get access to the renderer easily
*/

class Renderer
{
public:
	// initialize the renderer
	inline static void Init() { s_RenderAPI->Init(); }
	// delete the renderapi object to call its destructor and remove it from memory
	inline static void Shutdown()
	{
		delete s_RenderAPI;
	}

	// call the clear function of the renderapi
	// we give it default values here, which would make the screen completely blank
	// so if you call Clear() without parameters then it will clear the whole console
	inline static void Clear(wchar_t clearChar = ' ', Vector2i origin = { 0, 0 }, Vector2i dimensions = s_RenderAPI->GetConsoleDimensions()) { s_RenderAPI->Clear(origin, dimensions, clearChar); }

	// Queue adds a pointer to a sprite onto the queue, that will get drawn to the screen this game
	inline static void Queue(Sprite* sprite) { s_RenderQueue.push_back(sprite); }

	// draw all renders everything on the queue to the display
	inline static void DrawAll()
	{
		// iterate through the render queue
		for (Sprite* s : s_RenderQueue)
		{
			// submit each sprite to the renderapi for rendering
			SubmitImageData(s);
		}
		// then remove everything from the queue as it has all been handled
		s_RenderQueue.clear();
	}
	
	// send image data to the renderapi
	// there are a bunch of different overloads here to deal with different types of image data
	// you can send a raw 2D array of characters to the renderapi,
	// or you can send an image object,
	// or you can pass in the whole sprite
	// passing in the whole sprite is the most convenient, as it contains the image data, the image dimensions, and the position of the image
	// all in one go
	inline static void SubmitImageData(Sprite* sprite) { s_RenderAPI->SubmitImageData(sprite->GetImage()->GetImageData(), sprite->GetImage()->GetDimensions(), sprite->GetIntPosition()); }
	inline static void SubmitImageData(Image* image, Vector2i position) { s_RenderAPI->SubmitImageData(image->GetImageData(), image->GetDimensions(), position); }
	inline static void SubmitImageData(wchar_t** imageData, Vector2i dimensions, Vector2i position) { s_RenderAPI->SubmitImageData(imageData, dimensions, position); }

	// 2 options for text data
	// either a c-style string of wide characters
	// or just a wide string of text that gets converted into a cstring before passing it onto the renderapi
	inline static void SubmitTextData(wchar_t* text, int length, Vector2i position) { s_RenderAPI->SubmitTextData(text, length, position); }
	inline static void SubmitTextData(const std::wstring& text, int length, Vector2i position) { s_RenderAPI->SubmitTextData(text.c_str(), length, position); }

	// functions for getting the console dimensions
	inline static int GetConsoleWidth() { return s_RenderAPI->GetConsoleWidth(); }
	inline static int GetConsoleHeight() { return s_RenderAPI->GetConsoleHeight(); }

	// set the max height of the drawable area on the console
	inline static int SetMaxConsoleHeight(int height) { s_RenderAPI->FixMaxConsoleHeight(height); }

	// update the console dimensions if we need to
	// ie if there has been a change in the window size we need to change the size of the console in the renderapi
	inline static void UpdateConsoleDimensions() { s_RenderAPI->UpdateConsoleDimensions(); }
	inline static void UpdateConsoleDimensions(int x, int y) { s_RenderAPI->UpdateConsoleDimensions(x, y); }

private:
	// a reference to the renderapi object
	static RenderAPI* s_RenderAPI;

	// the render queue
	static std::vector<Sprite*> s_RenderQueue;
};
