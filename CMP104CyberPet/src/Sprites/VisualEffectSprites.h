#pragma once

#include "../Core/Sprite.h"

class VisualEffectSprite : public Sprite
{
public:
	VisualEffectSprite(Vector2f startPos, Vector2f endPos)
		: Sprite(), m_StartPos(startPos), m_EndPos(endPos)
	{
	}

	~VisualEffectSprite()
	{
	}

	inline void Reset()
	{
		SetCentrePosition(m_StartPos);
		LerpToPosition(m_EndPos);
	}

	inline void Reset(Vector2f startPos, Vector2f endPos)
	{
		SetCentrePosition(startPos);
		LerpToPosition(endPos);
	}

	inline void Update(float deltaTime) override { Sprite::Update(deltaTime); };
private:
	Vector2f m_StartPos;
	Vector2f m_EndPos;
};


class Carrot : public VisualEffectSprite
{
public:
	Carrot(Vector2f startPos, Vector2f endPos)
		: VisualEffectSprite(startPos, endPos)
	{
		SetImage(new Image(4, 3, R"(_\/_
\  /
 \/ )"));

		Reset();
	}

	~Carrot()
	{
	}
};
