#pragma once
#include "Vector2.h"
class Transform
{
public:
	Vector2 position;
	float rotation;
	Vector2 scale;

	Transform();
	
	Transform(Vector2 position_, float rotation_, Vector2 scale);
};

