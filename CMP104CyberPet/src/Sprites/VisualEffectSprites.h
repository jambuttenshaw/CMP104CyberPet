#pragma once

#include "../Core/Sprite.h"

class Carrot : public Sprite
{
public:
	Carrot()
		: Sprite()
	{
		SetImage(new Image(4, 3, R"(_\/_
\  /
 \/ )"));
		SetPosition({ 0, 0 });
	}
};
