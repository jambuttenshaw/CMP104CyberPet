#pragma once

#include "MathsUtility.h"

class Image
{
public:
	// constructors
	Image(int width, int height, char defaultFill = ' ');
	~Image();

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	inline Vector2i GetDimensions() { return Vector2i(m_Width, m_Height); }

	inline char** GetImageData() { return m_ImageData; }
private:
	void CreateImage(char defaultFill);

private:
	int m_Width, m_Height;

	char** m_ImageData;

};
