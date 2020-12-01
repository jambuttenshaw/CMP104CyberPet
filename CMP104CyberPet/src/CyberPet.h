#pragma once

#include "Core/Sprite.h"

#include <vector>

class CyberPet : public Sprite
{
public:
	enum class State {
		Neutral,
		Sleeping,
		Eating,
		Playing
	};

public:
	CyberPet(Vector2f initalPos);
	CyberPet(Vector2f initalPos, Sprite* pet);
	~CyberPet();

	void Update(float deltaTime) override;

	// functions for retrieving the stats of the pet
	inline float GetNormalizedHunger() { return m_Hunger / m_MaxHunger; }
	inline float GetNormalizedSleepiness() { return m_Sleepiness / m_MaxSleepiness; }
	inline float GetNormalizedFun() { return m_Fun / m_MaxFun; }
	inline float GetNormalizedHappiness() { return m_Happiness / m_MaxHappiness; }

	// naming related functions
	inline const std::string& GetName() { return m_Name; }
	inline void SetName(const std::string& name) { m_Name = name; }
	inline void AppendName(const std::string& c) { m_Name.append(c); }
	inline void DeleteLastCharacter() { m_Name = m_Name.substr(0, m_Name.size() - 1); }

	inline int GetNameLength() { return (int)m_Name.length(); }
	inline int GetMaxNameLength() { return m_MaxNameLength; }

	inline bool ValidName() { return m_Name.length(); }


	// controlling the state of the pet
	inline State GetState() { return m_State; }
	void SetState(State state);

	std::string GetActivityString();
	std::string GetHungerString();
	std::string GetSleepinessString();

	inline std::vector<Sprite*> GetVisualEffectSprites() { return m_VisualEffectsSprites; }

private:
	void Init();

private:
	Vector2f m_InitialPosition = { 0, 0 };

	std::string m_Name;
	int m_MaxNameLength = 24;

	State m_State = State::Neutral;
	// how long each activity lasts for
	float m_TimeUntilNeutral = 10; // 10 seconds
	float m_ReturnToNeutralTimer = 0;

	float m_MaxHunger = 1;
	float m_MaxSleepiness = 1;
	float m_MaxFun = 1;
	float m_MaxHappiness = m_MaxHunger * m_MaxSleepiness * m_MaxFun;


	float m_Hunger = 0;
	float m_Sleepiness = 0;
	float m_Fun = m_MaxFun;
	float m_Happiness = 0;


	// parameters for the visual effects
	float m_PlayMoveSpeed = 12.57f / m_TimeUntilNeutral; // pet should travel an angular displacement of 4pi while playing
	float m_PlayMoveAmplitude = 4;

	Vector2f m_FoodSpawnLocation = { 0, 0 };
	Vector2f m_FoodDestination = { 0, 0 };

	// container for visual effects spawned
	std::vector<Sprite*> m_VisualEffectsSprites;

	
	// using 0.017f will take 1 minute to reach max hunger and sleepiness, and fun and happiness to reach a minimum
	float m_HungerPerSecond = 0.017f;
	float m_SleepinessPerSecond = 0.017f;
	float m_FunPerSecond = 0.017f;

	// the speed that hunger, sleep and fun are recovered
	float m_EatingSpeed = 0.05f;
	float m_SleepingSpeed = 0.05f;
	float m_PlayingSpeed = 0.05f;

};

