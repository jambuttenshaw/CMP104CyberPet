#pragma once

#include "../Core/Sprite.h"

// GUIText inherits from sprite
// as it has both a position and an image
class GUIText : public Sprite
{
public:
	// constructor takes in a string for the text to be displayed on screen
	GUIText(const std::string& content)
		: Sprite() // call the parents constructor
	{
		// create a new image from the string
		SetImage(new Image((int)content.length(), 1, content));
		// position it at 0, 0 by default
		SetPosition({ 0, 0 });
	}

	// this constructor specifies a position to create the text object at
	// and optionally specify whether this position should be the topleft of the text, or the centre
	GUIText(const std::string& content, Vector2f position, bool positionAtCentre = false)
		: Sprite()
	{
		// same as the other constructor
		SetImage(new Image((int)content.length(), 1, content));

		// position the text at the specified position, either at the left edge or the centre
		// depending on the bool
		if (positionAtCentre)
			SetCentrePosition(position);
		else
			SetPosition(position);
	}

	// to be a child class of sprite this class has to implement the update function
	// but we dont need to do anything with text each frame so just leave it empty
	void Update(float deltaTime) override {};

	// sets the image of this sprite to contain the text specified in the parameter
	void SetString(const std::string& content)
	{
		SetImage(new Image((int)content.length(), 1, content));
	}

	// similar to the above function, but this one deletes the old image before setting a new one
	// this one should be used when the text object already has an image but it needs modified
	void ReplaceString(const std::string& content)
	{
		DeleteImage();
		SetImage(new Image((int)content.length(), 1, content));
	}
};
