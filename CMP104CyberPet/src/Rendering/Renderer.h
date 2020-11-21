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

	inline static void Submit(Image image) { s_RenderAPI->Submit(image.GetImageData()); }
	inline static void Submit(char** imageData) { s_RenderAPI->Submit(imageData); }

	inline static int GetConsoleWidth() { return s_RenderAPI->GetConsoleWidth(); }
	inline static int GetConsoleHeight() { return s_RenderAPI->GetConsoleHeight(); }

private:
	static RenderAPI* s_RenderAPI;
};

