#include "Sprite.h"

Sprite::Sprite()
	: m_Position(Vector2f(0, 0))
{

}

Sprite::Sprite(float x, float y)
	: m_Position(Vector2f(x, y))
{

}

Sprite::Sprite(Vector2f pos)
	: m_Position(pos)
{

}

Sprite::~Sprite()
{
	if (m_Image != nullptr)
	{
		delete m_Image;
	}
}
