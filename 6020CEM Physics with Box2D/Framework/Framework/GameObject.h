#pragma once
#include <map>
#include "Component.h"
#include <vector>
#include <string>
#include "Transform.h"

class RigidBody;
class GameObject
{
private:
	std::map<Component::typeOfComponent, std::vector<Component*>> allComponents;
	//transform is private since if the game object has a rigidbody we cant edit the transform since the rb will be the owner of this body, so we need getter and setters to control this
	Transform* transform;
	//this will store the rigidbody of the gameObject, if its a null pointer, then thers no rigidbody on this Gameobject
	RigidBody* rigidBody = nullptr;

public:
	std::string name;

	GameObject(std::string name_);
	~GameObject();
	GameObject(std::string name_, Transform* transform_);

	//this will add a component to the gameobject
	void AddComponent(Component* componentToAdd);

	//this will return if the user has the component or not
	bool HasComponent(Component* componentToCheck);

	//this will try and get the given component
	//Component* TryGetComponent(Component* componentToCheck);

	//this will try and get the given component, its inline since the visual studio compiler wasnt letting it be in the cpp
	template<typename T>
	inline T* TryGetComponent(Component::typeOfComponent componentType_) 
	{
		// Get the type of component to check
	    Component::typeOfComponent componentType = componentType_;
	
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
	        if (dynamic_cast<T*>(component) != nullptr)
	            return dynamic_cast<T*>(component);
	    }
	
	    return nullptr;
	};

	//this will get all components of a certain type
	std::vector<Component*> GetAllComponentsOfType(Component::typeOfComponent typeOfComponentToGet);

	//this removes a component
	void RemoveComponent(Component* componentToRemove);

#pragma region Geters and setters
	Transform* GetTransform();
	void SetTransform(Transform _newTransform);
	Vector2 GetPosition();
	void SetPosition(Vector2 _newPosition, bool checkForRigidBody = true);
	float GetRotation();
	void SetRotation(float _newRotation);
	Vector2 GetScale();
	void SetScale(Vector2 _newScale);
	bool HasRigidBody();
	RigidBody* TryGetRigidBody();
#pragma endregion

};

