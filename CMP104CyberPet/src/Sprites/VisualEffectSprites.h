#pragma once

#include "../Core/Sprite.h"

/*
A VisualEffectSprite is a sprite
whos only purpose is to appear at a position,
and then move to another position

it is very effective at making cool and simple visual effects
*/

// a generic parent class for all VisualEffectSprites
class VisualEffectSprite : public Sprite
{
public:
	// constructor takes in a start position and an end position
	VisualEffectSprite(Vector2f startPos, Vector2f endPos)
		: Sprite(), m_StartPos(startPos), m_EndPos(endPos)
	{
	}

	~VisualEffectSprite()
	{
	}

	// when the VEsprite resets, it returns to the start position
	// and sets up the lerping to the end position once more
	inline void Reset()
	{
		SetCentrePosition(m_StartPos);
		LerpToPosition(m_EndPos);
	}

	// a new start and end position can also be specified when resetting
	inline void Reset(Vector2f startPos, Vector2f endPos)
	{
		SetCentrePosition(startPos);
		LerpToPosition(endPos);
	}

	// and then to qualify as a sprite the update function must be implemented
	// and we also need the the Sprite::Update function to move this sprite across the screen
	inline void Update(float deltaTime) override { Sprite::Update(deltaTime); };
private:
	// store the start and end position as vectors
	Vector2f m_StartPos;
	Vector2f m_EndPos;
};


// a carrot as visual effects for when the pet is eating
class Carrot : public VisualEffectSprite
{
public:
	// take in a start pos and an end pos
	Carrot(Vector2f startPos, Vector2f endPos)
		: VisualEffectSprite(startPos, endPos)
	{
		// set the image of the sprite to a carrot
		SetImage(new Image(4, 3, R"(_\/_
\  /
 \/ )"));

		// resetting the sprite will move it into position and start the lerping
		Reset();
	}

	~Carrot()
	{
	}
};

// a Z that comes out of the pet to show it is sleeping
class SleepingZ : public VisualEffectSprite
{
public:
	// take in a start and end pos
	SleepingZ(Vector2f startPos, Vector2f endPos)
		: VisualEffectSprite(startPos, endPos)
	{
		// set the image to simply a Z
		SetImage(new Image(1, 1, "Z"));
		// resetting the sprite will move it into position and start the lerping
		Reset();
	}

	~SleepingZ()
	{
	}
};
