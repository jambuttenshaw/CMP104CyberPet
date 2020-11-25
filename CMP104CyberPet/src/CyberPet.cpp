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
    if (m_State != State::Eating)
    {

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
