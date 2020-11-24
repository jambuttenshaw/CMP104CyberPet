#pragma once

#include "GUI/GUIScreen.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init();

	void AddScreen(GUIScreen* screen);
	void LoadScreen(int screenNum);

	std::vector<Sprite*> GetSprites();

private:
	std::vector<GUIScreen*> m_Screens;
	int m_CurrentScreen = 0;

};
