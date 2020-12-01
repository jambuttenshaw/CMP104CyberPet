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
		Vector2f p = Lerp(m_LerpStart, m_LerpingTarget, m_LerpTimer);
		m_LerpTimer += deltaTime;
		
		SetPosition(p);
	
		// check if we are close to the target
		if (m_LerpTimer >= 1)
		{
			m_Lerping = false;
			SetPosition(m_LerpingTarget);
		}
	}
}

void Sprite::SetCentrePosition(Vector2f pos)
{
	float posX = pos.x - ((float)m_Image->GetWidth() * 0.5f);
	float posY = pos.y - ((float)m_Image->GetHeight() * 0.5f);

	m_Position = { posX, posY };
}


void Sprite::LerpToPosition(Vector2f pos)
{
	m_LerpingTarget = pos;
	m_LerpStart = m_Position;

	m_Lerping = true;
	m_LerpTimer = 0;
}
