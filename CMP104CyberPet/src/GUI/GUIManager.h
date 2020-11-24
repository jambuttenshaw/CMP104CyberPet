#pragma once

#include "GUIScreen.h"

class GUIManager
{
public:
	GUIManager();
	~GUIManager();

	void LoadScreen(int screenNum);

	std::vector<Sprite*> GetSprites();

private:
	std::vector<GUIScreen*> m_Screens;
	int m_CurrentScreen = 0;

};
