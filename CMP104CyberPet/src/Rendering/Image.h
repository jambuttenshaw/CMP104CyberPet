#pragma once

#include <string>

#include "../Core/MathsUtility.h"

class Image
{
public:
	// constructors
	Image(int width, int height, wchar_t defaultFill = ' ');
	Image(int width, int height, const std::string& imageContent);
	Image(const Image& oldImage);
	~Image();

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	inline Vector2i GetDimensions() { return Vector2i(m_Width, m_Height); }

	inline wchar_t** GetImageData() { return m_ImageData; }

	void SetCharacter(int x, int y, wchar_t character);

private:
	void CreateImage(wchar_t defaultFill);
	void CreateImage(const std::string& imageContent);
	void CopyImage(wchar_t** imageData);

private:
	int m_Width, m_Height;

	wchar_t** m_ImageData;

};
