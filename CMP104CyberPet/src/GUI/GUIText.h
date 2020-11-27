#pragma once

#include "../Core/Sprite.h"

class GUIText : public Sprite
{
public:
	GUIText(const std::string& content)
		: Sprite()
	{
		SetImage(new Image((int)content.length(), 1, content));
		SetPosition({ 0, 0 });
	}

	GUIText(const std::string& content, Vector2f position)
		: Sprite()
	{
		SetImage(new Image((int)content.length(), 1, content));
		SetPosition(position);
	}

	void Update(float deltaTime) override {};

	void SetString(const std::string& content)
	{
		SetImage(new Image((int)content.length(), 1, content));
	}

	void ReplaceString(const std::string& content)
	{
		DeleteImage();
		SetImage(new Image((int)content.length(), 1, content));
	}
};
