#pragma once
#include "Vector2.h"
#include <SFML/Graphics/Drawable.hpp>

class Shape
{
public:
	//this sotres the default pixels every shape starts with, and then they are multiplyed by the scale
	static const float defaultPixelsForBasicShapes;

	//this stores the position offset from the game Object
	Vector2 positionOffsetFromGameObject;
	//this stores the scale offset from the game object, if our object is 1,1 of scale
	//and we want 2,2 for the shape, we put 1,1 in here and this will be added to the scale
	Vector2 scaleOffsetFromGameObject;
	//rot offset from the gameobject
	float rotOffsetFromGameObject;

	//this gets the shape out of the type of SF drawable item
	virtual sf::Shape* GetDrawableShape() = 0;
};

