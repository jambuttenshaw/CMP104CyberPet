#include "Button.h"

#include "../Rendering/Image.h"

Button::Button(const std::string& text)
	: Sprite(), m_Text(text)
{
	ConstructImages();
	SetImage(m_InactiveImage);
}

Button::~Button()
{
	// whatever image is currently active will be deleted when the base class destructor is called
	// so we only need to delete which ever image is currently not being used
	if (m_Active)
		delete m_InactiveImage;
	else
		delete m_ActiveImage;
}

void Button::ConstructImages()
{
	// create an active and inactive image from the string supplied in the constructor

	// image constructor takes a width height and a string for content
	// the height will always be 3
	int height = 3;
	// the width is the length of the text + 4 (two characters each side of the text on the button)
	int width = m_Text.length() + 4;

	// create the content so the active button looks like this:
	/*
	 
	###############
	# SAMPLE TEXT #
	###############

	*/
	std::string content = "";
	for (int i = 0; i < width; i++)
		content += "#";
	content += "\n# " + m_Text + " #\n";
	for (int i = 0; i < width; i++)
		content += "#";

	// create the image
	m_ActiveImage = new Image(width, height, content);


	// repeat the same process for the inactive image
	height = 3;
	width = m_Text.length() + 4;

	// create the content so the active button looks like this:
	/*

	---------------
	| SAMPLE TEXT |
	---------------

	*/
	content = "";
	for (int i = 0; i < width; i++)
		content += "-";
	content += "\n| " + m_Text + " |\n";
	for (int i = 0; i < width; i++)
		content += "-";

	// create the image
	m_InactiveImage = new Image(width, height, content);
}
