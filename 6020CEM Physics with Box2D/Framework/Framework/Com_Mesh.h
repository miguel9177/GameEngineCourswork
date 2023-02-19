#pragma once
#include "Component.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "Shape.h"

class Com_Mesh : public Component
{
private:
	sf::Texture texture;
	Shape shape;
public :
	Com_Mesh();
	void Start() override;
};

