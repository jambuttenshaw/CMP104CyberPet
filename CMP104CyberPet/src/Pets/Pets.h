#pragma once

#include "../Core/Sprite.h"


class Pet : public Sprite
{
public:
	Pet()
		: Sprite()
	{}

	void Update(float deltaTime) override {};
};


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

		SetPosition({ 18, 6 });
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

		SetPosition({ 18, 6 });
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

		SetPosition({ 18, 6 });
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
		
		SetPosition({ 18, 6 });
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

		SetPosition({ 18, 6 });
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

		SetPosition({ 18, 6 });
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

		SetPosition({ 18, 6 });
	}
};
