#pragma once

#include "Button.h"

#include <vector>

class GUIScreen
{
public:
	GUIScreen();
	~GUIScreen();

	std::vector<Sprite*> GetButtonSprites();

private:

};
