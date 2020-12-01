#include "MathsUtility.h"

float Lerp(float a, float b, float t)
{
	return (1 - t) * a + t * b;
}


Vector2f Lerp(Vector2f a, Vector2f b, float t)
{
	return { 
		Lerp(a.x, b.x, t),
		Lerp(a.y, b.y, t)
	};
}

float SqrMagnitude(Vector2f v)
{
	return (v.x * v.x) + (v.y * v.y);
}

float Magnitude(Vector2f v)
{
	return sqrt(SqrMagnitude(v));
}
