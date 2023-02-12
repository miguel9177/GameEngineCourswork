#pragma once
class Component
{
private:
	enum class typeOfComponent { Mesh, Collider, ScriptBehaviour, RigidBody };
	typeOfComponent componentType;
	bool enabled;

public:
	Component(typeOfComponent typeOfComponent_);
	~Component();
	virtual void Start();
};

