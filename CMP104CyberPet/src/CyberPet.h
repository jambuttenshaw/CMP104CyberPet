#pragma once

#include "Core/Sprite.h"

class CyberPet : public Sprite
{
public:
	CyberPet();
	~CyberPet();

	void Update(float deltaTime) override;
};

