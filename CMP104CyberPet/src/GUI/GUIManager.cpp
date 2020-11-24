#include "GUIManager.h"

GUIManager::GUIManager()
{

}

GUIManager::~GUIManager()
{
	for (GUIScreen* s : m_Screens)
	{
		delete s;
	}
	m_Screens.clear();
}

std::vector<Sprite*> GUIManager::GetSprites()
{
	return m_Screens[m_CurrentScreen]->GetButtonSprites();
}
