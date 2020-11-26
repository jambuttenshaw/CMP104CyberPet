#include "GUIScreen.h"

#include <iostream>

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

	for (GUIText* t : m_Text)
	{
		delete t;
	}
	m_Text.clear();
}

void GUIScreen::Load()
{
	m_SelectedButton = 0;
	m_Buttons[0]->SetActive(true);
	for (int i = 1; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->SetActive(false);
	}
}

void GUIScreen::OnArrowKey(GUIScreen::ArrowDirection dir)
{
	switch (dir)
	{
	case GUIScreen::ArrowDirection::Left:	
	{
		m_SelectedButton--;
		if (m_SelectedButton == -1) m_SelectedButton = (int)m_Buttons.size() - 1;
	}; break;
	case GUIScreen::ArrowDirection::Right:
	{
		m_SelectedButton++;
		if (m_SelectedButton == (int)m_Buttons.size()) m_SelectedButton = 0;
	}; break;
	}

	RefreshButtons();
}

void GUIScreen::OnEnter()
{
	m_Buttons[m_SelectedButton]->Press();
}

void GUIScreen::RefreshButtons()
{
	for (int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->SetActive(i == m_SelectedButton);
}

std::vector<Sprite*> GUIScreen::GetSprites() 
{
	std::vector<Sprite*> sprites(0);
	for (Sprite* b : m_Buttons) sprites.push_back(b);
	for (Sprite* t : m_Text) sprites.push_back(t);

	return sprites;
}
