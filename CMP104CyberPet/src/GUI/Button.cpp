#include "Button.h"

Button::Button(const std::string& text)
	: Sprite(), m_Text(text)
{
	ConstructImages();
}

Button::~Button()
{
	delete m_ActiveImage;
	delete m_InactiveImage;
}

void Button::ConstructImages()
{
	// create an active and inactive image from the string supplied in the constructor
}
