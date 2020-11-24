#pragma once

#include <vector>

#include "RenderAPI.h"
#include "Image.h"
#include "../Core/Sprite.h"

class Renderer
{
public:
	inline static void Init() { s_RenderAPI->Init(); }
	inline static void Shutdown()
	{
		delete s_RenderAPI;
	}

	inline static void Clear(Vector2i origin = { 0, 0 }, Vector2i dimensions = s_RenderAPI->GetConsoleDimensions(), wchar_t clearChar = ' ') { s_RenderAPI->Clear(origin, dimensions, clearChar); }
	inline static void ClearAll() { s_RenderAPI->ClearAll(); }

	inline static void Queue(Sprite* sprite) { s_RenderQueue.push_back(sprite); }

	inline static void DrawAll()
	{
		for (Sprite* s : s_RenderQueue)
		{
			if (s->IsDirty())
			{
				Submit(s);
				s->Clean();
			}
		}
		s_RenderQueue.clear();
	}

	inline static void Submit(Sprite* sprite) { s_RenderAPI->Submit(sprite->GetImage()->GetImageData(), sprite->GetImage()->GetDimensions(), sprite->GetPosition()); }
	inline static void Submit(Image* image, Vector2i position) { s_RenderAPI->Submit(image->GetImageData(), image->GetDimensions(), position); }
	inline static void Submit(wchar_t** imageData, Vector2i dimensions, Vector2i position) { s_RenderAPI->Submit(imageData, dimensions, position); }

	inline static int GetConsoleWidth() { return s_RenderAPI->GetConsoleWidth(); }
	inline static int GetConsoleHeight() { return s_RenderAPI->GetConsoleHeight(); }

private:
	static RenderAPI* s_RenderAPI;

	static std::vector<Sprite*> s_RenderQueue;
};
