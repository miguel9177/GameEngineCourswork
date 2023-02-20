#include "Shape_Box.h"

Shape_Box::Shape_Box()
{
	rotOffsetFromGameObject = 0;
	positionOffsetFromGameObject = Vector2(0,0);
	scaleOffsetFromGameObject = Vector2(0, 0);
}

Shape_Box::Shape_Box(Vector2 _positionOffsetFromGameObject, float _rotOffsetFromGameObject, Vector2 _scaleOffsetFromGameObject)
{
	positionOffsetFromGameObject = _positionOffsetFromGameObject;
	rotOffsetFromGameObject = _rotOffsetFromGameObject;
	scaleOffsetFromGameObject = _scaleOffsetFromGameObject;
}
