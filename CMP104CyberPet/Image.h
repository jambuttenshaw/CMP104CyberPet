#pragma once

#include "MathsUtility.h"

class Image
{
public:
	Image(int width, int height, char defaultFill);
	~Image();

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	inline Vector2i GetDimensions() { return Vector2i(m_Width, m_Height); }

	char** GetImage();
private:
	void CreateImage();

private:
	int m_Width, m_Height;

};
