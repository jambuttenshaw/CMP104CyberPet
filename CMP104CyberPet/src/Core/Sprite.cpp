#include "Sprite.h"

Sprite::Sprite()
	: m_Position(Vector2i(0, 0))
{

}

Sprite::Sprite(int x, int y)
	: m_Position(Vector2i(x, y))
{

}

Sprite::Sprite(Vector2i pos)
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
