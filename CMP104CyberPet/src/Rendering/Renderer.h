#pragma once

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

	inline static void Clear(char clearChar = ' ') { s_RenderAPI->Clear(clearChar); }

	inline static void Submit(Image* image, Vector2i position) { s_RenderAPI->Submit(image->GetImageData(), image->GetDimensions(), position); }
	inline static void Submit(char** imageData, Vector2i dimensions, Vector2i position) { s_RenderAPI->Submit(imageData, dimensions, position); }

	inline static int GetConsoleWidth() { return s_RenderAPI->GetConsoleWidth(); }
	inline static int GetConsoleHeight() { return s_RenderAPI->GetConsoleHeight(); }

private:
	static RenderAPI* s_RenderAPI;
};

