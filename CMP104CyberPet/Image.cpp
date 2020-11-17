#include "Image.h"

Image::Image(int width, int height, char defaultFill)
	: m_Width(width), m_Height(height)
{
	CreateImage(defaultFill);
}

Image::~Image()
{
	// free each sub-array in the 2d array of image data
	for (int i = 0; i < m_Height; i++)
		delete[] m_ImageData[i];
	delete[] m_ImageData;
}

void Image::CreateImage(char defaultFill)
{
	// an image is just a 2d array of chars
	// a 2d array is just an array of arrays
	
	// and in c++, an array is really just a pointer
	// so here ill create a an array of pointers, where each pointer points to another array
	// and voila; a 2d array

	m_ImageData = new char* [m_Height];
	for (int i = 0; i < m_Height; i++)
	{
		// set the pointer at this height in the image array to a pointer to a new array
		m_ImageData[i] = new char[m_Width];

		// fill the array with the default fill character
		for (int j = 0; j < m_Width; j++)
		{
			m_ImageData[i][j] = defaultFill;
		}
	}
}
