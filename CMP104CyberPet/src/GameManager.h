#pragma once

#include "GUI/GUIScreen.h"
#include "GUI/GUIText.h"
#include "Pets/Pets.h"
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

	void SelectPet();
	void NextPet();

private:
	// cyber pet is only defined once we have chosen a pet
	// so we need to be careful not to reference it if is still nullptr
	CyberPet* m_CyberPet = nullptr;

	// for selecing the pet
	Sprite* m_Pets[7];
	int m_CurrentPet = 0;

	std::vector<GUIScreen*> m_Screens;
	int m_CurrentScreen = 0;

	std::vector<GUIText*> m_TextSprites;

	GUIText* m_PetName;
	GUIText* m_PetActivityText;

	GUIText* m_PetFeelingsLabel;
	GUIText* m_PetHungerText;
	GUIText* m_PetSleepinessText;

	GUIText* m_HungerBar;
	GUIText* m_SleepinessBar;
	GUIText* m_FunBar;
	GUIText* m_HappinessBar;

	bool m_Quit = false;

};
