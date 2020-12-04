#include "GameManager.h"

#include "Input/Input.h"
#include "Rendering/Renderer.h"

#include <iostream>

GameManager::GameManager()
{
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

	I build each screen in its own scope
	since a lot of the local variables I only want to exist
	while the screen is being constructed

	Once the screen has been added to the game manager,
	everything is contained within the game manager so the 
	local variables are no longer needed and can be deleted

	Everything is still guarenteed to be freed from memory
	as references to each object are still stored within this game manager
	or within a GUIScreen, and will be processed and deleted when destructors are called
	*/

	// SCREEN 1 - CHOOSING YOUR PET
	{
		// create a new screen
		auto screen = new GUIScreen();

		// add a button, set the position and execution function and then add it to the screen
		auto changePetButton = new Button("Change Pet");
		changePetButton->SetPosition({ 8, 18 });
		// again using lambdas to capture the game managers scope
		// so I can reference members of this class within the lambda
		changePetButton->SetPressFunction([this]() { this->NextPet(); });
		screen->AddButon(changePetButton);

		// repeat this process for the next button
		auto selectPetButton = new Button("Select Pet");
		selectPetButton->SetPosition({ 26, 18 });
		selectPetButton->SetPressFunction([this]() { this->SelectPet(); });
		screen->AddButon(selectPetButton);

		// and again for the quit button
		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 44, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		// then add this screen into the game manager,
		// and the screen has been sorted!
		AddGUIScreen(screen);
	}


	// SCREEN 2 - NAMING YOUR PET
	{
		// create a new screen
		auto screen = new GUIScreen();

		// create a confirm name button
		auto confirmNameButton = new Button("Confirm Name");
		confirmNameButton->SetPosition({ 8, 18 });
		confirmNameButton->SetPressFunction([this]()
			{
				// before we set the name of the pet,
				// check to make sure its a valid name
				if (this->m_CyberPet->ValidName())
				{
					// fill in the strings on screen with the newly created pets name
					// just to make it look a little more personal
					this->m_PetName->ReplaceString(m_CyberPet->GetName());
					this->m_PetFeelingsLabel->ReplaceString(m_CyberPet->GetName() + " is currently feeling:");
					// then move onto the next screen
					this->NextScreen();
				}
			});
		// add the button into the screen
		screen->AddButon(confirmNameButton);

		// create the quit button the same as in the last screen
		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 28, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		// add some text to describe how to enter the pets name
		auto instructionText = new GUIText("Type to enter your pets name (Max length 24).", { 8, 14 });
		screen->AddText(instructionText);

		// and then add a text object to hold the WIP pets name
		auto nameText = new GUIText("Pet name: ", {14, 16});
		screen->AddText(nameText);

		// add this screen to the game manager
		AddGUIScreen(screen);
	}


	// SCREEN 3 - ACTIVITIES WITH YOUR PET
	{
		// create a new screen
		auto screen = new GUIScreen();

		// create a new button for feeding the pet
		// it should just call the set tate button on the cyber pet when pressed
		auto feedButton = new Button("Feed");
		feedButton->SetPosition({ 8, 18 });
		feedButton->SetPressFunction([this]() { this->m_CyberPet->SetState(CyberPet::State::Eating); });
		screen->AddButon(feedButton);

		// create a new button for napping in the same way
		auto napButton = new Button("Nap");
		napButton->SetPosition({ 20, 18 });
		napButton->SetPressFunction([this]() { this->m_CyberPet->SetState(CyberPet::State::Sleeping); });
		screen->AddButon(napButton);

		// and then again once more for sleeping
		auto playButton = new Button("Play");
		playButton->SetPosition({31, 18 });
		playButton->SetPressFunction([this]() { this->m_CyberPet->SetState(CyberPet::State::Playing); });
		screen->AddButon(playButton);

		// then create a quit button again
		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 43, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		// these member varialbes will exist outside of this scope
		// since we need to reference these later to update their contents

		// create text to hold what the pet us currently doing
		m_PetActivityText = new GUIText("The pet is currently neutral.", { 32,17 }, true);
		screen->AddText(m_PetActivityText);

		// create text to hold how the pet is currently feeling
		m_PetFeelingsLabel = new GUIText("The pet is currently feeling:", { 64, 14 });
		screen->AddText(m_PetFeelingsLabel);

		// create text to hold the pets description of its hunger
		m_PetHungerText = new GUIText(" - well fed.", { 64, 15 });
		screen->AddText(m_PetHungerText);

		// create text to hold the pets description of its sleepiness
		m_PetSleepinessText = new GUIText(" - wide awake", { 64, 16 });
		screen->AddText(m_PetSleepinessText);

		// add the screen to the game manager
		AddGUIScreen(screen);
	}


	// SCREEN 4 - GAME OVER
	{
		// create a new screen
		auto screen = new GUIScreen();

		// create a quit button, same as before
		auto quitButton = new Button("Quit");
		quitButton->SetPosition({ 8, 18 });
		quitButton->SetPressFunction([this]() { this->Quit(); });
		screen->AddButon(quitButton);

		// then add some text that tells you your pet ran away
		m_PetRanAwayText = new GUIText("Your pet has ran away.", { 32,17 }, true);
		screen->AddText(m_PetRanAwayText);

		// add the screen to the game manager
		AddGUIScreen(screen);
	}

	/*
	THESE OBJECTS EXIST ON EVERY SCREEN
	*/

	// add instructions text
	// this tells user how to use the project
	// fairly simple, theres only 3 keys to press
	// and the on screen buttons describe what they do
	m_TextSprites.push_back(new GUIText("Use arrow keys to scroll through buttons.", { 32, 23 }, true));
	m_TextSprites.push_back(new GUIText("Use enter to select button.", { 32, 24 }, true));
	
	// text to hold the pets name
	m_PetName = new GUIText("Your Pet", { 64, 3 });
	m_TextSprites.push_back(m_PetName);

	// add progress bars

	// a progress bar for pets hunger
	m_HungerBar = new GUIText("Hunger    : |----------|", { 64, 5 });
	m_TextSprites.push_back(m_HungerBar);

	// a progress bar for pets sleepiness
	m_SleepinessBar = new GUIText("Sleepiness: |----------|", { 64, 7 });
	m_TextSprites.push_back(m_SleepinessBar);

	// a progress bar for pets fun
	m_FunBar = new GUIText("Fun       : |##########|", { 64, 9 });
	m_TextSprites.push_back(m_FunBar);

	// a progress bar for pets happiness
	m_HappinessBar = new GUIText("Happiness : |##########|", { 64, 11 });
	m_TextSprites.push_back(m_HappinessBar);

	// a wee seperator for visuals
	// these dont change throughout the projects duration, they just make it look cooler
	m_TextSprites.push_back(new GUIText("------------------------", { 64, 2 }));
	m_TextSprites.push_back(new GUIText("------------------------", { 64, 4 }));
	m_TextSprites.push_back(new GUIText("------------------------", { 64, 12 }));


	// create the library of pets that the user can choose from
	// instantiate one of each type of pet
	m_Pets[0] = new Frog;
	m_Pets[1] = new Aardvark;
	m_Pets[2] = new Camel;
	m_Pets[3] = new Shark;
	m_Pets[4] = new Cat;
	m_Pets[5] = new Dog;
	m_Pets[6] = new Dolphin;

	// add the currently selected pet to the vector of pets to display
	m_PetsToDisplay.push_back(m_Pets[m_CurrentPet]);

	// load the first screen
	LoadGUIScreen(0);
}

GameManager::~GameManager()
{
	// delete all of the screens
	for (GUIScreen* s : m_Screens)
	{
		delete s;
	}
	// empty the vector of the screen pointers
	m_Screens.clear();

	// happiness bar etc are contained in text sprites,
	// so they get deleted along with everything else in the array
	for (GUIText* t : m_TextSprites)
	{
		delete t;
	}
	m_TextSprites.clear();

	// goodbye cyber pet
	delete m_CyberPet;
}


void GameManager::Update(float deltaTime)
{

	// THIS CODE GETS RUN EACH FRAME

	// check if we are in the main screen
	if (m_CurrentScreen == 2)
	{
		// this is the screen that we actually interact with the pet
		// so we only want to update the pet when were viewing this screen
		// the state of the pet should not change outwith this screen

		// update the pet
		m_CyberPet->Update(deltaTime);

		// check if the pet is really unhappy and wants to run away soon
		if (m_CyberPet->GetNormalizedHappiness() == 0)
		{
			// the pet does want to run away
			m_WantingToRunAway = true;

			// countdown the timer
			m_RunningAwayTimer += deltaTime;
			
			// display the timer for the pet running away on screen
			// in place of the activity the pet is currently doing
			m_PetActivityText->ReplaceString(m_CyberPet->GetName() + " will run away in " + std::to_string((int)(m_RunningAwayThreshold - (int)m_RunningAwayTimer)) + " seconds.");

			// uh oh - you're out of time to save the pet!
			if (m_RunningAwayTimer > m_RunningAwayThreshold)
			{
				// time to run away
				// switch to the game over screen

				// set the text to say the pet ran away
				m_PetRanAwayText->ReplaceString(m_CyberPet->GetName() + " ran away.");
				m_PetRanAwayText->SetCentrePosition({ 32, 17 });

				// then the pet should run off screen
				// we can use sprites lerping functionality to do that
				m_CyberPet->LerpToPosition({ -28, -15 });

				// then load up the game over screen
				LoadGUIScreen(3);
			}
		}
		else
		{
			// the pet is still happy and does not want to run away
			m_WantingToRunAway = false;
			m_RunningAwayTimer = 0;
		}

		// if the pet is not in its neutral state,
		// then we want the buttons to be disabled
		if (m_CyberPet->GetState() == CyberPet::State::Neutral)
		{
			// the pet is neutral
			// so enable the current screen
			if (m_Screens[m_CurrentScreen]->GetDisabled()) m_Screens[m_CurrentScreen]->Enable();
		}
		else
		{
			// the pet is busy and cannot take any more instructions at the moment:
			// disable the screen
			if (!m_Screens[m_CurrentScreen]->GetDisabled()) m_Screens[m_CurrentScreen]->Disable();
		}

		// update the progress bars
		// the create progress bar function gives a string for the graphics of the progress bar
		// we just pass in the stat we want to have a progress bar for and then give it a label

		// do this for each stat of the pet
		m_HungerBar->ReplaceString("Hunger    : " + CreateProgressBar(m_CyberPet->GetNormalizedHunger()));
		m_SleepinessBar->ReplaceString("Sleepiness: " + CreateProgressBar(m_CyberPet->GetNormalizedSleepiness()));
		m_FunBar->ReplaceString("Fun       : " + CreateProgressBar(m_CyberPet->GetNormalizedFun()));
		m_HappinessBar->ReplaceString("Happiness : " + CreateProgressBar(m_CyberPet->GetNormalizedHappiness()));

		// update the text with the pets current activity
		// but only of the pet is not wanting to run away
		if (!m_WantingToRunAway) m_PetActivityText->ReplaceString(m_CyberPet->GetName() + " is currently " + m_CyberPet->GetActivityString() + ".");
		// re-centre the text
		m_PetActivityText->SetCentrePosition({ 32, 16 });

		// set the descriptions of how the pet is currently feeling
		m_PetHungerText->ReplaceString(" - " + m_CyberPet->GetHungerString());
		m_PetSleepinessText->ReplaceString(" - " + m_CyberPet->GetSleepinessString());

	} else if (m_CurrentScreen == 1)
	{
		// the screen is the set pet name screen
		// we want to set the WIP pet name text to the text that has currently been entered into the pet name
		m_Screens[1]->GetText(1)->ReplaceString("Pet name: " + m_CyberPet->GetName());
	}
	else if (m_CurrentScreen == 0)
	{
		// the screen is the select pet screen

		// update each pet in the pets array
		for (Pet* p : m_Pets) p->Update(deltaTime);

		// check to see if there are any pets that we are currently rendering that we shouldnt be

		// even though we dont check which pet is active,
		// when you switch pet the active pet is added to the end of the array
		// so by iterating through in order
		// we will always remove the old pet if it is inactive first

		for (int i = 0; i < m_PetsToDisplay.size(); i++)
		{
			// we need to have at least 1 pet displayed on screen
			if (m_PetsToDisplay.size() > 1)
			{
				// if the pet is not moving, then we should erase it
				if (!m_PetsToDisplay[i]->IsLerping())
				{
					// erase takes an iterator of the pet to erase position
					// which is the start of the vector plus how many items we have iterated into it
					m_PetsToDisplay.erase(m_PetsToDisplay.begin() + i);
				}
			}
		}

	}
	else if (m_CurrentScreen == 3)
	{
		// if it is the game over screen we only want to update the pet
		// so it can move off screen
		m_CyberPet->Update(deltaTime);
	}
}

void GameManager::Draw()
{
	// adds everything that needs to be drawn into the render queue
	// get sprites gets all the sprites that need rendered
	for (Sprite* s : GetSprites())
	{
		// then add each of them to the renderers queue
		Renderer::Queue(s);
	}
}


void GameManager::OnKeyEvent(KEY_EVENT_RECORD* e)
{
	// this function is called every time a key on the keyboard is pressed
	// it allows us to deal with the event record e

	// if the key event is a keydown event pressing A/D or enter key,
	// we want to send an arrow press event or enter event onto the current gui scene
	
	// check to see if it was a key down or key up event
	if (e->bKeyDown)
	{
		// event is keydown event

		// get the key code of the key press
		// this allows us to use windows virtual key codes to identify what key was pressed
		unsigned short c = e->wVirtualKeyCode;

		switch (c)
		{
		// right arrow; send the event to the current screen and specify the direction
		case VK_RIGHT:	m_Screens[m_CurrentScreen]->OnArrowKey(GUIScreen::ArrowDirection::Right); return;
		// left arrow; send the event to the current screen and specify the direction
		case VK_LEFT:	m_Screens[m_CurrentScreen]->OnArrowKey(GUIScreen::ArrowDirection::Left); return;
		// enter key; call the on enter function of the current screen
		case VK_RETURN:	m_Screens[m_CurrentScreen]->OnEnter(); return;
		default:	break;
		}

		// when a key is pressed
		// we want to check if were on the pet naming screen
		// because we want to take key inputs and add them onto the pets name
		if (m_CurrentScreen == 1)
		{ 
			// the pets name can only contain letters
			// key codes referenced from https://docs.microsoft.com/en-gb/windows/win32/inputdev/virtual-key-codes
			// check it is a letter that was pressed, or the space
			if ((c >= 0x41 && c <= 0x5A) || c == VK_SPACE)
				// check to see that the pets name isnt too long already
				// if it isnt too long then add on the ASCII code of the pressed key onto the end of the pets name
				if (m_CyberPet->GetNameLength() < m_CyberPet->GetMaxNameLength())  m_CyberPet->AppendName(std::string(1, e->uChar.AsciiChar));

			// we also want backspace to delete the last letter
			if (c == VK_BACK)
				// if back space is pressed then remove the last letter from the pets name
				m_CyberPet->DeleteLastCharacter();
		}
	}
}

void GameManager::SelectPet()
{
	// the user has chosen which pet the want

	// create a new cyber pet object from the pet that the user selected
	m_CyberPet = new CyberPet(m_PetPosition, m_Pets[m_CurrentPet]);

	// move onto the pet naming screen
	NextScreen();

	// delete all of the pet objects: we dont need them anymore
	for (Pet* p : m_Pets) delete p;

	// remove all pointers from the pets to display array
	m_PetsToDisplay.clear();
}

void GameManager::NextPet()
{
	// move onto the next pet in the list

	// make the old one move off of the screen
	m_Pets[m_CurrentPet]->MoveOffScreen();

	// increment the currente pet
	m_CurrentPet++;
	// if the current pet is out of bounds of the size of the list,
	// then roll it around back to 0
	if (m_CurrentPet == sizeof(m_Pets) / sizeof(m_Pets[0])) m_CurrentPet = 0;
	
	// make the new pet move on the screen
	m_Pets[m_CurrentPet]->MoveOnScreen();
	// add it to the list of pets that need displayed
	m_PetsToDisplay.push_back(m_Pets[m_CurrentPet]);
}

void GameManager::AddGUIScreen(GUIScreen* screen)
{
	// add a new screen onto the vector of gui screens
	m_Screens.push_back(screen);
}

void GameManager::LoadGUIScreen(int screenNum)
{
	// set the current screen to the specified index,
	// then load that screen
	m_CurrentScreen = screenNum;
	m_Screens[screenNum]->Load();
}

std::vector<Sprite*> GameManager::GetSprites()
{
	// get all the sprites from the current screen
	std::vector<Sprite*> sprites = m_Screens[m_CurrentScreen]->GetSprites();
	// add all of the text sprites from this game manager
	for (Sprite* s : m_TextSprites) sprites.push_back(s);
	
	// if were on the pet select screen
	if (m_CurrentScreen == 0)
	{
		// add all of the pets that need displayed
		for (Sprite* s : m_PetsToDisplay) sprites.push_back(s);
	}
	else
	{
		// add all the cyberpets visual effect sprites
		for (Sprite* s : m_CyberPet->GetVisualEffectSprites()) sprites.push_back(s);
		// then add the cyberpet itself
		// do it in this order so that the cyberpet overwrites the visual effects if they overlap
		sprites.push_back(m_CyberPet);
	}

	// return the vector of sprites
	return sprites;
}


std::string GameManager::CreateProgressBar(float normalizedValue)
{
	// n is the number of #'s out of 10 in the progress bar
	// it is calculated simply like this
	int n = (int)ceil(10.0f * normalizedValue);
	
	// start the string with a pipe to contain the progress bar
	std::string s = "|";
	// add the correct amount of #'s
	for (int i = 0; i < n; i++) s.append("#");
	// fill the rest of the progress bar with -'s
	for (int i = 0; i < 10 - n; i++) s.append("-");
	// then close the progress bar with another pipe
	s.append("|");
	
	// return this constructed string
	return s;
}
