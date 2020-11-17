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

	inline static void Submit() { s_RenderAPI->Submit();	}

private:
	static RenderAPI* s_RenderAPI;
};

