#include "GUIManager.h"

GUIManager::GUIManager()
{
	// create a test screen
	auto testScreen = new GUIScreen();
	auto testButton = new Button("Test Button");
	testButton->SetPosition({ 0, 0 });
	testScreen->AddButon(testButton);
	AddScreen(testScreen);
}

GUIManager::~GUIManager()
{
	for (GUIScreen* s : m_Screens)
	{
		delete s;
	}
	m_Screens.clear();
}

void GUIManager::Init()
{
	LoadScreen(0);
}

void GUIManager::AddScreen(GUIScreen* screen)
{
	m_Screens.push_back(screen);
}

void GUIManager::LoadScreen(int screenNum)
{
	m_CurrentScreen = screenNum;
	m_Screens[screenNum]->Load();
}

std::vector<Sprite*> GUIManager::GetSprites()
{
	return m_Screens[m_CurrentScreen]->GetButtonSprites();
}
