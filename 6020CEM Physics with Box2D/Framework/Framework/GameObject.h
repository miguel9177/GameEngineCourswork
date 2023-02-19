#pragma once
#include <map>
#include "Component.h"
#include <vector>
#include <string>
#include "Transform.h"

class GameObject
{
private:
	std::map<Component::typeOfComponent, std::vector<Component*>> allComponents;
public:
	
	std::string name;

	Transform* transform;

	GameObject(std::string name_);
	~GameObject();
	GameObject(std::string name_, Transform* transform_);

	void AddComponent(Component* componentToAdd);

	void RemoveComponent(Component* componentToRemove);
};

