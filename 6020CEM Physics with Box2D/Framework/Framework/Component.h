#pragma once
class GameObject;
class Component
{
public:
	enum class typeOfComponent { Mesh, Collider, ScriptBehaviour, RigidBody };

private:
	bool enabled;
	typeOfComponent componentType;

public:
	
	GameObject* gameObject;
	Component(typeOfComponent typeOfComponent_);
	~Component();
	typeOfComponent GetTypeOfComponent();
	virtual void Start() = 0;
};

