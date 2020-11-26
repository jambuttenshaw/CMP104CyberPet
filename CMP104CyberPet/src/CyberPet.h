#pragma once

#include "Core/Sprite.h"

class CyberPet : public Sprite
{
public:
	enum State {
		Neutral,
		Sleeping,
		Eating,
		Playing
	};

public:
	CyberPet();
	~CyberPet();

	void Update(float deltaTime) override;

	// functions for retrieving the stats of the pet
	inline float GetNormalizedHunger() { return m_Hunger / m_MaxHunger; }
	inline float GetNormalizedSleepiness() { return m_Sleepiness / m_MaxSleepiness; }
	inline float GetNormalizedHappiness() { return m_Happiness / m_MaxHappiness; }

	inline const std::string& GetName() { return m_Name; }
	inline void SetName(const std::string& name) { m_Name = name; }
	inline void AppendName(const std::string& c) { m_Name.append(c); }
	inline void DeleteLastCharacter() { m_Name = m_Name.substr(0, m_Name.size() - 1); }

	inline int GetNameLength() { return m_Name.length(); }
	inline int GetMaxNameLength() { return m_MaxNameLength; }

	inline bool ValidName() { return m_Name.length(); }

private:

	std::string m_Name;
	int m_MaxNameLength = 20;

	State m_State = State::Neutral;

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

