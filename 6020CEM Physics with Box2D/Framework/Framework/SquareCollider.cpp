#include "SquareCollider.h"
#include "Vector2.h"

SquareCollider::SquareCollider(Vector2 _halfSize) : Com_Collider(ColliderType::BoxColl)
{
	halfSize = _halfSize;
	posOffset = Vector2(0, 0);
	offsetAngle = 0;
}

SquareCollider::SquareCollider(Vector2 _halfSize, Vector2 _offsetPos) : Com_Collider(ColliderType::BoxColl)
{
	halfSize = _halfSize;
	posOffset = _offsetPos;
	offsetAngle = 0;
}

SquareCollider::SquareCollider(Vector2 _halfSize, Vector2 _offsetPos, float _offsetAngle) : Com_Collider(ColliderType::BoxColl)
{
	halfSize = _halfSize;
	posOffset = _offsetPos;
	offsetAngle = _offsetAngle;
}
