#include "GUIScreen.h"

GUIScreen::GUIScreen()
	: m_Buttons(0)
{

}

GUIScreen::~GUIScreen()
{
	for (Button* b : m_Buttons)
	{
		delete b;
	}
	m_Buttons.clear();
}

std::vector<Sprite*> GUIScreen::GetButtonSprites()
{

}