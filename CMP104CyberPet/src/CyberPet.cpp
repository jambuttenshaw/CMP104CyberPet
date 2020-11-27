#include "CyberPet.h"

CyberPet::CyberPet()
	: Sprite()
{
	SetImage(new Image(21, 6, R"(       _     _       
      (')-=-(')      
    __(   "   )__    
   / _/'-----'\_ \   
___\\ \\     // //___
>____)/_\---/_\(____<)"));

}

CyberPet::~CyberPet()
{

}

void CyberPet::Update(float deltaTime)
{
    if (m_State != State::Neutral)
    {
        m_ReturnToNeutralTimer -= deltaTime;
        if (m_ReturnToNeutralTimer <= 0)
            m_State = State::Neutral;
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

    // this formula means that happiness decreases as hunger or sleepiness increases, 
    // and if hunger OR sleepiness reach their maximum then happiness is 0
    m_Happiness = (m_MaxHunger - m_Hunger) * (m_MaxSleepiness - m_Sleepiness) / m_MaxHappiness;
}

void CyberPet::SetState(State state)
{
    m_State = state;
    m_ReturnToNeutralTimer = m_TimeUntilNeutral;
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

    return "something unknown";

}
