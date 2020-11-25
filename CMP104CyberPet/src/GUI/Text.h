#pragma once

#include "../Core/Sprite.h"

class Text : public Sprite
{
public:
	Text(const std::string& content);
	Text(const std::string& content, Vector2i position);
};
