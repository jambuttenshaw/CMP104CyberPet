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

	// to be overridden in a child class
	virtual void Update(float deltaTime) = 0;

	inline Vector2i GetPosition() { return m_Position; }
	inline void SetPosition(Vector2i pos) { m_Position = pos; SetDirty(); }

	inline void SetImage(Image* image) { m_Image = image; SetDirty(); }
	inline Image* GetImage() { return m_Image; }

	inline void Clean() { m_Dirty = false; }
	inline void SetDirty() { m_Dirty = true; }
	inline bool IsDirty() { return m_Dirty; }

private:
	Vector2i m_Position;

	bool m_Dirty = false; // a flag to say whether the sprite has been modified since the last time it was drawn

	Image* m_Image = nullptr;
};

