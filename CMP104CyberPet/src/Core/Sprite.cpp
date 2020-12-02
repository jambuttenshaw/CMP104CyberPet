#include "Sprite.h"

// if no position is specified set the position of the sprite to 0, 0
Sprite::Sprite()
	: m_Position(Vector2f(0, 0))
{
}

// in this constructor the position is specified as two different float parameters
Sprite::Sprite(float x, float y)
	: m_Position(Vector2f(x, y))
{
}

// this constructor takes a vector for the position
Sprite::Sprite(Vector2f pos)
	: m_Position(pos)
{
}

// destructor: delete the sprite's image if it has one
Sprite::~Sprite()
{
	// if the image is nullptr then it doesnt exist
	// otherwise we want to delete the image from memory
	if (m_Image != nullptr)
	{
		delete m_Image;
	}
}

void Sprite::Update(float deltaTime)
{
	// check if the sprite should be linearly interpolating between positions
	if (m_Lerping)
	{
		// get the position it should be at this frame
		Vector2f p = Lerp(m_LerpStart, m_LerpingTarget, m_LerpTimer);
		// increment the timer by the time elapsed this frame
		m_LerpTimer += deltaTime;
		
		// move the sprite to the new position
		SetPosition(p);
	
		// the t parameter in the lerp function ranges from 0 to 1, 
		// so once the timer is at least 1 the sprite has reached its target
		if (m_LerpTimer >= 1)
		{
			// set the sprites position to exactly its target and show that its no longer lerping
			m_Lerping = false;
			SetPosition(m_LerpingTarget);
		}
	}
}

// this moves the centre of the sprite to the position specified
// m_Position stores the topleft corner of the sprite,
// so we need to offset the position specified in the parameter by half the sprites dimensions
void Sprite::SetCentrePosition(Vector2f pos)
{
	float posX = pos.x - ((float)m_Image->GetWidth() * 0.5f);
	float posY = pos.y - ((float)m_Image->GetHeight() * 0.5f);

	m_Position = { posX, posY };
}

// starts the sprite lerping to a specified position
void Sprite::LerpToPosition(Vector2f pos)
{
	// set the target, and where the sprite is moving from
	m_LerpingTarget = pos;
	m_LerpStart = m_Position;

	// flag the sprite as currently lerping,
	// so the update function knows to move the sprite
	m_Lerping = true;
	// reset the timer in case it has been used before
	m_LerpTimer = 0;
}
