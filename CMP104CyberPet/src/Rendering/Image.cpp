#include "Image.h"

// the first constructor
// create the image using the default fill character
Image::Image(int width, int height, wchar_t defaultFill)
	: m_Width(width), m_Height(height)
{
	CreateImage(defaultFill);
}

// the next constructor creates the image out of the given string
Image::Image(int width, int height, const std::string& imageContent)
	: m_Width(width), m_Height(height)
{
	CreateImage(imageContent);
}

// the copy constructor: creates a deep copy of the image given
// when we create a new image out of an old one we do not want both objects
// pointing to the same image in memory
Image::Image(const Image& oldImage)
	: m_Width(oldImage.m_Width), m_Height(oldImage.m_Height)
{
	CopyImage(oldImage.m_ImageData);
}

// the destructor frees the image data from memory
Image::~Image()
{
	// free each sub-array in the 2d array of image data
	for (int i = 0; i < m_Height; i++)
		delete[] m_ImageData[i];
	delete[] m_ImageData;
}

// create image out of a default fill character
void Image::CreateImage(wchar_t defaultFill)
{
	// an image is just a 2d array of chars
	// a 2d array is just an array of arrays
	
	// and in c++, an array is really just a pointer
	// so here ill create a an array of pointers, where each pointer points to another array
	// and voila; a 2d array

	// create an array of pointers with the size of the height of the image
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

// this creates the image out of the string
void Image::CreateImage(const std::string& imageContent)
{
	// initialize the image data array with empty arrays
	// create an arary of pointers with the size of the height of the image
	m_ImageData = new wchar_t* [m_Height];
	for (int i = 0; i < m_Height; i++)
	{
		// set the pointer at this height in the image array to a pointer to a new array
		m_ImageData[i] = new wchar_t[m_Width];
	}


	// image is created largely the same way,
	// except we access the string to fill in the image rather than just using a default fill character

	// the coordinates we are about to place a character at in the 2D array
	int x = 0;
	int y = 0;

	// convert it to a c string: a pointer to the first character in the string
	const char* cString = imageContent.c_str();

	// iterate for the length of the string
	for (int i = 0; i < strlen(cString); i++)
	{
		// we do not want to put newlines into the char array
		if (cString[i] == '\n')
			continue;

		// place the current character from the string in the array
		// we need to cast it to a wchar_t cause that is the data type
		// the console api works with
		m_ImageData[y][x] = (wchar_t)cString[i];

		// increase x
		x++;
		// if we have reached the end of the row, move onto the next one
		if (x == m_Width)
		{
			// move back to the first column and move down a row
			x = 0;
			y++;
		}
	}
}

// copies an image when a deep copy of an image object is required
void Image::CopyImage(wchar_t** imageData)
{
	// initialize the image data array with empty arrays
	m_ImageData = new wchar_t* [m_Height];
	for (int i = 0; i < m_Height; i++)
	{
		// set the pointer at this height in the image array to a pointer to a new array
		m_ImageData[i] = new wchar_t[m_Width];
	}

	// just sample the old image for whatever character existed there,
	// and place it at the same position in the new array
	for (int i = 0; i < m_Height; i++)
	{
		for (int j = 0; j < m_Width; j++)
		{
			m_ImageData[i][j] = imageData[i][j];
		}
	}
}

// set a specific character at a specific position
void Image::SetCharacter(int x, int y, wchar_t character)
{
	m_ImageData[y][x] = character;
}
