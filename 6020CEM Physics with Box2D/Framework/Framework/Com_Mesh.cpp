#include "Com_Mesh.h"
#include "GameObject.h"

const float Com_Mesh::scalingFactor = 200.f;

Com_Mesh::Com_Mesh() : Component(Component::typeOfComponent::Mesh, uniqueComponentIdIdentifier)
{
	texture = nullptr;
	shape = nullptr;
	
}

Com_Mesh::Com_Mesh(sf::Texture* texture_, Shape* shape_) : Component(Component::typeOfComponent::Mesh, uniqueComponentIdIdentifier)
{
	texture = texture_;
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
void Com_Mesh::SetTexture(sf::Texture* texture_)
{
	texture = texture_;
	
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

//this lets the user add a shape to the Mesh
Shape* Com_Mesh::GetShape()
{
	return shape;
}

//this returns the prepared shape to draw
sf::Shape* Com_Mesh::GetMeshToRender()
{
	//OFFSET X += HW Y += HY
	//get the correct position, rotation and scale of the mesh, applying its ofssets
	Vector2 positionOfMesh = (gameObject->GetPosition() + (shape->GetHalfWidthAndHalfHeightOffset()) + shape->positionOffsetFromGameObject) * scalingFactor;
	float rotationOfMesh = (gameObject->GetRotation());
	Vector2 scaleOfMesh = (gameObject->GetScale() + shape->scaleOffsetFromGameObject);

	//set the shape position, rotation, and scale of mesh
	shape->GetDrawableShape()->setPosition(positionOfMesh);
	shape->GetDrawableShape()->setRotation(rotationOfMesh);
	shape->GetDrawableShape()->setScale(scaleOfMesh);
	return shape->GetDrawableShape();
}
