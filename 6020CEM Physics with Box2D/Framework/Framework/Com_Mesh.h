#pragma once
#include "Component.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "Shape.h"

class Com_Mesh : public Component
{
private:
	sf::Texture* texture;
	Shape* shape;
public :
	Com_Mesh();

	Com_Mesh(sf::Texture* texture_, Shape* shape_);

	~Com_Mesh();

	void Start() override;

	//this lets the user add a texture to the mesh
	void SetTexture(sf::Texture* texture_);

	//this lets the user add a shape to the Mesh
	void SetShape(Shape* shape_);
};

