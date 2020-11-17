#pragma once

#include "RenderAPI.h"

class Renderer
{
public:
	inline static void Init() {}
	inline static void Shutdown()
	{
		delete s_RenderAPI;
	}

	inline static void Clear() { s_RenderAPI->Clear(); }

	inline static void Submit() { s_RenderAPI->Submit(); }

	inline static int GetConsoleWidth() { s_RenderAPI->GetConsoleWidth(); }
	inline static int GetConsoleHeight() { s_RenderAPI->GetConsoleHeight(); }

private:
	static RenderAPI* s_RenderAPI;
};

