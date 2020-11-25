#pragma once

#include "Core/Sprite.h"

class CyberPet : public Sprite
{
public:
	CyberPet();
	~CyberPet();

	void Update(float deltaTime) override;

private:

	std::string m_Name;

	float m_Hunger = 0;
	float m_Sleepiness = 0;
	float m_Happiness = 0;

	// using 0.017f will take 1 minute to each max hunger and sleepiness, and happiness to reach a minimum
	float m_HungerPerSecond = 0.017f;
	float m_SleepinessPerSecond = 0.017f;

	float m_MaxHunger = 1;
	float m_MaxSleepiness = 1;
	float m_MaxHappiness = m_MaxHunger * m_MaxSleepiness;
};

