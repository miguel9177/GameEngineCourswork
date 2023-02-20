#pragma once
class GameObject;
class Component
{
public:
	enum class typeOfComponent { Mesh = 0, Collider = 100, ScriptBehaviour = 10000, RigidBody = 200 };

private:
	typeOfComponent componentType;
	//each component type has a unique Id identifier, so that we can easaly check if a component is the same as another
	const unsigned int uniqueComponentIdIdentifier;
public:
	bool enabled;
	GameObject* gameObject;
	Component(typeOfComponent typeOfComponent_, const unsigned int _uniqueComponentIdIdentifier);
	~Component();
	virtual void Start() = 0;
	typeOfComponent GetTypeOfComponent();
	const unsigned int GetUniqueIdIdentifier();
};

