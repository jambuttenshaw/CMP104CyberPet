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

void Sprite::Update(float deltaTime)
{
	if (m_Lerping)
	{
		// check if we are close to the target
		if (SqrMagnitude({ m_LerpingTarget.x - m_Position.x, m_LerpingTarget.y - m_Position.y }) < m_LerpTerminationThreshold)
		{
			m_Lerping = false;
			SetCentrePosition(m_LerpingTarget);
		}
		// otherwise just keep on lerping closer
		else SetCentrePosition(Lerp(m_Position, m_LerpingTarget, deltaTime));
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


void Sprite::LerpToPosition(Vector2f pos)
{
	m_Lerping = true;
	m_LerpingTarget = pos;
}
