#pragma once

#include "Button.h"

#include <vector>

class GUIScreen
{
public:
	GUIScreen();
	~GUIScreen();

	void Load();

	inline std::vector<Sprite*> GetButtonSprites() { return std::vector<Sprite*>(m_Buttons.begin(), m_Buttons.end()); }

	inline void AddButon(Button* button) { m_Buttons.push_back(button); }

private:
	std::vector<Button*> m_Buttons;
};
