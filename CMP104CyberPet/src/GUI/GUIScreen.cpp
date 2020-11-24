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

void GUIScreen::Load()
{
	m_Buttons[0]->SetActive(true);
	for (int i = 1; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->SetActive(false);
	}
}
