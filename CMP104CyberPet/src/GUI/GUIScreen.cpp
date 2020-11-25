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
		if (m_SelectedButton == -1) m_SelectedButton = m_Buttons.size() - 1;
	}; break;
	case GUIScreen::ArrowDirection::Right:
	{
		m_SelectedButton++;
		if (m_SelectedButton == m_Buttons.size()) m_SelectedButton = 0;
	}; break;
	}

	RefreshButtons();
}

void GUIScreen::RefreshButtons()
{
	for (int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->SetActive(i == m_SelectedButton);
}
