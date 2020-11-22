#include "Image.h"

#include <iostream>

Image::Image(int width, int height, wchar_t defaultFill)
	: m_Width(width), m_Height(height)
{
	CreateImage(defaultFill);
}

Image::Image(int width, int height, const std::string& imageContent)
	: m_Width(width), m_Height(height)
{
	CreateImage(imageContent);
}

Image::~Image()
{
	// free each sub-array in the 2d array of image data
	for (int i = 0; i < m_Height; i++)
		delete[] m_ImageData[i];
	delete[] m_ImageData;
}

void Image::CreateImage(wchar_t defaultFill)
{
	// an image is just a 2d array of chars
	// a 2d array is just an array of arrays
	
	// and in c++, an array is really just a pointer
	// so here ill create a an array of pointers, where each pointer points to another array
	// and voila; a 2d array

	m_ImageData = new wchar_t* [m_Height];
	for (int i = 0; i < m_Height; i++)
	{
		// set the pointer at this height in the image array to a pointer to a new array
		m_ImageData[i] = new wchar_t[m_Width];

		// fill the array with the default fill character
		for (int j = 0; j < m_Width; j++)
		{
			m_ImageData[i][j] = defaultFill;
		}
	}
}

void Image::CreateImage(const std::string& imageContent)
{
	// initialize the image data array with empty arrays
	m_ImageData = new wchar_t* [m_Height];
	for (int i = 0; i < m_Height; i++)
	{
		// set the pointer at this height in the image array to a pointer to a new array
		m_ImageData[i] = new wchar_t[m_Width];
	}


	// image is created largely the same way,
	// except we access the string to fill in the image rather than just using a default fill character
	int x = 0;
	int y = 0;


	const char* cString = imageContent.c_str();

	for (int i = 0; i < strlen(cString); i++)
	{
		// we do not want to put newlines into the char array
		if (cString[i] == '\n')
			continue;

		// place the current character in the array
		m_ImageData[y][x] = cString[i];

		// increase x
		x++;
		// if we have reached the end of the row, move onto the next one
		if (x == m_Width)
		{
			x = 0;
			y++;
		}

	}

	
}


void Image::SetCharacter(int x, int y, wchar_t character)
{
	m_ImageData[y][x] = character;
}
