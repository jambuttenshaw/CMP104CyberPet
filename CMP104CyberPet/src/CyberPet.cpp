#include "CyberPet.h"

#include <iostream>

CyberPet::CyberPet(Vector2f initalPos)
	: Sprite(), m_InitialPosition(initalPos)
{
    // this is a default constructor that defaults to a frog
	SetImage(new Image(21, 6, R"(       _     _       
      (')-=-(')      
    __(   "   )__    
   / _/'-----'\_ \   
___\\ \\     // //___
>____)/_\---/_\(____<)"));
    Init();
}

CyberPet::CyberPet(Vector2f initalPos, Sprite* pet)
    : Sprite(), m_InitialPosition(initalPos)
{
    // copy the image from the pet
    SetImage(new Image(*pet->GetImage()));
    Init();
}

void CyberPet::Init()
{
    SetCentrePosition(m_InitialPosition);

    std::vector<VisualEffectSprite*> m_VisualEffectsSprites(0);

    m_FoodDestination =
    {
        (m_InitialPosition.x - GetImage()->GetWidth() * 0.5f) - 2,
        m_InitialPosition.y,
    };
}

CyberPet::~CyberPet()
{

}

void CyberPet::Update(float deltaTime)
{
    Sprite::Update(deltaTime);

    for (VisualEffectSprite* s : m_VisualEffectsSprites) s->Update(deltaTime);

    if (m_State != State::Neutral)
    {
        m_ReturnToNeutralTimer -= deltaTime;
        if (m_ReturnToNeutralTimer <= 0)
        {
            // stop the previous states visual effects
            if (m_State == State::Playing)
            {
                SetCentrePosition(m_InitialPosition);
            }

            // delete any visual effects sprites that are kicking about
            for (VisualEffectSprite* s : m_VisualEffectsSprites) delete s;
            m_VisualEffectsSprites.clear();

            m_State = State::Neutral;
        }

        if (m_State == State::Eating)
        {
            for (VisualEffectSprite* s : m_VisualEffectsSprites)
            {
                if (!s->IsLerping())
                {
                    // if the current state is eating,
                    // then the only visual effect sprites that can exist must be carrots
                    // so we are safe to call this dynamic cast on the sprite pointer to access the reset function
                    s->Reset();
                }
            }
        }
    }



    if (m_State == State::Eating)
    {
        m_Hunger -= m_EatingSpeed * deltaTime;
        if (m_Hunger < 0)
            m_Hunger = 0;
    }
    else
    {
        // only get hungrier if the pet isnt eating
        // increase the hunger by the increase rate
        m_Hunger += m_HungerPerSecond * deltaTime;
        if (m_Hunger > m_MaxHunger) m_Hunger = m_MaxHunger;
    }
    



    if (m_State == State::Sleeping)
    {
        m_Sleepiness -= m_SleepingSpeed * deltaTime;
        if (m_Sleepiness < 0)
            m_Sleepiness = 0;
    }
    else
    {
        // only get sleepier if the pet isnt sleeping
        // increase the hunger by the increase rate
        m_Sleepiness += m_SleepinessPerSecond * deltaTime;
        if (m_Sleepiness > m_MaxSleepiness) m_Sleepiness = m_MaxSleepiness;
    }


    if (m_State == State::Playing)
    {
        m_Fun += m_PlayingSpeed * deltaTime;
        if (m_Fun > m_MaxFun)
            m_Fun = m_MaxFun;

        // visual effects:
        // the pet should move about in a figure of 8
        float t = (m_TimeUntilNeutral - m_ReturnToNeutralTimer) * m_PlayMoveSpeed;
        SetCentrePosition({
                m_InitialPosition.x + (4 * m_PlayMoveAmplitude * (float)sin(t)),
                m_InitialPosition.y + (m_PlayMoveAmplitude * (float)sin(t) * (float)cos(t))
            });
    }
    else
    {
        m_Fun -= m_FunPerSecond * deltaTime;
        if (m_Fun < 0) m_Fun = 0;
    }


    // this formula means that happiness decreases as hunger or sleepiness increases and increases with fun, 
    // and if hunger OR sleepiness reach their maximum OR fun reaches a minimum then happiness is 0
    m_Happiness = (float)sqrt((m_MaxHunger - m_Hunger) * (m_MaxSleepiness - m_Sleepiness) * m_Fun / m_MaxHappiness);
}

void CyberPet::SetState(State state)
{
    m_State = state;
    m_ReturnToNeutralTimer = m_TimeUntilNeutral;

    if (state == State::Eating)
    {
        m_VisualEffectsSprites.push_back(new Carrot(m_FoodSpawnLocation, m_FoodDestination));
    }
}

std::string CyberPet::GetActivityString()
{
    switch (m_State)
    {
    case State::Neutral:        return "doing nothing"; break;
    case State::Eating:         return "eating"; break;
    case State::Sleeping:       return "sleeping"; break;
    case State::Playing:        return "playing"; break;
    }

    return "doing something unknown";
}

std::string CyberPet::GetHungerString()
{
    // the activity string is composed of 2 parts
    // the activity that the pet is currently doing, and how the pet is currently feeling

    // create a string to describe how hungry the pet is
    float percentageHunger = GetNormalizedHunger();
    if (percentageHunger > 0.99f)
        return "dying";
    else if (percentageHunger > 0.75f)
        return "starving";
    else if (percentageHunger > 0.5f)
        return "rather hungry";
    else if (percentageHunger > 0.25f)
        return "slightly peckish";
    else
        return "well fed";
}

std::string CyberPet::GetSleepinessString()
{
    float percentageSleepiness = GetNormalizedSleepiness();
    if (percentageSleepiness > 0.99f)
        return "collapsing";
    else if (percentageSleepiness > 0.75f)
        return "falling asleep";
    else if (percentageSleepiness > 0.5f)
        return "tired";
    else if (percentageSleepiness > 0.25f)
        return "awake";
    else
        return "wide awake";
}

std::vector<Sprite*> CyberPet::GetVisualEffectSprites()
{
    std::vector<Sprite*> sprites(0);
    for (Sprite* s : m_VisualEffectsSprites) sprites.push_back(s);
    return sprites;
}
