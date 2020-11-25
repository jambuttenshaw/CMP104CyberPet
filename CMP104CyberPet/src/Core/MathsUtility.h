#pragma once

struct Vector2f;
struct Vector2i;

// define a 2-component vector of floats
struct Vector2f
{
	float x;
	float y;

	Vector2f(float _x, float _y)
		: x(_x), y(_y) {}

	Vector2f(Vector2i v)
		: x((float)v.x), y((float)v.y) {}
};

// define a 2-component vector of integers
struct Vector2i
{
	int x;
	int y;

	Vector2i(int _x, int _y)
		: x(_x), y(_y) {}

	Vector2i(Vector2f v)
		: x(round(v.x)), y(round(v.y)) {}
};

// the default data type for vector components is float
typedef Vector2f Vector2;
