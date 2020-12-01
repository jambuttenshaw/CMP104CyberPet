#pragma once

#include <cmath>


// define a 2-component vector of floats
struct Vector2f
{
	float x;
	float y;

	// a constructor that just assigns the parameters into the struct
	Vector2f(float _x, float _y)
		: x(_x), y(_y) {}
};

// define a 2-component vector of integers
// exact same structure as the float vector,
// but when talking about positions in the console it doesnt make sense to use real numbers
// where only integers are applicable
struct Vector2i
{
	int x;
	int y;

	Vector2i(int _x, int _y)
		: x(_x), y(_y) {}
};


// Lerp = Linear interpolation
// linearly transitions between a and b based on parameter t, where t is between 0 and 1
// t = 0 returns a, t = 1 returns b
float Lerp(float a, float b, float t);
Vector2f Lerp(Vector2f a, Vector2f b, float t);

// functions for getting magnitude of vectors
float SqrMagnitude(Vector2f v); // getting the square of the magnitude is often a better performing solution
float Magnitude(Vector2f v);
