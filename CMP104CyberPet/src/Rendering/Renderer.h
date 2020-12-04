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
	inline static void Init() { s_RenderAPI->Init(); }
	inline static void Shutdown()
	{
		delete s_RenderAPI;
	}

	inline static void Clear(wchar_t clearChar = ' ', Vector2i origin = { 0, 0 }, Vector2i dimensions = s_RenderAPI->GetConsoleDimensions()) { s_RenderAPI->Clear(origin, dimensions, clearChar); }

	inline static void Queue(Sprite* sprite) { s_RenderQueue.push_back(sprite); }

	inline static void DrawAll()
	{
		for (Sprite* s : s_RenderQueue)
		{
			SubmitImageData(s);
		}
		s_RenderQueue.clear();
	}

	inline static void SubmitImageData(Sprite* sprite) { s_RenderAPI->SubmitImageData(sprite->GetImage()->GetImageData(), sprite->GetImage()->GetDimensions(), sprite->GetIntPosition()); }
	inline static void SubmitImageData(Image* image, Vector2i position) { s_RenderAPI->SubmitImageData(image->GetImageData(), image->GetDimensions(), position); }
	inline static void SubmitImageData(wchar_t** imageData, Vector2i dimensions, Vector2i position) { s_RenderAPI->SubmitImageData(imageData, dimensions, position); }

	inline static void SubmitTextData(wchar_t* text, int length, Vector2i position) { s_RenderAPI->SubmitTextData(text, length, position); }
	inline static void SubmitTextData(const std::wstring& text, int length, Vector2i position) { s_RenderAPI->SubmitTextData(text.c_str(), length, position); }

	inline static int GetConsoleWidth() { return s_RenderAPI->GetConsoleWidth(); }
	inline static int GetConsoleHeight() { return s_RenderAPI->GetConsoleHeight(); }

	inline static int SetMaxConsoleHeight(int height) { s_RenderAPI->FixMaxConsoleHeight(height); }
	inline static void UpdateConsoleDimensions() { s_RenderAPI->UpdateConsoleDimensions(); }
	inline static void UpdateConsoleDimensions(int x, int y) { s_RenderAPI->UpdateConsoleDimensions(x, y); }

private:
	static RenderAPI* s_RenderAPI;

	static std::vector<Sprite*> s_RenderQueue;
};
