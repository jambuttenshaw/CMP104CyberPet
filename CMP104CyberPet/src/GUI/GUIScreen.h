#pragma once

#include "Button.h"
#include "GUIText.h"

#include <vector>

class GUIScreen
{
public:
	enum class ArrowDirection
	{
		Left, Right
	};

public:
	GUIScreen();
	~GUIScreen();

	void Load();

	void OnArrowKey(ArrowDirection dir);
	void OnEnter();

	std::vector<Sprite*> GetSprites();

	inline void AddButon(Button* button) { m_Buttons.push_back(button); }
	inline void AddText(GUIText* text) { m_Text.push_back(text); }

	inline Button* GetButton(int index) { return m_Buttons[index]; }
	inline GUIText* GetText(int index) { return m_Text[index]; }

private:

	void RefreshButtons();

private:
	std::vector<Button*> m_Buttons;
	int m_SelectedButton = 0;

	std::vector<GUIText*> m_Text;
};
