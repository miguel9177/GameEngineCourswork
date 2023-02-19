#include "Transform.h"

Transform::Transform()
{
	position = Vector2(); 
	rotation = 0;
	scale = Vector2(1, 1);
}

Transform::Transform(Vector2 position_, float rotation_, Vector2 scale_)
{
	position = position_;
	rotation = rotation_;
	scale = scale_;
}
