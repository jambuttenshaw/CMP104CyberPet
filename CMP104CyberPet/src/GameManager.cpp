#include "GameManager.h"

GameManager::GameManager()
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

GameManager::~GameManager()
{
	for (GUIScreen* s : m_Screens)
	{
		delete s;
	}
	m_Screens.clear();
}

void GameManager::Init()
{
	LoadScreen(0);
}

void GameManager::AddScreen(GUIScreen* screen)
{
	m_Screens.push_back(screen);
}

void GameManager::LoadScreen(int screenNum)
{
	m_CurrentScreen = screenNum;
	m_Screens[screenNum]->Load();
}

std::vector<Sprite*> GameManager::GetSprites()
{
	return m_Screens[m_CurrentScreen]->GetButtonSprites();
}
