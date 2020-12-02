#pragma once

#include "Button.h"
#include "GUIText.h"

#include <vector>

// a GUIScreem is a container class that holds all the buttons and text
// that should be displayed on screen when this GUIScreen has been loaded
// it also handles scrolling through buttons and pressing them
class GUIScreen
{
public:
	// a quick enum for specifying which direction the buttons should be scrolled in
	// makes the code mode readable than just using integers, and more useful than using strings
	enum class ArrowDirection
	{
		Left, Right
	};

public:
	// constructor and destructor
	GUIScreen();
	~GUIScreen();

	// sets up the content of the screen ready to be used
	void Load();

	// event callback functions
	// on arrow key scrolls the buttons to the left or right depending on the direction passed in
	// on enter will call the buttons press function
	void OnArrowKey(ArrowDirection dir);
	void OnEnter();

	// used by the game manager to get everything in the screen that should be drawn this frame0
	std::vector<Sprite*> GetSprites();

	// adds a pointer to a new button or text object into their respective vectors
	inline void AddButon(Button* button) { m_Buttons.push_back(button); }
	inline void AddText(GUIText* text) { m_Text.push_back(text); }

	// returns the pointer at the specified index in the buttons or text vectors
	inline Button* GetButton(int index) { return m_Buttons[index]; }
	inline GUIText* GetText(int index) { return m_Text[index]; }

	// enable and disable is used to toggle whether the user can interact with the screen at this moment
	// when the screen is disabled, the buttons appear inactive and the user cannot scroll though buttons or press them
	inline void Enable() { m_Disabled = false; RefreshButtons(); }
	inline void Disable() { m_Disabled = true; RefreshButtons(); }
	inline bool GetDisabled() { return m_Disabled; }

private:
	// updates which button appears visually to be the selected button
	void RefreshButtons();

private:
	// a vector containing pointers to all the buttons that appear on this screen
	std::vector<Button*> m_Buttons;
	// the index of the button that is currently selected
	int m_SelectedButton = 0;

	// whether this screen is disabled or not
	bool m_Disabled = false;

	// a vector that holds pointers to every text object that should be displayed on this screen
	std::vector<GUIText*> m_Text;
};
