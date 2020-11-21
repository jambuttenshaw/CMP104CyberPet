#include "Rendering/RenderAPI.h"

RenderAPI::RenderAPI()
{

}

RenderAPI::~RenderAPI()
{

}

void RenderAPI::Init()
{

}

void RenderAPI::Submit(char** imageData)
{
	
}

void RenderAPI::Clear()
{

}

Vector2i RenderAPI::GetConsoleDimensions()
{

	return Vector2i(0, 0);
}

int RenderAPI::GetConsoleWidth()
{
	return GetConsoleDimensions().x;
}

int RenderAPI::GetConsoleHeight()
{
	return GetConsoleDimensions().y;
}
