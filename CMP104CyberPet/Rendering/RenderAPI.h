#pragma once

#include "MathsUtility.h"

class RenderAPI
{
public:
	RenderAPI();
	~RenderAPI();

	void Init();

	void Submit(char** imageData);
	void Clear();

	Vector2i GetConsoleDimensions();
	int GetConsoleWidth();
	int GetConsoleHeight();

};

