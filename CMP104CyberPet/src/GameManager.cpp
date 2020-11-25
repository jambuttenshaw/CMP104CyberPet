#include "GameManager.h"

#include "Input/Input.h"

#include <iostream>



#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }



GameManager::GameManager()
{
	// initialize members
	std::vector<GUIScreen*> m_Screens(0);

	// set the event callback
	Input::SetEventCallback(BIND_EVENT_FN(GameManager::OnEvent));

	// create a new cyber pet object
	m_CyberPet = new CyberPet;




	// create a test screen
	auto testScreen = new GUIScreen();

	auto testButton1 = new Button("Rest the pet");
	testButton1->SetPosition({ 0, 20 });
	testScreen->AddButon(testButton1);

	auto testButton2 = new Button("Feed the pet");
	testButton2->SetPosition({ 20, 20 });
	testScreen->AddButon(testButton2);

	AddGUIScreen(testScreen);


	// load the first screen
	LoadGUIScreen(0);
}

GameManager::~GameManager()
{
	for (GUIScreen* s : m_Screens)
	{
		delete s;
	}
	m_Screens.clear();

	delete m_CyberPet;
}


void GameManager::Update(float deltaTime)
{

}


void GameManager::OnEvent(INPUT_RECORD* e)
{
	// all events go through this event callback function
	switch (e->EventType)
	{
	case KEY_EVENT:		OnKeyEvent(&e->Event.KeyEvent);
	}
}

void GameManager::OnKeyEvent(KEY_EVENT_RECORD* e)
{
	// if the key event is a keydown event pressing A/D or enter key,
	// we want to send an arrow press event or enter event onto the current gui scene
	
	if (e->bKeyDown)
	{
		// event is keydown event
		switch (e->uChar.AsciiChar)
		{
		// D key
		case 100:	m_Screens[m_CurrentScreen]->OnArrowKey(GUIScreen::ArrowDirection::Right); break;
		// A key
		case 97:	m_Screens[m_CurrentScreen]->OnArrowKey(GUIScreen::ArrowDirection::Left); break;
		// enter key
		case 13:	break;
		default:	break;
		}
	}
}

void GameManager::AddGUIScreen(GUIScreen* screen)
{
	m_Screens.push_back(screen);
}

void GameManager::LoadGUIScreen(int screenNum)
{
	m_CurrentScreen = screenNum;
	m_Screens[screenNum]->Load();
}

std::vector<Sprite*> GameManager::GetSprites()
{
	std::vector<Sprite*> sprites = m_Screens[m_CurrentScreen]->GetButtonSprites();
	sprites.push_back(m_CyberPet);

	return sprites;
}
