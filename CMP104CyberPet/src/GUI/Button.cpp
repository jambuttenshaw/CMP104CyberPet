#include "Button.h"

#include "../Rendering/Image.h"

Button::Button(const std::string& text)
	: Sprite(), m_Text(text) // initialize parameters and call the base class constructor
{
	// set up the button
	// create the images the button needs
	// then set the sprites image
	ConstructImages();
	SetImage(m_InactiveImage);
}

Button::~Button()
{
	// whatever image is currently active will be deleted when the base class destructor is called
	// so we only need to delete which ever image is currently not being used
	// we do not want to attempt to free the same memory twice
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
	int width = (int)m_Text.length() + 4;

	// create the content so the active button looks like this:
	/*
	 
	###############
	# SAMPLE TEXT #
	###############

	*/
	std::string content = "";
	for (int i = 0; i < width; i++) content += "#"; // create the top line of the button as a line of #'s
	content += "\n# " + m_Text + " #\n"; // place the text inside the button
	for (int i = 0; i < width; i++) content += "#"; // then another line of #'s below

	// create the image by instantiating a new Image object and assigning it to the active image
	m_ActiveImage = new Image(width, height, content);


	// repeat the same process for the inactive image
	height = 3;
	width = (int)m_Text.length() + 4;

	// create the content so the active button looks like this:
	/*

	---------------
	| SAMPLE TEXT |
	---------------

	*/
	// the exact same system for creating the string content for the button
	content = "";
	for (int i = 0; i < width; i++) content += "-";
	content += "\n| " + m_Text + " |\n";
	for (int i = 0; i < width; i++)  content += "-";

	// create the image by instantiating a new Image object and assigning it to the inactive image
	m_InactiveImage = new Image(width, height, content);
}
