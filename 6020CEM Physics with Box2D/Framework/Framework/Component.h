#pragma once
class GameObject;
class Component
{
public:
	//this stores the type of component
	enum class typeOfComponent { Mesh = 0, Collider = 100, Physics = 200, Audio,ScriptBehaviour = 10000};

private:
	typeOfComponent componentType;
	//each component type has a unique Id identifier, so that we can easaly check if a component is the same as another
	const unsigned int uniqueComponentIdIdentifier;
public:
	bool enabled;
	GameObject* gameObject;//stores the gameobject that owns the component
	Component(typeOfComponent typeOfComponent_, const unsigned int _uniqueComponentIdIdentifier);
	~Component();
	virtual void Start() = 0;
	//this gets the type of component
	typeOfComponent GetTypeOfComponent();
	//returns the unique id identifier
	const unsigned int GetUniqueIdIdentifier();
};

