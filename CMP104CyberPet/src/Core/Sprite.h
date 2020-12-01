#pragma once

#include "MathsUtility.h"
#include "../Rendering/Image.h"

// A sprite is a generic class to describe any object that will appear on screen
// that has both an image and a position,
// with some extra useful functionality thrown in
class Sprite
{
public:
	// a sprite has a default constructor, but also can be constructed at a position
	Sprite();
	Sprite(float x, float y);
	Sprite(Vector2f pos);
	// virtual destructor since this class will be inhereted from
	virtual ~Sprite();

	// to be overridden in a child class
	virtual void Update(float deltaTime);

	// Getters for the position as a float or as an integer
	// we need the int position when rendering to the console
	// we dont want to round the position, just to chop off the decimal places
	inline Vector2f GetPosition() { return m_Position; }
	inline Vector2i GetIntPosition() { return { (int)m_Position.x, (int)m_Position.y }; }

	// functions to set the position of the sprite
	// we also want to set where the centre of the sprite is sometimes, instead of the topleft corner
	// in cases where we cant guarentee the width and height of the sprite
	inline void SetPosition(Vector2f pos) { m_Position = pos; }
	void SetCentrePosition(Vector2f pos);

	// sprite has built-in lerping functionality
	// that is we can specify a position we want the sprite to move towards,
	// and it will smoothly move towards that position each frame
	void LerpToPosition(Vector2f pos);
	// to check if the linear interpolation of position is still in progress
	inline bool IsLerping() { return m_Lerping; }

	// setting the image of the sprite
	// this takes a raw pointer, and stores this pointer in the sprite
	inline void SetImage(Image* image) { m_Image = image; }
	// when another class needs access to this sprite's image, we give it a raw pointer to the image
	inline Image* GetImage() { return m_Image; }
protected:
	// we only want children of the sprite class to be able to delete the image
	// this is useful when the image of the sprite is getting replaced and we need to free the memory taken up by the old one
	inline void DeleteImage() { delete m_Image; }

private:
	Vector2f m_Position;

	Vector2f m_LerpStart = { 0, 0 };
	Vector2f m_LerpingTarget = { 0, 0 };
	float m_LerpTimer = 0;
	bool m_Lerping = false;

	bool m_Dirty = false; // a flag to say whether the sprite has been modified since the last time it was drawn

	Image* m_Image = nullptr;
};

