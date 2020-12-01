#include "MathsUtility.h"

// linearly interpolate between a and b
float Lerp(float a, float b, float t)
{
	// simple formula to smoothly transition between a and b depending on t
	return (1 - t) * a + t * b;
}

// this lerp function does the exact same thing, but on a vector
// it lerps each component of the vector between the components of the input
Vector2f Lerp(Vector2f a, Vector2f b, float t)
{
	return { 
		Lerp(a.x, b.x, t),
		Lerp(a.y, b.y, t)
	};
}

// returns the square of the magnitude of the vector given
// this is used often just for better performance than getting the magnitude itself
// since sqrt is an expensive operation
float SqrMagnitude(Vector2f v)
{
	return (v.x * v.x) + (v.y * v.y);
}

// sometimes the magnitude is actually required though
float Magnitude(Vector2f v)
{
	return sqrt(SqrMagnitude(v));
}
