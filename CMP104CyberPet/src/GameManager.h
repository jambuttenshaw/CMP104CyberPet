#pragma once

#include "GUI/GUIScreen.h"
#include "CyberPet.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update(float deltaTime);

	void AddGUIScreen(GUIScreen* screen);
	void LoadGUIScreen(int screenNum);

	std::vector<Sprite*> GetSprites();

private:
	CyberPet* m_CyberPet;

	std::vector<GUIScreen*> m_Screens;
	int m_CurrentScreen = 0;

};
