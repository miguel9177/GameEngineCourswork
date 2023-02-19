#pragma once

class Component
{
public:
	enum class typeOfComponent { Mesh, Collider, ScriptBehaviour, RigidBody };

private:
	bool enabled;
	typeOfComponent componentType;

public:

	Component(typeOfComponent typeOfComponent_);
	~Component();
	typeOfComponent GetTypeOfComponent();
	virtual void Start() = 0;
};

