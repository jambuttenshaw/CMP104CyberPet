#include "GameManager.h"

#include "Input/Input.h"
#include "Rendering/Renderer.h"

#include <iostream>


GameManager::GameManager()
{
	// initialize members
	std::vector<GUIScreen*> m_Screens(0);

	// set the event callback
	
	// the event callback function won't be executed within the game manager's scope,
	// it will be executed from inside the InputAPI

	// therefore, we need to use a lambda to capture the scope of the game manager so that members
	// of this class can be referenced inside the event callback function
	Input::SetEventCallback(
		// the event callback will always be passed a pointer to an input record
		// so we need to specify this as a parameter in the lambda
		// the lambda will return void, so we don't need to specify return type
		[this](KEY_EVENT_RECORD* e)
		{
			// now specify the actual on event function we want to call; GameManager::OnEvent();
			return this->OnKeyEvent(e); 
		}
	);

	/*
	------------------------------
	CREATING THE GAME SCREENS HERE
	------------------------------
	*/

	// SCREEN 1 - CHOOSING YOUR PET
	{
		auto screen = new GUIScreen();

		auto changePetButton = new Button("Change Pet");
		changePetButton->SetPosition({ 8, 18 });
		screen->AddButon(changePetButton);

		auto selectPetButton = new Button("Select Pet");
		selectPetButton->SetPosition({ 26, 18 });
		selectPetButton->SetPressFunction([this]() { this->NextScreen(); });
		screen->AddButon(selectPetButton);

		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 44, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		AddGUIScreen(screen);
	}


	// SCREEN 2 - NAMING YOUR PET
	{
		auto screen = new GUIScreen();

		auto namePetButton = new Button("Name Pet");
		namePetButton->SetPosition({ 8, 18 });
		screen->AddButon(namePetButton);

		auto confirmNameButton = new Button("Confirm Name");
		confirmNameButton->SetPosition({ 24, 18 });
		confirmNameButton->SetPressFunction([this]() { this->NextScreen(); });
		screen->AddButon(confirmNameButton);

		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 44, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		AddGUIScreen(screen);
	}


	// SCREEN 3 - ACTIVITIES WITH YOUR PET
	{
		auto screen = new GUIScreen();

		auto feedButton = new Button("Feed");
		feedButton->SetPosition({ 8, 18 });
		screen->AddButon(feedButton);

		auto napButton = new Button("Nap");
		napButton->SetPosition({ 20, 18 });
		screen->AddButon(napButton);

		auto playButton = new Button("Play");
		playButton->SetPosition({31, 18 });
		screen->AddButon(playButton);

		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 43, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		AddGUIScreen(screen);
	}


	// add instructions text
	m_TextSprites.push_back(new GUIText("Use A/D to scroll through buttons.", { 12, 22 }));
	m_TextSprites.push_back(new GUIText("Use Enter to select button.", { 12, 23 }));

	

	// add progress bars
	m_HungerBar = new GUIText("    Hunger: |----------|", { 64, 1 });
	m_TextSprites.push_back(m_HungerBar);

	m_SleepinessBar = new GUIText("Sleepiness: |----------|", { 64, 3 });
	m_TextSprites.push_back(m_SleepinessBar);

	m_HappinessBar = new GUIText(" Happiness: |----------|", { 64, 5 });
	m_TextSprites.push_back(m_HappinessBar);



	// load the first screen
	LoadGUIScreen(0);



	// SET UP THE CYBER PET SPRITE
	
	// create a new cyber pet object
	m_CyberPet = new CyberPet;
	m_CyberPet->SetPosition({ 15, 2 });

}

GameManager::~GameManager()
{
	for (GUIScreen* s : m_Screens)
	{
		delete s;
	}
	m_Screens.clear();

	// happiness bar etc are contained in text sprites,
	// so they get deleted along with everything else in the array
	for (GUIText* t : m_TextSprites)
	{
		delete t;
	}
	m_TextSprites.clear();

	delete m_CyberPet;
}


void GameManager::Update(float deltaTime)
{

	// THIS CODE GETS RUN EACH FRAME

	// update the pet
	m_CyberPet->Update(deltaTime);

	// update the progress bars
	m_HungerBar->SetString("    Hunger: " + CreateProgressBar(m_CyberPet->GetNormalizedHunger()));
	m_SleepinessBar->SetString("Sleepiness: " + CreateProgressBar(m_CyberPet->GetNormalizedSleepiness()));
	m_HappinessBar->SetString(" Happiness: " + CreateProgressBar(m_CyberPet->GetNormalizedHappiness()));

}

void GameManager::Draw()
{
	// add our pet to the render queue
	for (Sprite* s : GetSprites())
	{
		Renderer::Queue(s);
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
		case 13:	m_Screens[m_CurrentScreen]->OnEnter(); break;
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
	for (Sprite* s : m_TextSprites)
	{
		sprites.push_back(s);
	}
	sprites.push_back(m_CyberPet);

	return sprites;
}


std::string GameManager::CreateProgressBar(float normalizedValue)
{
	int n = (int)ceil(10.0f * normalizedValue);
	std::string s = "|";
	for (int i = 0; i < n; i++) s.append("#");
	for (int i = 0; i < 10 - n; i++) s.append("-");
	s.append("|");

	return s;
}
