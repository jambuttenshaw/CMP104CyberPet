#include "CyberPet.h"

// take in the initial position of the pet
CyberPet::CyberPet(Vector2f initalPos)
	: Sprite(), m_InitialPosition(initalPos)
{
    // this is a default constructor that defaults to a frog
    // when a pet is not specified to construct from
	SetImage(new Image(21, 6, R"(       _     _       
      (')-=-(')      
    __(   "   )__    
   / _/'-----'\_ \   
___\\ \\     // //___
>____)/_\---/_\(____<)"));

    // call init
    Init();
}

// take in the initial pos and a pet to take the image from
CyberPet::CyberPet(Vector2f initalPos, Sprite* pet)
    : Sprite(), m_InitialPosition(initalPos)
{
    // copy the image from the pet
    // use the copy constructor of the image class
    // this will give the cyberpet the same image as the pet, but the image will be in a different location in memory
    // so when we delete the pets the cyberpet wont lose its image
    SetImage(new Image(*pet->GetImage()));

    // call init
    Init();
}

void CyberPet::Init()
{
    // set the position of the sprite
    SetCentrePosition(m_InitialPosition);

    // set the location that the food effects will move to
    m_FoodDestination =
    {
        (m_InitialPosition.x - GetImage()->GetWidth() * 0.5f) - 2,
        m_InitialPosition.y,
    };

    // set the location that the Z's will originate from
    m_SleepingZSpawnLocation =
    {
        m_InitialPosition.x,
        m_InitialPosition.y - GetImage()->GetHeight() * 0.5f,
    };
}

CyberPet::~CyberPet()
{
    // delete any visual effects sprites that may exist
    for (VisualEffectSprite* s : m_VisualEffectsSprites)
    {
        delete s;
    }
    // and clear the vector of the pointers
    m_VisualEffectsSprites.clear();
}

// the big update function
// take in the time elapsed since last frame
void CyberPet::Update(float deltaTime)
{
    // call the base class update function
    Sprite::Update(deltaTime);

    // update all the visual effects sprites in the container
    for (VisualEffectSprite* s : m_VisualEffectsSprites)
    {
        s->Update(deltaTime);
        // if any of them have reached their destination,
        // then move them back to the start and make them move again
        if (!s->IsLerping()) s->Reset();
    }

    // if the pet is doing anything other than sitting about
    if (m_State != State::Neutral)
    {
        // update the timer with how long it is until the pet is neutral again
        m_ReturnToNeutralTimer -= deltaTime;

        // its time to go back to neutral!
        if (m_ReturnToNeutralTimer <= 0)
        {
            // stop the previous states visual effects
            // if the sprite was playing we want to make sure its back in the right place
            if (m_State == State::Playing)
            {
                // set it back to the initial position
                SetCentrePosition(m_InitialPosition);
            }

            // delete any visual effects sprites that are kicking about
            for (VisualEffectSprite* s : m_VisualEffectsSprites) delete s;
            m_VisualEffectsSprites.clear();

            // and set the state to neutral
            m_State = State::Neutral;
        }
    }


    // the pet is having a snack
    if (m_State == State::Eating)
    {
        // decrease the hunger by how quick the pet eats
        m_Hunger -= m_EatingSpeed * deltaTime;
        // make sure the hunger doesnt pass below 0 cause that wouldnt make sense
        if (m_Hunger < 0)
        {
            m_Hunger = 0;
        }
    }
    else
    {
        // only get hungrier if the pet isnt eating
        // increase the hunger by the increase rate
        m_Hunger += m_HungerPerSecond * deltaTime;
        // dont let the hunger exceed the max hunger or else weird things will happen
        // (the happiness would become negative)
        if (m_Hunger > m_MaxHunger) m_Hunger = m_MaxHunger;
    }
    


    // the pet is napping
    if (m_State == State::Sleeping)
    {
        // get less sleepy as the pet is napping
        m_Sleepiness -= m_SleepingSpeed * deltaTime;
        // but the pet cant get less sleepy than completely awake
        if (m_Sleepiness < 0)
        {
            m_Sleepiness = 0;
        }
    }
    else
    {
        // only get sleepier if the pet isnt sleeping
        // increase the hunger by the increase rate
        m_Sleepiness += m_SleepinessPerSecond * deltaTime;
        // dont let the sleepiness exceed the max sleepiness
        if (m_Sleepiness > m_MaxSleepiness) m_Sleepiness = m_MaxSleepiness;
    }


    // the pet is having some fun
    if (m_State == State::Playing)
    {
        // increase the fun by how much its playing
        m_Fun += m_PlayingSpeed * deltaTime;
        // dont let the fun exceed the maximum though
        if (m_Fun > m_MaxFun)
            m_Fun = m_MaxFun;

        // visual effects:
        // the pet should move about in a figure of 8
        // the pet moves according to the parametric equation:
        // x = 4a * sin(t)
        // y = a * sin(t) * cos(t)
        // where a is the amplitude of the motion
        // this creates a very elongated figure of 8

        // work out how long the pet has been playing for the t value
        float t = (m_TimeUntilNeutral - m_ReturnToNeutralTimer) * m_PlayMoveSpeed;
        // then set the position according to the equation
        SetCentrePosition({
                m_InitialPosition.x + (4 * m_PlayMoveAmplitude * (float)sin(t)),
                m_InitialPosition.y + (m_PlayMoveAmplitude * (float)sin(t) * (float)cos(t))
            });
    }
    else
    {
        // decrease the fun if the pet is not playing
        m_Fun -= m_FunPerSecond * deltaTime;
        // but dont let it go below 0
        if (m_Fun < 0) m_Fun = 0;
    }


    // this formula means that happiness decreases as hunger or sleepiness increases and increases with fun, 
    // and if hunger OR sleepiness reach their maximum OR fun reaches a minimum then happiness is 0
    m_Happiness = (float)sqrt((m_MaxHunger - m_Hunger) * (m_MaxSleepiness - m_Sleepiness) * m_Fun / m_MaxHappiness);
}

// set the current state of the pet
void CyberPet::SetState(State state)
{
    // set the state
    m_State = state;
    // initialize the timer
    m_ReturnToNeutralTimer = m_TimeUntilNeutral;

    // if the pet has just started eating
    // then bring in the carrot effects
    if (state == State::Eating)
        m_VisualEffectsSprites.push_back(new Carrot(m_FoodSpawnLocation, m_FoodDestination));
    else if (state == State::Sleeping)
        // if the pet is sleeping then create the sleeping Z effect
        m_VisualEffectsSprites.push_back(new SleepingZ(m_SleepingZSpawnLocation, m_SleepingZDestination));
}   

std::string CyberPet::GetActivityString()
{
    // get a string to describe what the pet is currently doing
    // the string is unique to each activity
    switch (m_State)
    {
    case State::Neutral:        return "doing nothing"; break;
    case State::Eating:         return "eating"; break;
    case State::Sleeping:       return "sleeping"; break;
    case State::Playing:        return "playing"; break;
    }

    // just in case something goes wrong
    return "doing something unknown";
}

std::string CyberPet::GetHungerString()
{
    // create a string to describe how hungry the pet is
    // if the pet is more than 99% hungry it is dying
    // if it is between 75% and 99% then it is starving
    // if it is between 50% and 75% it is rather hungry
    // if it is between 20% and 50% it is slightly peckish
    // if it is 20% or less then it is well fed

    float percentageHunger = GetNormalizedHunger();
    if (percentageHunger > 0.99f)
        return "dying";
    else if (percentageHunger > 0.75f)
        return "starving";
    else if (percentageHunger > 0.5f)
        return "rather hungry";
    else if (percentageHunger > 0.2f)
        return "slightly peckish";
    else
        return "well fed";
}

std::string CyberPet::GetSleepinessString()
{
    // create a string to describe how sleepy the pet is
    // if the pet is more than 99% sleepy it is collapsing
    // if it is between 75% and 99% then it is falling asleep
    // if it is between 50% and 75% it is tired
    // if it is between 20% and 50% it is awake
    // if it is 20% or less then it is wide awake
    float percentageSleepiness = GetNormalizedSleepiness();
    if (percentageSleepiness > 0.99f)
        return "collapsing";
    else if (percentageSleepiness > 0.75f)
        return "falling asleep";
    else if (percentageSleepiness > 0.5f)
        return "tired";
    else if (percentageSleepiness > 0.2f)
        return "awake";
    else
        return "wide awake";
}

std::vector<Sprite*> CyberPet::GetVisualEffectSprites()
{
    // we need to get a vector of sprite pointers
    // currently we have a vector of VisualEffectSprite pointers
    // but as that inherits from sprite we just need to create a new vector
    // and add them all into it
    std::vector<Sprite*> sprites(0);
    for (Sprite* s : m_VisualEffectsSprites) sprites.push_back(s);
    return sprites;
}
