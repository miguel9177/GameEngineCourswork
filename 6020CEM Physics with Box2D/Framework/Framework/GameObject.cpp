#include "GameObject.h"
#include "RigidBody.h"
#include <iostream>
#include "Com_Collider.h"

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

//this adds components to the game object
void GameObject::AddComponent(Component* componentToAdd)
{
    //if the component that we are adding is a physics component
    if (componentToAdd->GetTypeOfComponent() == Component::typeOfComponent::Physics)
    {
        //if the component we are adding is a rigidbody
        if (componentToAdd->GetUniqueIdIdentifier() == RigidBody::uniqueComponentIdIdentifier)
        {
            if (HasRigidBody())
            {
                std::cout << "ERROR: trying to add a rigidbody to a GameObject that already has a rigidbody" << std::endl;
                return;
            }
            rigidBody = static_cast<RigidBody*>(componentToAdd);
        }
    }

    //if the component we are adding is a collider component
    if (componentToAdd->GetTypeOfComponent() == Component::typeOfComponent::Collider)
    {
        //if the component we are adding is a collider
        if (componentToAdd->GetUniqueIdIdentifier() == Com_Collider::uniqueComponentIdIdentifier)
        {
            if (!HasRigidBody())
            {
                std::cout << "ERROR: trying to add a collider to a gameobject that has no Rigidbody" << std::endl;
                return;
            }
        }
    }

	allComponents[componentToAdd->GetTypeOfComponent()].push_back(componentToAdd);
    componentToAdd->gameObject = this;
    componentToAdd->Start();
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

////this will return the component if the gameobject has it, and return null if the gameObject doesnt have it
//Component* GameObject::TryGetComponent(Component* _componentToCheck)
//{
//    // Get the type of the component to check
//    Component::typeOfComponent componentType = _componentToCheck->GetTypeOfComponent();
//
//    // Check if the type of component exists in the map
//    auto it = allComponents.find(componentType);
//    if (it == allComponents.end()) {
//        return nullptr;
//    }
//
//    // Get the vector of components for the given type
//    std::vector<Component*>& componentsOfType = it->second;
//
//    // Loop through the vector of components
//    for (std::vector<Component*>::iterator it = componentsOfType.begin(); it != componentsOfType.end(); ++it)
//    {
//        // do something with each component in the vector
//        Component* component = *it;
//        if (component->GetUniqueIdIdentifier() == _componentToCheck->GetUniqueIdIdentifier())
//            return component;
//    }
//
//    return nullptr;
//}

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

#pragma region Geters and setters

    Transform* GameObject::GetTransform()
    {
        return transform;
    }

    //this sets the transfpr,, it checks if we have a rb, if yes tell rb to update the transform
    void GameObject::SetTransform(Transform _newTransform)
    {
        if (HasRigidBody())
        {
            rigidBody->SetPositionAndRotation(_newTransform.position, _newTransform.rotation);
            transform->scale = _newTransform.scale;
        }
        else
            *transform = _newTransform;
    }

    Vector2 GameObject::GetPosition()
    {
        return transform->position;
    }

    //this sets the positiom, it checks if we have a rb, if yes tell rb to update the position
    void GameObject::SetPosition(Vector2 _newPosition, bool checkForRigidBody)
    {
        if (HasRigidBody() && checkForRigidBody)
            rigidBody->SetPosition(_newPosition);

        transform->position = _newPosition;
    }

    float GameObject::GetRotation()
    {
        return transform->rotation;
    }

    //this sets the rotation, it checks if we have a rb, if yes tell rb to update the rotation
    void GameObject::SetRotation(float _newRotation)
    {
        transform->rotation = _newRotation;
        if (HasRigidBody())
            rigidBody->SetRotation(_newRotation);
    }

    Vector2 GameObject::GetScale()
    {
        return transform->scale;
    }

    void GameObject::SetScale(Vector2 _newScale)
    {
        transform->scale = _newScale;
    }

    bool GameObject::HasRigidBody()
    {
        if (rigidBody == nullptr)
            return false;
        else
            return true;
    }

    RigidBody* GameObject::TryGetRigidBody()
    {
        if (rigidBody == nullptr)
            return nullptr;
        else
            return rigidBody;
    }

#pragma endregion



