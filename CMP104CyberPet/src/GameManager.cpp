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
		changePetButton->SetPressFunction([this]() { this->NextPet(); });
		screen->AddButon(changePetButton);

		auto selectPetButton = new Button("Select Pet");
		selectPetButton->SetPosition({ 26, 18 });
		selectPetButton->SetPressFunction([this]() { this->SelectPet(); });
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

		auto confirmNameButton = new Button("Confirm Name");
		confirmNameButton->SetPosition({ 8, 18 });
		confirmNameButton->SetPressFunction([this]()
			{
				if (this->m_CyberPet->ValidName())
				{
					this->m_PetName->ReplaceString(m_CyberPet->GetName());
					this->m_PetFeelingsLabel->ReplaceString(m_CyberPet->GetName() + " is currently feeling:");
					this->NextScreen();
				}
			});
		screen->AddButon(confirmNameButton);

		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 28, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		auto instructionText = new GUIText("Type to enter your pets name (Max length 24).", { 8, 14 });
		screen->AddText(instructionText);

		auto nameText = new GUIText("Pet name: ", {14, 16});
		screen->AddText(nameText);

		AddGUIScreen(screen);
	}


	// SCREEN 3 - ACTIVITIES WITH YOUR PET
	{
		auto screen = new GUIScreen();

		auto feedButton = new Button("Feed");
		feedButton->SetPosition({ 8, 18 });
		feedButton->SetPressFunction([this]() { this->m_CyberPet->SetState(CyberPet::State::Eating); });
		screen->AddButon(feedButton);

		auto napButton = new Button("Nap");
		napButton->SetPosition({ 20, 18 });
		napButton->SetPressFunction([this]() { this->m_CyberPet->SetState(CyberPet::State::Sleeping); });
		screen->AddButon(napButton);

		auto playButton = new Button("Play");
		playButton->SetPosition({31, 18 });
		playButton->SetPressFunction([this]() { this->m_CyberPet->SetState(CyberPet::State::Playing); });
		screen->AddButon(playButton);

		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 43, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		m_PetActivityText = new GUIText("The pet is currently neutral.", { 32,17 }, true);
		screen->AddText(m_PetActivityText);

		m_PetFeelingsLabel = new GUIText("The pet is currently feeling:", { 64, 14 });
		screen->AddText(m_PetFeelingsLabel);

		m_PetHungerText = new GUIText(" - well fed.", { 64, 15 });
		screen->AddText(m_PetHungerText);

		m_PetSleepinessText = new GUIText(" - wide awake", { 64, 16 });
		screen->AddText(m_PetSleepinessText);

		AddGUIScreen(screen);
	}


	// SCREEN 4 - GAME OVER
	{
		auto screen = new GUIScreen();

		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 8, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		m_PetRanAwayText = new GUIText("Your pet has ran away.", { 32,17 }, true);
		screen->AddText(m_PetRanAwayText);

		AddGUIScreen(screen);
	}


	// add instructions text
	m_TextSprites.push_back(new GUIText("Use arrow keys to scroll through buttons.", { 32, 23 }, true));
	m_TextSprites.push_back(new GUIText("Use enter to select button.", { 32, 24 }, true));

	
	// a title for the pets name
	m_PetName = new GUIText("Your Pet", { 64, 3 });
	m_TextSprites.push_back(m_PetName);

	// add progress bars
	m_HungerBar = new GUIText("Hunger    : |----------|", { 64, 5 });
	m_TextSprites.push_back(m_HungerBar);

	m_SleepinessBar = new GUIText("Sleepiness: |----------|", { 64, 7 });
	m_TextSprites.push_back(m_SleepinessBar);

	m_FunBar = new GUIText("Fun       : |##########|", { 64, 9 });
	m_TextSprites.push_back(m_FunBar);

	m_HappinessBar = new GUIText("Happiness : |##########|", { 64, 11 });
	m_TextSprites.push_back(m_HappinessBar);

	// a wee seperator for visuals
	m_TextSprites.push_back(new GUIText("------------------------", { 64, 2 }));
	m_TextSprites.push_back(new GUIText("------------------------", { 64, 4 }));
	m_TextSprites.push_back(new GUIText("------------------------", { 64, 12 }));


	// create the library of pets that the user can choose from
	m_Pets[0] = new Frog;
	m_Pets[1] = new Aardvark;
	m_Pets[2] = new Camel;
	m_Pets[3] = new Shark;
	m_Pets[4] = new Cat;
	m_Pets[5] = new Dog;
	m_Pets[6] = new Dolphin;
	

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

	
	if (m_CurrentScreen == 2)
	{
		// this is the screen that we actually interact with the pet
		// so we only want to update the pet when were viewing this screen

		// update the pet
		m_CyberPet->Update(deltaTime);

		// check if the pet is really unhappy and wants to run away soon
		if (m_CyberPet->GetNormalizedHappiness() == 0)
		{
			m_WantingToRunAway = true;

			m_RunningAwayTimer += deltaTime;
			
			m_PetActivityText->ReplaceString(m_CyberPet->GetName() + " will run away in " + std::to_string((int)(m_RunningAwayThreshold - (int)m_RunningAwayTimer)) + " seconds.");

			if (m_RunningAwayTimer > m_RunningAwayThreshold)
			{
				// time to run away
				// switch to the game over screen
				m_PetRanAwayText->ReplaceString(m_CyberPet->GetName() + " ran away.");
				m_PetRanAwayText->SetCentrePosition({ 32, 17 });
				LoadGUIScreen(3);
			}
		}
		else
		{
			m_WantingToRunAway = false;
			m_RunningAwayTimer = 0;
		}

		// if the pet is not in its neutral state,
		// then we want the buttons to be disabled
		if (m_CyberPet->GetState() == CyberPet::State::Neutral)
		{
			if (m_Screens[m_CurrentScreen]->GetDisabled()) m_Screens[m_CurrentScreen]->Enable();
		}
		else
		{
			if (!m_Screens[m_CurrentScreen]->GetDisabled()) m_Screens[m_CurrentScreen]->Disable();
		}

		// update the progress bars
		
		m_HungerBar->ReplaceString("Hunger    : " + CreateProgressBar(m_CyberPet->GetNormalizedHunger()));
		m_SleepinessBar->ReplaceString("Sleepiness: " + CreateProgressBar(m_CyberPet->GetNormalizedSleepiness()));
		m_FunBar->ReplaceString("Fun       : " + CreateProgressBar(m_CyberPet->GetNormalizedFun()));
		m_HappinessBar->ReplaceString("Happiness : " + CreateProgressBar(m_CyberPet->GetNormalizedHappiness()));

		if (!m_WantingToRunAway) m_PetActivityText->ReplaceString(m_CyberPet->GetName() + " is currently " + m_CyberPet->GetActivityString() + ".");
		m_PetActivityText->SetCentrePosition({ 32, 16 });

		m_PetHungerText->ReplaceString(" - " + m_CyberPet->GetHungerString());
		m_PetSleepinessText->ReplaceString(" - " + m_CyberPet->GetSleepinessString());

	} else if (m_CurrentScreen == 1)
	{
		m_Screens[1]->GetText(1)->ReplaceString("Pet name: " + m_CyberPet->GetName());
	}
	else if (m_CurrentScreen == 0)
	{
		for (Sprite* p : m_Pets) p->Update(deltaTime);
	}
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
		unsigned short c = e->wVirtualKeyCode;

		switch (c)
		{
		// right arrow
		case VK_RIGHT:	m_Screens[m_CurrentScreen]->OnArrowKey(GUIScreen::ArrowDirection::Right); break;
		// left arrow
		case VK_LEFT:	m_Screens[m_CurrentScreen]->OnArrowKey(GUIScreen::ArrowDirection::Left); break;
		// enter key
		case VK_RETURN:	m_Screens[m_CurrentScreen]->OnEnter(); break;
		default:	break;
		}

		// when a key is pressed
		// we want to check if were on the pet naming screen
		// because we want to take key inputs and add them onto the pets name
		if (m_CurrentScreen == 1)
		{ 
			// the pets name can only contain letters
			// key codes referenced from https://docs.microsoft.com/en-gb/windows/win32/inputdev/virtual-key-codes
			if ((c >= 0x41 && c <= 0x5A) || c == VK_SPACE)
				if (m_CyberPet->GetNameLength() < m_CyberPet->GetMaxNameLength())  m_CyberPet->AppendName(std::string(1, e->uChar.AsciiChar));

			// we also want backspace to delete the last letter
			if (c == VK_BACK)
				m_CyberPet->DeleteLastCharacter();
		}
	}
}

void GameManager::SelectPet()
{
	// create a new cyber pet object
	m_CyberPet = new CyberPet(m_PetPosition, m_Pets[m_CurrentPet]);

	NextScreen();

	for (Sprite* p : m_Pets)
	{
		delete p;
	}
}

void GameManager::NextPet()
{
	m_CurrentPet++;
	if (m_CurrentPet == sizeof(m_Pets) / sizeof(m_Pets[0])) m_CurrentPet = 0;
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
	std::vector<Sprite*> sprites = m_Screens[m_CurrentScreen]->GetSprites();
	for (Sprite* s : m_TextSprites) sprites.push_back(s);
	
	if (m_CurrentScreen == 0)
		sprites.push_back(m_Pets[m_CurrentPet]);
	else if (m_CurrentScreen < 3)
	{
		for (Sprite* s : m_CyberPet->GetVisualEffectSprites()) sprites.push_back(s);
		sprites.push_back(m_CyberPet);
	}

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
