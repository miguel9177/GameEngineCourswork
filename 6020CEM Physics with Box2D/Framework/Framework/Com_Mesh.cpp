#include "Com_Mesh.h"
#include "GameObject.h"
#include <iostream>



const float Com_Mesh::scalingFactor = 200.f;

Com_Mesh::Com_Mesh() : Component(Component::typeOfComponent::Mesh, uniqueComponentIdIdentifier)
{
	texture = nullptr;
	shape = nullptr;
	// Create a small circle to represent the origin point
	debug_OriginPointShape = new sf::CircleShape(2.15f);
	
}

Com_Mesh::Com_Mesh(std::string texturePath_, Shape* shape_) : Component(Component::typeOfComponent::Mesh, uniqueComponentIdIdentifier)
{
	texturePath = texturePath_;
	texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath))
	{
		std::cout << "Texture did not load!" << "\n" << std::endl;
	}
	shape = shape_;

	// Create a small circle to represent the origin point
	debug_OriginPointShape = new sf::CircleShape(2.15f);

	//if the texture is not 0, it means theres a texture assigned
	if (texture != nullptr && texture->getSize() != sf::Vector2u(0, 0) && shape != nullptr)
	{
		shape->GetDrawableShape()->setTexture(texture);
	}
	//else fill the object with pink color
	else if (shape != nullptr)
	{
		shape->GetDrawableShape()->setFillColor(sf::Color::Magenta);
	}
}

Com_Mesh::~Com_Mesh()
{
	delete texture;
	delete shape;
}

//this is called by the component
void Com_Mesh::Start()
{
}

//this lets the user add a texture to the mesh
void Com_Mesh::SetTexture(std::string texturePath_)
{
	texturePath = texturePath_;
	texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath))
	{
		std::cout << "Texture did not load!" << "\n" << std::endl;
	}
	
	//if the texture is not 0, it means theres a texture assigned
	if (texture != nullptr && texture->getSize() != sf::Vector2u(0, 0) && shape != nullptr)
	{
		shape->GetDrawableShape()->setTexture(texture);
	}
	//else fill the object with pink color
	else if(shape != nullptr)
	{
		shape->GetDrawableShape()->setFillColor(sf::Color::Magenta);
	}
}

//this lets the user add a shape to the Mesh
void Com_Mesh::SetShape(Shape* shape_)
{
	shape = shape_;

	//if the texture is not 0, it means theres a texture assigned
	if (texture != nullptr && texture->getSize() != sf::Vector2u(0, 0) && shape != nullptr)
	{
		shape->GetDrawableShape()->setTexture(texture);
	}
	//else fill the object with pink color
	else if (shape != nullptr)
	{
		shape->GetDrawableShape()->setFillColor(sf::Color::Magenta);
	}
}

//this lets the user add a texture to the mesh
sf::Texture* Com_Mesh::GetTexture()
{
	return texture;
}

std::string Com_Mesh::GetTexturePath()
{
	return texturePath;
}

//this lets the user add a shape to the Mesh
Shape* Com_Mesh::GetShape()
{
	return shape;
}

//this returns the prepared shape to draw
sf::Shape* Com_Mesh::GetMeshToRender()
{
	//this gets the position rotation and scaling of the mesh
	Vector2 positionOfMesh = ((gameObject->GetPosition()) + shape->positionOffsetFromGameObject) * scalingFactor;
	float rotationOfMesh = (gameObject->GetRotation());
	Vector2 scaleOfMesh = (gameObject->GetScale() + shape->scaleOffsetFromGameObject);

	//this gets the bounds of the shape
	sf::FloatRect shapeBounds = shape->GetDrawableShape()->getLocalBounds();

	//moves the origin of the image to the center
	shape->GetDrawableShape()->setOrigin(shapeBounds.width / 2, shapeBounds.height / 2);

	//positions, rotates and scales the mesh
	shape->GetDrawableShape()->setPosition(positionOfMesh);
	shape->GetDrawableShape()->setRotation(rotationOfMesh);
	shape->GetDrawableShape()->setScale(scaleOfMesh);

	//this returns the mesh to render
	return shape->GetDrawableShape();
}

//this draws the origin point of the sfml object
sf::Shape* Com_Mesh::Debug_GetOriginPointToRender()
{
	sf::Vector2f shapePos = shape->GetDrawableShape()->getPosition();
	sf::Vector2f originPointPos = shape->GetDrawableShape()->getOrigin();
	
	debug_OriginPointShape->setFillColor(sf::Color::Red);
	debug_OriginPointShape->setOrigin(2.15f, 2.15f);
	debug_OriginPointShape->setPosition(originPointPos + shapePos);
	return debug_OriginPointShape;
}
