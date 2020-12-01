#pragma once

#include "../Core/Sprite.h"

class Carrot : public Sprite
{
public:
	Carrot(Vector2f startPos, Vector2f endPos)
		: Sprite()
	{
		SetImage(new Image(4, 3, R"(_\/_
\  /
 \/ )"));
		SetCentrePosition(startPos);
		LerpToPosition(endPos);
	}

	~Carrot()
	{
	}

	inline void Update(float deltaTime) override { Sprite::Update(deltaTime); };
};
