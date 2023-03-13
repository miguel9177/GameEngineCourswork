#include "Shape_Box.h"

Shape_Box::Shape_Box()
{
	rotOffsetFromGameObject = 0;
	positionOffsetFromGameObject = Vector2(0,0);
	scaleOffsetFromGameObject = Vector2(0, 0);
	boxShape = sf::RectangleShape(sf::Vector2f(defaultPixelsForBasicShapes, defaultPixelsForBasicShapes));
}

Shape_Box::Shape_Box(Vector2 _positionOffsetFromGameObject, float _rotOffsetFromGameObject, Vector2 _scaleOffsetFromGameObject)
{
	positionOffsetFromGameObject = _positionOffsetFromGameObject;
	rotOffsetFromGameObject = _rotOffsetFromGameObject;
	scaleOffsetFromGameObject = _scaleOffsetFromGameObject;
	boxShape = sf::RectangleShape(sf::Vector2f(defaultPixelsForBasicShapes, defaultPixelsForBasicShapes));
}

Shape_Box::~Shape_Box()
{
	//delete boxShape;
}

sf::Shape* Shape_Box::GetDrawableShape()
{
	return &boxShape;
}

Vector2 Shape_Box::GetHalfWidthAndHalfHeightOffset()
{
	return Vector2((defaultPixelsForBasicShapes  / 2) / 200.f, (defaultPixelsForBasicShapes / 2) / 200.f );
}