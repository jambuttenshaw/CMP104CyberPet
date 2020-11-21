#pragma once

#include "Image.h"

class Sprite
{
public:
	Sprite();
	Sprite(int x, int y);
	Sprite(Vector2i pos);
	virtual ~Sprite();

	inline Image* GetImage() { return m_Image; }

private:
	Vector2i m_Position;

	Image* m_Image;
};

