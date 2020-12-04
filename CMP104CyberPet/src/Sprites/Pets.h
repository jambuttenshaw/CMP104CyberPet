#pragma once

#include "../Core/Sprite.h"

// a generic parent class for one of the pet options
// it inherits from sprite as it has a position and an image
class Pet : public Sprite
{
public:
	// call the sprite constructor
	Pet()
		: Sprite()
	{}

	// we want to call the base class implementation of Update
	// as that is the code that actually Lerps the sprite across screen
	void Update(float deltaTime) override 
	{
		Sprite::Update(deltaTime); 
	};

	// move on screen will set up the linear interpolation from off screen to the center of the screen
	// then as time passes the sprite will move into position,
	// which is all handled in Sprite::Update
	void MoveOnScreen()
	{
		// set the position as off screen
		SetCentrePosition({ 32, -12 });
		// set the desired position to the centre of the screen
		// LerpToPosition takes in the topleft corner of the image, so we have to adjust for differing image dimensions
		LerpToPosition({ 32 - (GetImage()->GetWidth() * 0.5f), 8 - (GetImage()->GetHeight() * 0.5f) });
	}

	// move off screen sets up the lerping from the centre of the screen to off to the left
	void MoveOffScreen()
	{
		// make sure the sprite is positioned correctly in the centre of the screen
		SetCentrePosition({ 32, 8 });
		// then set the lerping to move it off to the left
		LerpToPosition({ -32 - (GetImage()->GetWidth() * 0.5f), 8 - (GetImage()->GetHeight() * 0.5f) });
	}
};


/*
Each pet can be easily defined by inheriting from the Pet class
and then assigning the pet a unique image

when creating the image, the width and height of the image has to be passed in as wel as the string of the content of the image

when setting the centre position of a sprite, you need to already have an image as the dimensions of the image are
used to determine where the centre of the sprite is


Each child class represents a different pet choice
I designed this to be as easy as possible to add more pet choices
*/


class Frog : public Pet
{
public:
	Frog()
		: Pet()
	{
		SetImage(new Image(21, 6, R"(       _     _       
      (')-=-(')      
    __(   "   )__    
   / _/'-----'\_ \   
___\\ \\     // //___
>____)/_\---/_\(____<)"));

		SetCentrePosition({ 32, 8 });
	}
};


class Aardvark : public Pet
{
public:
	Aardvark()
		: Pet()
	{
		SetImage(new Image(23, 7, R"(       _.---._    /\\  
    ./'       "--`\//  
  ./              o \  
 /./\  )______   \__ \ 
./  / /\ \   | \ \  \ \
   / /  \ \  | |\ \  \7
    "     "    "  "    )"));

		SetCentrePosition({ 32, 8 });
	}
};


class Camel : public Pet
{
public:
	Camel()
		: Pet()
	{
		SetImage(new Image(16, 8, R"(   //           
 _oo\           
(__/ \  _  _    
   \  \/ \/ \   
   (         )\ 
    \_______/  \
     [[] [[]    
     [[] [[]    )"));

		SetCentrePosition({ 32, 8 });
	}
};


class Shark : public Pet
{
public:
	Shark()
		: Pet()
	{
		SetImage(new Image(25, 10, R"( _________         .    .
(..       \_    ,  |\  /|
 \       O  \  /|  \ \/ /
  \______    \/ |   \  / 
     vvvv\    \ |   /  | 
     \^^^^  ==   \_/   | 
      `\_   ===    \.  | 
      / /\_   \ /      | 
      |/   \_  \|      / 
             \________/  )"));
		
		SetCentrePosition({ 32, 8 });
	}
};


class Cat : public Pet
{
public:
	Cat()
		: Pet()
	{
		SetImage(new Image(17, 10, R"( ,_     _        
 |\\_,-~/        
 / _  _ |    ,--.
(  @  @ )   / ,-'
 \  _T_/-._( (   
 /         `. \  
|         _  \ | 
 \ \ ,  /      | 
  || |-_\__   /  
 ((_/`(____,-'   )"));

		SetCentrePosition({ 32, 8 });
	}
};


class Dog : public Pet
{
public:
	Dog()
		: Pet()
	{
		SetImage(new Image(22, 9, R"(             ____     
            /    \__  
|\         /    @   \ 
\ \_______|    \  .:|>
 \      ##|    | \__/ 
  |    ####\__/   \   
  /  /  ##       \|   
 /  /__________\  \   
 L_JJ           \__JJ )"));

		SetCentrePosition({ 32, 8 });
	}
};


class Dolphin : public Pet
{
public:
	Dolphin()
		: Pet()
	{
		SetImage(new Image(28, 12, R"(              ,-.           
             /  (           
        _.--'!   '--._      
      ,'              ''.   
     |!                   \ 
   _.'  O      ___       ! \
  (_.-^, __..-'  ''''--.   )
      /,'             _.' / 
                  .-''    | 
                 (..--^.  ' 
                       | /  
                       '    )"));

		SetCentrePosition({ 32, 8 });
	}
};
