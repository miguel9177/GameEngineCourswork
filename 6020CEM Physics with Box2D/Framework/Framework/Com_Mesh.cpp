#include "Com_Mesh.h"

Com_Mesh::Com_Mesh() : Component(Component::typeOfComponent::Mesh)
{
	texture = nullptr;
	shape = nullptr;
	
}

Com_Mesh::Com_Mesh(sf::Texture* texture_, Shape* shape_) : Component(Component::typeOfComponent::Mesh)
{
	texture = texture_;
	shape = shape_;
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
}

//this lets the user add a shape to the Mesh
void Com_Mesh::SetShape(Shape* shape_)
{
	shape = shape_;
}

