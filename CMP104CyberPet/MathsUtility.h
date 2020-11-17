#pragma once

// define a type for 2-component vector of floats
typedef struct Vector2f
{
	float x;
	float y;

	Vector2f(float _x, float _y)
		: x(_x), y(_y) {}
};

// define a type for 2-component vector of integers
typedef struct Vector2i
{
	int x;
	int y;

	Vector2i(int _x, int _y)
		: x(_x), y(_y) {}
};

// the default data type for vector components is float
typedef struct Vector2 Vector2f;
