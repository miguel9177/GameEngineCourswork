#pragma once
#include <map>
#include "Component.h"
#include <vector>
#include <string>
class GameObject
{
private:
	std::map<Component::typeOfComponent, std::vector<Component*>> allComponents;
public:
	GameObject(std::string name);

	void AddComponent(Component* componentToAdd);

	void RemoveComponent(Component* componentToRemove);
};

