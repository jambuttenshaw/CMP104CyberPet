#pragma once

#include "MathsUtility.h"
#include "../Rendering/Image.h"

class Sprite
{
public:
	Sprite();
	Sprite(float x, float y);
	Sprite(Vector2f pos);
	virtual ~Sprite();

	// to be overridden in a child class
	virtual void Update(float deltaTime) = 0;

	inline Vector2f GetPosition() { return m_Position; }
	inline Vector2i GetIntPosition() { return { (int)m_Position.x, (int)m_Position.y }; }

	inline void SetPosition(Vector2f pos) { m_Position = pos; SetDirty(); }
	inline void SetCentrePosition(Vector2f pos) 
	{
		m_Position = {
			pos.x - ((float)m_Image->GetWidth() * 0.5f),
			pos.y -((float)m_Image->GetHeight() * 0.5f)
		};
	}

	inline void SetImage(Image* image) { m_Image = image; SetDirty(); }
	inline Image* GetImage() { return m_Image; }

	inline void Clean() { m_Dirty = false; }
	inline void SetDirty() { m_Dirty = true; }
	inline bool IsDirty() { return m_Dirty; }

protected:
	inline void DeleteImage() { delete m_Image; }

private:
	Vector2f m_Position;

	bool m_Dirty = false; // a flag to say whether the sprite has been modified since the last time it was drawn

	Image* m_Image = nullptr;
};

