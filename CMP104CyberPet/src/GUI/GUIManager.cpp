#include "GUIManager.h"

GUIManager::GUIManager()
{
	// create a test screen
	auto testScreen = new GUIScreen();

	auto testButton1 = new Button("Rest the pet");
	testButton1->SetPosition({ 0, 20 });
	testScreen->AddButon(testButton1);

	auto testButton2 = new Button("Feed the pet");
	testButton2->SetPosition({ 20, 20 });
	testScreen->AddButon(testButton2);

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
