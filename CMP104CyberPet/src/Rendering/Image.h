#pragma once

#include <string>

#include "../Core/MathsUtility.h"

// a class that is used for displaying graphics on the console
// since we can only display characters on the console,
// an 'image' here is simply a 2D array of characters

// windows console api requires the data to be of type wchar_t; wide character
// a character that takes up 2 bytes instead of 1.

class Image
{
public:
	// constructors
	// either create an image filled from 1 character,
	// or created from a string, where each line of the string
	// is each row in the image
	Image(int width, int height, wchar_t defaultFill = ' ');
	Image(int width, int height, const std::string& imageContent);
	// a copy constructor:
	// important when we need to assign a sprite the image of another sprite
	// but we dont want both sprites pointing towards the same data in memory
	// because when one sprite gets deleted, the other sprite will no longer
	// have an image to display on screen
	Image(const Image& oldImage);
	
	// image destructor
	~Image();

	// simple getters to return the width and height of the image
	// or get the dimensions as a Vector
	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	inline Vector2i GetDimensions() { return Vector2i(m_Width, m_Height); }

	// get the actual data in the image
	// return a pointer to the 2D array
	inline wchar_t** GetImageData() { return m_ImageData; }

	// set a specific character in the image
	// specify the x and y coordinates within the image, and the character you want to place
	void SetCharacter(int x, int y, wchar_t character);

private:
	// private functions used to create the image out of the data supplied in the constructor
	
	// this one creates an image fill with 1 single character
	void CreateImage(wchar_t defaultFill);
	// this one creates an image from a string, where each line in the string is a row in the image
	void CreateImage(const std::string& imageContent);
	// this one recreates a given image but in a new place in memory; for copying an image
	void CopyImage(wchar_t** imageData);

private:
	// the width and height of the image
	int m_Width, m_Height;

	// the actual data of the image
	wchar_t** m_ImageData;

};
