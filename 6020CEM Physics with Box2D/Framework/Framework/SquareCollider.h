#pragma once
#include "Com_Collider.h"
class Vector2;
class SquareCollider : public Com_Collider
{
private:
	Vector2 halfSize;
	Vector2 posOffset;
	float offsetAngle;
public:
	SquareCollider(Vector2 _halfSize);
	SquareCollider(Vector2 _halfSize, Vector2 _offsetPos);
	SquareCollider(Vector2 _halfSize, Vector2 _offsetPos, float _offsetAngle);


};

