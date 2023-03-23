#pragma once
#include "Component.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "Shape.h"

class Com_Mesh : public Component
{
private:
	sf::Texture* texture;
	std::string texturePath;
	Shape* shape;
	sf::CircleShape* debug_OriginPointShape;
public :
	static const unsigned int uniqueComponentIdIdentifier = 0;
	static const float scalingFactor;

	Com_Mesh();

	Com_Mesh(std::string texturePath_, Shape* shape_);

	~Com_Mesh();

	void Start() override;

	//this lets the user add a texture to the mesh
	void SetTexture(std::string texture_);

	//this lets the user add a shape to the Mesh
	void SetShape(Shape* shape_);

	//returns the current texture
	sf::Texture* GetTexture();
	std::string GetTexturePath();
	//returns the current shape
	Shape* GetShape();
	//returns the mesh all prepared to be drawn, with correct position, rotation and texture
	sf::Shape* GetMeshToRender();
	//this will get the origin point to render
	sf::Shape* Debug_GetOriginPointToRender();
};

