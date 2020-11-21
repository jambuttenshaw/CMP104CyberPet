#pragma once

#include "Rendering/RenderAPI.h"
#include "Rendering/Image.h"
#include "Sprite.h"

class Renderer
{
public:
	inline static void Init() {}
	inline static void Shutdown()
	{
		delete s_RenderAPI;
	}

	inline static void Clear() { s_RenderAPI->Clear(); }

	inline static void Submit(Sprite sprite) { s_RenderAPI->Submit(sprite.GetImage().GetImageData()); }
	inline static void Submit(Image image) { s_RenderAPI->Submit(image.GetImageData()); }
	inline static void Submit(char** imageData) { s_RenderAPI->Submit(imageData); }

	inline static int GetConsoleWidth() { s_RenderAPI->GetConsoleWidth(); }
	inline static int GetConsoleHeight() { s_RenderAPI->GetConsoleHeight(); }

private:
	static RenderAPI* s_RenderAPI;
};

