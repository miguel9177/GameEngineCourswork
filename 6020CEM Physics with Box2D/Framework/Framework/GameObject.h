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

	//this will add a component to the gameobject
	void AddComponent(Component* componentToAdd);

	//this will return if the user has the component or not
	bool HasComponent(Component* componentToCheck);

	//this will try and get the given component
	Component* TryGetComponent(Component* componentToCheck);

	//this will get all components of a certain type
	std::vector<Component*> GetAllComponentsOfType(Component::typeOfComponent typeOfComponentToGet);

	//this removes a component
	void RemoveComponent(Component* componentToRemove);
};

