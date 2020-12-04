#pragma once

#include "Core/Sprite.h"
#include "Sprites/VisualEffectSprites.h"

#include <vector>

// the main cyberpet itself!
// inherits from sprite as it has an image and a position
class CyberPet : public Sprite
{
public:
	// an enum to represent the current state of the sprite
	// it makes more sense to read the code when the state can be written
	// as eg Neutral than using arbitrary integers to represent the state
	enum class State {
		Neutral,
		Sleeping,
		Eating,
		Playing
	};

public:
	// the cyberpet can be constructed at a position, or also with a pet to construct its image from
	CyberPet(Vector2f initalPos);
	CyberPet(Vector2f initalPos, Sprite* pet);
	// destructor
	~CyberPet();

	// update function of the cyberpet
	// required to qualify as a sprite
	void Update(float deltaTime) override;

	// functions for retrieving the stats of the pet
	// the stats are normalized to be in the range of 0 and 1
	// which makes them easier to work with
	inline float GetNormalizedHunger() { return m_Hunger / m_MaxHunger; }
	inline float GetNormalizedSleepiness() { return m_Sleepiness / m_MaxSleepiness; }
	inline float GetNormalizedFun() { return m_Fun / m_MaxFun; }
	inline float GetNormalizedHappiness() { return m_Happiness / m_MaxHappiness; }

	// naming related functions
	// get the name of the cyberpet
	inline const std::string& GetName() { return m_Name; }
	// set the name of the cyberpet
	inline void SetName(const std::string& name) { m_Name = name; }

	// these are used when the user is tpying in the name of the cyberpet
	// add a character onto the end of the cyberpet's name
	inline void AppendName(const std::string& c) { m_Name.append(c); }
	// remove the last character from the cyberpet's name
	// substr returns the section of the string between the specified indices
	inline void DeleteLastCharacter() { m_Name = m_Name.substr(0, m_Name.size() - 1); }

	// get the length of the pets name
	inline int GetNameLength() { return (int)m_Name.length(); }
	// get the maximum allowed length of the pets name
	inline int GetMaxNameLength() { return m_MaxNameLength; }

	// check that the name has a length greater than 0
	inline bool ValidName() { return m_Name.length(); }


	// controlling the state of the pet
	// get the current state of the pet
	inline State GetState() { return m_State; }
	// set the current state of the pet
	void SetState(State state);

	// gets a strig to describe what the pet is currently doing
	std::string GetActivityString();
	// gets a string to describe how hungry the pet is
	std::string GetHungerString();
	// gets a string to describe how sleepy the pet is
	std::string GetSleepinessString();

	// gets a vector of all the visual effects sprites that the cyberpet has currently created
	std::vector<Sprite*> GetVisualEffectSprites();

private:
	// an initializing function
	void Init();

private:
	// where the pet resides by default
	Vector2f m_InitialPosition = { 0, 0 };

	// the name of the sprite
	std::string m_Name;
	// the maximum allowed length of the sprites name
	int m_MaxNameLength = 24;

	// what state the sprite is in
	// set it to neutral by default
	State m_State = State::Neutral;

	// how long each activity lasts for
	float m_TimeUntilNeutral = 10; // 10 seconds

	// a timer to check how long is left until the pet becomes neutral again
	float m_ReturnToNeutralTimer = 0;

	// the maximum value that each stat can have
	float m_MaxHunger = 1;
	float m_MaxSleepiness = 1;
	float m_MaxFun = 1;
	// the max happiness can be calculated as the product of the max of the rest of the stats
	float m_MaxHappiness = m_MaxHunger * m_MaxSleepiness * m_MaxFun;

	// initialize the stats of the pet at their most positive
	// such that the happiness of the pet == max happiness
	float m_Hunger = 0;
	float m_Sleepiness = 0;
	float m_Fun = m_MaxFun;

	// this gets calculated in the update function, so the value we initialize it with doesnt matter too much
	float m_Happiness = 0;


	// parameters for the visual effects
	float m_PlayMoveSpeed = 12.57f / m_TimeUntilNeutral; // pet should travel an angular displacement of 4pi while playing
	// how extreme the movement of the pet is
	float m_PlayMoveAmplitude = 4;

	// these get set in init as they depend on the dimenions of the sprites image
	Vector2f m_FoodSpawnLocation = { 0, 0 };
	Vector2f m_FoodDestination = { 0, 0 };

	Vector2f m_SleepingZSpawnLocation = { 0, 0 };
	Vector2f m_SleepingZDestination = { 56, 0 };

	// container for visual effects spawned
	std::vector<VisualEffectSprite*> m_VisualEffectsSprites;

	
	// using 0.017f will take 1 minute to reach max hunger and sleepiness, and fun and happiness to reach a minimum
	// the stats of the pet will increase/decrease by this amount each second
	float m_HungerPerSecond = 0.017f;
	float m_SleepinessPerSecond = 0.017f;
	float m_FunPerSecond = 0.017f;

	// the speed that hunger, sleep and fun are recovered
	// the stats of the pet will increase/decrease by this amount each second
	float m_EatingSpeed = 0.05f;
	float m_SleepingSpeed = 0.05f;
	float m_PlayingSpeed = 0.05f;

};

