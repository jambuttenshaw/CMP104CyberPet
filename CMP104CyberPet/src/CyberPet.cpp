#include "CyberPet.h"

CyberPet::CyberPet()
	: Sprite()
{
	SetImage(new Image(21, 6, R"(       _     _       
      (')-=-(')      
    __(   "   )__    
   / _/'-----'\_ \   
___\\ \\     // //___
>____)/_\---/_\(____<)"));

}

CyberPet::~CyberPet()
{

}

void CyberPet::Update()
{

}
