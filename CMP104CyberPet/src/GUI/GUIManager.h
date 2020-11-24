#pragma once

#include "GUIScreen.h"

#include "../Core/Sprite.h"

#include <vector>


class GUIManager
{
public:
	GUIManager();
	~GUIManager();

	std::vector<Sprite*> GetSprites();

private:
	std::vector<GUIScreen*> m_Screens;

};
