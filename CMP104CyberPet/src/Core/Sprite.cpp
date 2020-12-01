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

void Sprite::SetCentrePosition(Vector2f pos)
{
	float posX = pos.x - ((float)m_Image->GetWidth() * 0.5f);
	float posY = pos.y - ((float)m_Image->GetHeight() * 0.5f);

	if (posX < 0) posX = 0;
	if (posY < 0) posY = 0;

	m_Position = { posX, posY };
}
