#pragma once

#include <string>

#include "../Core/MathsUtility.h"

class Image
{
public:
	// constructors
	Image(int width, int height, char defaultFill = ' ');
	Image(int width, int height, const std::string& imageContent);
	~Image();

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	inline Vector2i GetDimensions() { return Vector2i(m_Width, m_Height); }

	inline char** GetImageData() { return m_ImageData; }

	void SetCharacter(int x, int y, char character);

private:
	void CreateImage(char defaultFill);
	void CreateImage(const std::string& imageContent);

private:
	int m_Width, m_Height;

	char** m_ImageData;

};
