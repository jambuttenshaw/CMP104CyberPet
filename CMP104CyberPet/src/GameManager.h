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
	inline void NextScreen() { if (m_CurrentScreen < m_Screens.size() - 1) LoadGUIScreen(m_CurrentScreen + 1); }

	inline bool TestQuitGame() { return m_Quit; }
	inline void Quit() { m_Quit = true; }

	std::vector<Sprite*> GetSprites();

private:
	std::string CreateProgressBar(float normalizedValue);

private:
	CyberPet* m_CyberPet;

	std::vector<GUIScreen*> m_Screens;
	int m_CurrentScreen = 0;

	std::vector<GUIText*> m_TextSprites;

	GUIText* m_PetName;
	GUIText* m_PetActivityText;
	GUIText* m_HungerBar;
	GUIText* m_SleepinessBar;
	GUIText* m_FunBar;
	GUIText* m_HappinessBar;

	bool m_Quit = false;

};
