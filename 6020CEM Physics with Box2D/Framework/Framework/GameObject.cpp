#include "GameObject.h"

GameObject::GameObject(std::string name_)
{
	name = name_;

}

GameObject::~GameObject()
{
	delete transform;

    // Iterate over each key-value pair in the map
    for (auto& typeOfComponent_ : allComponents) {
        // Get the vector of components
        auto& componentVector = typeOfComponent_.second;

        // Iterate over each component in the vector
        for (auto& component : componentVector) {
            // Delete the component
            delete component;
        }

        // Clear the vector
        componentVector.clear();
    }

    // Clear the map
    allComponents.clear();
}

GameObject::GameObject(std::string name_, Transform* transform_)
{
	name = name_;
	transform = transform_;
}

void GameObject::AddComponent(Component* componentToAdd)
{
	allComponents[componentToAdd->GetTypeOfComponent()].push_back(componentToAdd);
    componentToAdd->gameObject = this;
}

//this will return true if the user has the component
bool GameObject::HasComponent(Component* _componentToCheck)
{
    // Get the type of the component to check
    Component::typeOfComponent componentType = _componentToCheck->GetTypeOfComponent();

    // Check if the type of component exists in the map
    auto it = allComponents.find(componentType);
    if (it == allComponents.end()) {
        return false;
    }

    // Get the vector of components for the given type
    std::vector<Component*>& componentsOfType = it->second;

    // Loop through the vector of components
    for (std::vector<Component*>::iterator it = componentsOfType.begin(); it != componentsOfType.end(); ++it) 
    {
        // do something with each component in the vector
        Component* component = *it;
        if (component->GetUniqueIdIdentifier() == _componentToCheck->GetUniqueIdIdentifier())
            return true;
    }

    return false;
}

//this will return the component if the gameobject has it, and return null if the gameObject doesnt have it
Component* GameObject::TryGetComponent(Component* _componentToCheck)
{
    // Get the type of the component to check
    Component::typeOfComponent componentType = _componentToCheck->GetTypeOfComponent();

    // Check if the type of component exists in the map
    auto it = allComponents.find(componentType);
    if (it == allComponents.end()) {
        return nullptr;
    }

    // Get the vector of components for the given type
    std::vector<Component*>& componentsOfType = it->second;

    // Loop through the vector of components
    for (std::vector<Component*>::iterator it = componentsOfType.begin(); it != componentsOfType.end(); ++it)
    {
        // do something with each component in the vector
        Component* component = *it;
        if (component->GetUniqueIdIdentifier() == _componentToCheck->GetUniqueIdIdentifier())
            return component;
    }

    return nullptr;
}

//this will get all the components of a certain type
std::vector<Component*> GameObject::GetAllComponentsOfType(Component::typeOfComponent _typeOfComponentToGet)
{
    // Check if the type of component exists in the map
    auto it = allComponents.find(_typeOfComponentToGet);

    // Check if the type of component exists in the map
    if (it != allComponents.end()) {
        // Get the vector of components for the given type
        std::vector<Component*>& componentsOfType = it->second;

        // Return the vector of components
        return componentsOfType;
    }

    // If the type of component is not found, return an empty vector
    return std::vector<Component*>();
}

void GameObject::RemoveComponent(Component* componentToRemove)
{

}


