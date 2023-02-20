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

bool GameObject::HasComponent(Component* _componentToCheck)
{
    return false;
}

void GameObject::RemoveComponent(Component* componentToRemove)
{

}


