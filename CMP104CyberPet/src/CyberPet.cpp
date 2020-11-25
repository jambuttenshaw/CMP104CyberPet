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
    // increase the hunger and sleepiness by their second-ly rates
    m_Hunger += m_HungerPerSecond * deltaTime;
    m_Sleepiness += m_SleepinessPerSecond * deltaTime;

    // this formula means that happiness decreases as hunger or sleepiness increases, 
    // and if hunger OR sleepiness reach their maximum then happiness is 0
    m_Happiness = (m_MaxHunger - m_Hunger) * (m_MaxSleepiness - m_Sleepiness) / m_MaxHappiness;
}
