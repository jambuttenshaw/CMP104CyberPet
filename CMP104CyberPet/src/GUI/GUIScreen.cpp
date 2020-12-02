#include "GUIScreen.h"

// constructor just initializes the buttons as an empty vector
GUIScreen::GUIScreen()
	: m_Buttons(0)
{
}

// destructor deletes all the buttons and text objects stored in this screen
// and then empties the vectors of the pointers to the objects
// now that they have been deleted
GUIScreen::~GUIScreen()
{
	for (Button* b : m_Buttons)
	{
		delete b;
	}
	m_Buttons.clear();

	for (GUIText* t : m_Text)
	{
		delete t;
	}
	m_Text.clear();
}

// load this current screen
void GUIScreen::Load()
{
	// by default the first button is active
	m_SelectedButton = 0;
	// set the button to be graphically active
	m_Buttons[0]->SetActive(true);

	// loop through the rest of the buttons in the vector and set them all to inactive
	for (int i = 1; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->SetActive(false);
	}
}

// this function is called when an arrow key is pressed
void GUIScreen::OnArrowKey(GUIScreen::ArrowDirection dir)
{
	// we dont want the button to respond to events if its disabled
	if (m_Disabled) return;

	// switch on the direction
	switch (dir)
	{
		// if the left key is pressed
	case GUIScreen::ArrowDirection::Left:	
	{
		// decrease the selected button
		m_SelectedButton--;

		// if were out of range of the vector, then loop back around to the other side
		if (m_SelectedButton == -1) m_SelectedButton = (int)m_Buttons.size() - 1;
	}; break;

		// if the right arrow is pressed
	case GUIScreen::ArrowDirection::Right:
	{
		// increase the selected button
		m_SelectedButton++;
		// if were out of range of the vector then loop back around to the other side
		if (m_SelectedButton == (int)m_Buttons.size()) m_SelectedButton = 0;
	}; break;
	}

	// update the visual appearance of the buttons now that the selected button has changed
	RefreshButtons();
}

// called when the enter key is pressed
void GUIScreen::OnEnter()
{
	// we do not want to press the button if the screen is disabled
	if (m_Disabled) return;

	// call the press function on the selected button
	m_Buttons[m_SelectedButton]->Press();
}

// updates the visual appearance of each of the buttons
// so the user knows which one is currently selected
void GUIScreen::RefreshButtons()
{
	for (int i = 0; i < m_Buttons.size(); i++)
		// we only want the button to be displayed as active if it is the selected button,
		// and this screen is not disabled
		m_Buttons[i]->SetActive((i == m_SelectedButton) && (!m_Disabled));
}

// get all the sprites within this class that should be displayed this frame
std::vector<Sprite*> GUIScreen::GetSprites() 
{
	// create an empty vector
	std::vector<Sprite*> sprites(0);

	// add all the buttons
	for (Sprite* b : m_Buttons) sprites.push_back(b);

	// add all the text
	for (Sprite* t : m_Text) sprites.push_back(t);

	// return the sprites vector
	return sprites;
}
