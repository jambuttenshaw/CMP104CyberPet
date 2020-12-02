#pragma once

#include "../Core/Sprite.h"

#include <functional>

// a class to create a graphical button
// that can be selected
// and can be given a function to call when pressed
// it inherets from sprite since it has both an image and a position on screen
class Button : public Sprite
{
public:
	// a constructor for the button that takes in a string
	// the string is the text that is displayed on the button
	Button(const std::string& text);
	// destructor
	~Button();

	// the only thing we want to do in the update function is call the parent class update function
	// all the button-specific behaviour is handled by event callbacks
	void Update(float deltaTime) override { Sprite::Update(deltaTime); };

	// execute the function to be executed when the button is pressed
	// quickly check the function isnt null as we dont want to try call a nullptr
	inline void Press() { if (m_PressFunction != nullptr) m_PressFunction(); }

	// an active button has a different visual appearance
	// so that the user knows that this is the button that will be pressed when they hit enter
	inline void SetActive(bool active) { m_Active = active; UpdateImage(); }
	// a getter so we can check if this is the active button
	inline bool GetActive() { return m_Active; }

	// this sets the function that is executed when the button is pressed
	// std::function<void()> is an object that allows me to specify a variable that holds a reference
	// to a function that returns void and takes no parameters
	// a limitation to this design is that a function executed on a button press cannot return data
	// nor take parameters
	inline void SetPressFunction(const std::function<void()>& func) { m_PressFunction = func; }

private:
	// a private function that generates the image objects that the button will use
	void ConstructImages();
	// checks if the button should be using the active image or the inactive image
	inline void UpdateImage() { SetImage(m_Active ? m_ActiveImage : m_InactiveImage); }

private:
	// the text on the button
	std::string m_Text;

	// pointers to the images that the button will use
	Image* m_InactiveImage = nullptr;
	Image* m_ActiveImage = nullptr;

	// whether the button is currently active or not
	bool m_Active = false;

	// the function that is executed when the button is 'clicked' must return void and take no parameters
	// again using std::function to create a variable that will hold a pointer to the function
	std::function<void()> m_PressFunction;
};