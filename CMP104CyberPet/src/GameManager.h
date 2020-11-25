#pragma once

#include "GUI/GUIScreen.h"
#include "GUI/GUIText.h"
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

	std::vector<GUIText*> m_TextSprites;
	GUIText* m_HungerBar;
	GUIText* m_SleepinessBar;
	GUIText* m_HappinessBar;

};
