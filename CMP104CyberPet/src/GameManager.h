#pragma once

#include "GUI/GUIScreen.h"
#include "GUI/GUIText.h"
#include "Sprites/Pets.h"
#include "CyberPet.h"

#include "windows.h"

// this is where the magic happens
class GameManager
{
public:
	// constructor
	GameManager();
	// destructor
	~GameManager();

	// the big main update function that make stuff happen
	void Update(float deltaTime);

	// this adds everything that needs drawn into the render queue
	void Draw();

	// an event callback function for when a key is pressed
	void OnKeyEvent(KEY_EVENT_RECORD* e);

	// adds a new guiscreen into the list
	void AddGUIScreen(GUIScreen* screen);
	// loads a new gui screen by index
	void LoadGUIScreen(int screenNum);
	// moves onto the next screen
	// with a little check to make sure we wont pass out of bounds of the vector
	inline void NextScreen() { if (m_CurrentScreen < m_Screens.size() - 1) LoadGUIScreen(m_CurrentScreen + 1); }

	// check if it is time to quit the game
	inline bool TestQuitGame() { return m_Quit; }
	// this is when it is time to quit the game
	inline void Quit() { m_Quit = true; }

	// get a vector of pointers to all the sprites that need drawn this frame
	std::vector<Sprite*> GetSprites();

private:
	// creates a cool looking progress bar out of a value between 0 and 1
	std::string CreateProgressBar(float normalizedValue);

	// uses the currently selected pet to construct a cyberpet
	void SelectPet();
	// moves onto the next pet in the list
	void NextPet();

private:
	// cyber pet is only defined once we have chosen a pet
	// so we need to be careful not to reference it if is still nullptr
	CyberPet* m_CyberPet = nullptr;
	// the default position of the cyberpet
	Vector2f m_PetPosition = { 32, 8 };

	// for selecing the pet
	// there are 7 different pets to choose from
	Pet* m_Pets[7];
	// this is how many of them should be visible on screen at the moment
	std::vector<Sprite*> m_PetsToDisplay;
	// the pet that is currently being viewed
	int m_CurrentPet = 0;

	// a vector of pointers to all the screens that exist in the game
	std::vector<GUIScreen*> m_Screens;
	// the screen that is currently being viewed on the console
	int m_CurrentScreen = 0;

	// a vector of pointers to all the text that needs drawn onto the screen,
	// that isnt specific to a certain screen
	std::vector<GUIText*> m_TextSprites;

	// if the pets happiness is 0, then the owner has 10 seconds before the pet runs away
	float m_RunningAwayThreshold = 10;
	// this counts down until the pet runs away
	float m_RunningAwayTimer = 0;
	// this is true when happiness is 0 and the countdown has commenced
	bool m_WantingToRunAway = false;

	// a text object that displays the name of the pet
	GUIText* m_PetName;
	// a text object that displays what the pet is currently doing
	GUIText* m_PetActivityText;

	// a text object that displays how the pet is currently feeling
	GUIText* m_PetFeelingsLabel;
	// a text object that displays the description of the pets hunger
	GUIText* m_PetHungerText;
	// a text object that displays the description of the pets tiredness
	GUIText* m_PetSleepinessText;

	// a text object that displays the progress bar for the pets hunger
	GUIText* m_HungerBar;
	// a text object that displays the progress bar for the pets sleepiness
	GUIText* m_SleepinessBar;
	// a text object that displays the progress bar for the pets fun
	GUIText* m_FunBar;
	// a text object that displays the progress bar for the pets happiness
	GUIText* m_HappinessBar;

	// a text object that displays the message when the pet has ran away for a different owner
	// I HOPE YOU NEVER SEE THIS OBJECT IN ACTION!
	GUIText* m_PetRanAwayText;

	// a bool holding whether the application should quit or not
	bool m_Quit = false;

};
