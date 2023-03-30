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
	//stores all componenbts
	std::map<Component::typeOfComponent, std::vector<Component*>> allComponents;
	//transform is private since if the game object has a rigidbody we cant edit the transform since the rb will be the owner of this body, so we need getter and setters to control this
	Transform* transform;
	//this will store the rigidbody of the gameObject, if its a null pointer, then thers no rigidbody on this Gameobject
	RigidBody* rigidBody = nullptr;

public:
	//stores the name
	std::string name;

	GameObject(std::string name_);
	~GameObject();
	GameObject(std::string name_, Transform* transform_);

	//this will add a component to the gameobject
	void AddComponent(Component* componentToAdd);

	//this will return if the user has the component or not
	bool HasComponent(Component* componentToCheck);

	//this will try and get the given component, its inline since the visual studio compiler wasnt letting it be in the cpp
	template<typename T>
	inline T* TryGetComponent(Component::typeOfComponent componentType_) 
	{	
	    //this checks if the components exists and stores the components aswell in a map
	    auto it = allComponents.find(componentType_);
	    if (it == allComponents.end()) {
	        return nullptr;
	    }
	
	    //gets all the comppnents of the correct type
	    std::vector<Component*>& componentsOfType = it->second;
	
	    //loops trhough all of them
	    for (std::vector<Component*>::iterator it = componentsOfType.begin(); it != componentsOfType.end(); ++it)
	    {
	        //returns the requested component
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
	inline std::map<Component::typeOfComponent, std::vector<Component*>>* GetAllComponents() { return &allComponents; };
#pragma endregion

};

