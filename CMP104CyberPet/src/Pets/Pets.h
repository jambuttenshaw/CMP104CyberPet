#pragma once

#include "../Core/Sprite.h"

class Frog : public Sprite
{
public:
	Frog()
		: Sprite()
	{
		SetImage(new Image(21, 6, R"(       _     _       
      (')-=-(')      
    __(   "   )__    
   / _/'-----'\_ \   
___\\ \\     // //___
>____)/_\---/_\(____<)"));
	}

	void Update(float deltaTime) override {}
};


class Aardvark : public Sprite
{
public:
	Aardvark()
		: Sprite()
	{
		SetImage(new Image(23, 7, R"(       _.---._    /\\  
    ./'       "--`\//  
  ./              o \  
 /./\  )______   \__ \ 
./  / /\ \   | \ \  \ \
   / /  \ \  | |\ \  \7
    "     "    "  "    )"));
	}

	void Update(float deltaTime) override {}
};
