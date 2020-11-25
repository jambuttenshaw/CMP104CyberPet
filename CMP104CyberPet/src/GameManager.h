#pragma once

#include "GUI/GUIScreen.h"
#include "CyberPet.h"

#include "windows.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update(float deltaTime);
	void Draw();

	void OnKeyEvent(KEY_EVENT_RECORD* e);

	void AddGUIScreen(GUIScreen* screen);
	void LoadGUIScreen(int screenNum);

	std::vector<Sprite*> GetSprites();

private:
	CyberPet* m_CyberPet;

	std::vector<GUIScreen*> m_Screens;
	int m_CurrentScreen = 0;

};
