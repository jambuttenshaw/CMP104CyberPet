#pragma once

#include "MathsUtility.h"

class RenderAPI
{
public:
	RenderAPI();
	~RenderAPI();

	void Init();

	void Submit();
	void Clear();

	Vector2i GetConsoleDimensions();
	int GetConsoleWidth();
	int GetConsoleHeight();

};

