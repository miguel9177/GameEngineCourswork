#include "GameObject.h"

GameObject::GameObject(std::string name)
{
}

void GameObject::AddComponent(Component* componentToAdd)
{
	allComponents[componentToAdd->GetTypeOfComponent()].push_back(componentToAdd);
}

void GameObject::RemoveComponent(Component* componentToRemove)
{
}


