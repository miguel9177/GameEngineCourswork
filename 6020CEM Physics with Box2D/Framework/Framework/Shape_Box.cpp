#include "Shape_Box.h"

//normal constructor that makes the offsets to 0
Shape_Box::Shape_Box()
{
	rotOffsetFromGameObject = 0;
	positionOffsetFromGameObject = Vector2(0,0);
	scaleOffsetFromGameObject = Vector2(0, 0);
	//sets the box shape
	boxShape = sf::RectangleShape(sf::Vector2f(defaultPixelsForBasicShapes, defaultPixelsForBasicShapes));
}

//this is a constructor that adds an offset to the mesh
Shape_Box::Shape_Box(Vector2 _positionOffsetFromGameObject, float _rotOffsetFromGameObject, Vector2 _scaleOffsetFromGameObject)
{
	positionOffsetFromGameObject = _positionOffsetFromGameObject;
	rotOffsetFromGameObject = _rotOffsetFromGameObject;
	scaleOffsetFromGameObject = _scaleOffsetFromGameObject;
	//sets the box shape
	boxShape = sf::RectangleShape(sf::Vector2f(defaultPixelsForBasicShapes, defaultPixelsForBasicShapes));
}

Shape_Box::~Shape_Box()
{
	//delete boxShape;
}

//returns the drawable shape
sf::Shape* Shape_Box::GetDrawableShape()
{
	return &boxShape;
}

//returns the half width and height
Vector2 Shape_Box::GetHalfWidthAndHalfHeightOffset()
{
	return Vector2((defaultPixelsForBasicShapes  / 2) / 200.f, (defaultPixelsForBasicShapes / 2) / 200.f );
}