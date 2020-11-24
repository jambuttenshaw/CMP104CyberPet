#pragma once

#include "../Core/Sprite.h"

class Button : public Sprite
{
public:
	Button(const std::string& text);
	~Button();

	inline void SetActive(bool active) { m_Active = active; UpdateImage(); }
	inline bool GetActive() { return m_Active; }

private:
	void ConstructImages();
	inline void UpdateImage() { SetImage(m_Active ? m_ActiveImage : m_InactiveImage); SetDirty(); }

private:
	std::string m_Text;

	Image* m_InactiveImage = nullptr;
	Image* m_ActiveImage = nullptr;

	bool m_Active = false;
};