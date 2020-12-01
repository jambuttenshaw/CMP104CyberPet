#pragma once

#include "../Core/Sprite.h"

#include <functional>

class Button : public Sprite
{
public:
	Button(const std::string& text);
	~Button();

	void Update(float deltaTime) override { Sprite::Update(deltaTime); };

	inline void Press() { if (m_PressFunction != nullptr) m_PressFunction(); }

	inline void SetActive(bool active) { m_Active = active; UpdateImage(); }
	inline bool GetActive() { return m_Active; }

	inline void SetPressFunction(const std::function<void()>& func) { m_PressFunction = func; }

private:
	void ConstructImages();
	inline void UpdateImage() { SetImage(m_Active ? m_ActiveImage : m_InactiveImage); }

private:
	std::string m_Text;

	Image* m_InactiveImage = nullptr;
	Image* m_ActiveImage = nullptr;

	bool m_Active = false;

	// the function that is executed when the button is 'clicked' must return void and take no parameters
	std::function<void()> m_PressFunction;
};