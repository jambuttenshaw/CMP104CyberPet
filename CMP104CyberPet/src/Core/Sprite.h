#pragma once

#include "MathsUtility.h"
#include "../Rendering/Image.h"

class Sprite
{
public:
	Sprite();
	Sprite(int x, int y);
	Sprite(Vector2i pos);
	virtual ~Sprite();

	inline Vector2i GetPosition() { return m_Position; }

	inline void SetImage(Image* image) { m_Image = image; }
	inline Image* GetImage() { return m_Image; }

private:
	Vector2i m_Position;

	Image* m_Image;
};

