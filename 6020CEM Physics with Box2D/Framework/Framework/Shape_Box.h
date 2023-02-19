#pragma once
#include <SFML/Graphics.hpp>
#include "Shape.h"

class Shape_Box : public Shape
{
private:
	sf::RectangleShape boxShape;

	Shape_Box();
};

