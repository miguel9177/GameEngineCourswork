#pragma once
#include "Component.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "Shape.h"

//this is a com_mesh, its a visible representation of a gamobject
class Com_Mesh : public Component
{
private:
	//stores its tesxture
	sf::Texture* texture;
	//stores the texture path
	std::string texturePath;
	//stores its shape
	Shape* shape;
	//stores the origin point
	sf::CircleShape* debug_OriginPointShape;
public :
	//this is a unique id identifier, read documentation graph to fully understand its reason, but in short everty component needs an unique identifier
	static const unsigned int uniqueComponentIdIdentifier = 0;
	//stores the scaling factore between the sfml and box2d
	static const float scalingFactor;

	Com_Mesh();

	//constructor that accepts a textture and a shape, so that he can draw it
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

