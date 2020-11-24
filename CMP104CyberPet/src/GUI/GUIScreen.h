#pragma once

#include "Button.h"

#include <vector>

class GUIScreen
{
public:
	enum ArrowDirection
	{
		Left, Right
	};

public:
	GUIScreen();
	~GUIScreen();

	void Load();

	void OnArrowKey(ArrowDirection dir);

	inline std::vector<Sprite*> GetButtonSprites() { return std::vector<Sprite*>(m_Buttons.begin(), m_Buttons.end()); }

	inline void AddButon(Button* button) { m_Buttons.push_back(button); }

private:

	void RefreshButtons();

private:
	std::vector<Button*> m_Buttons;
	int m_SelectedButton = 0;
};
