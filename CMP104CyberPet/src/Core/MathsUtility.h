#pragma once


// define a 2-component vector of floats
struct Vector2f
{
	float x;
	float y;

	Vector2f(float _x, float _y)
		: x(_x), y(_y) {}
};

// define a 2-component vector of integers
struct Vector2i
{
	int x;
	int y;

	Vector2i(int _x, int _y)
		: x(_x), y(_y) {}
};
