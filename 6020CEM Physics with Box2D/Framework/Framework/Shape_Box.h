#pragma once
#include <SFML/Graphics.hpp>
#include "Shape.h"

class Shape_Box : public Shape
{
private:
	sf::RectangleShape boxShape;	

public:
	Shape_Box();
	Shape_Box(Vector2 _positionOffsetFromGameObject, float _rotOffsetFromGameObject, Vector2 _scaleOffsetFromGameObject);
	~Shape_Box();
	//this will return the sape of the rectangleShape
	sf::Shape* GetDrawableShape() override;
	//this will return the sape of the rectangleShape
	Vector2 GetHalfWidthAndHalfHeightOffset() override;
};
