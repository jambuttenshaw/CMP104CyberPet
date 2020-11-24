#pragma once

#include "../Core/Sprite.h"

class Button : public Sprite
{
public:
	Button(const std::string& text);
	~Button();

private:
	void ConstructImages();

private:
	std::string m_Text;

	Image* m_InactiveImage = nullptr;
	Image* m_ActiveImage = nullptr;

	bool m_Active = false;
};