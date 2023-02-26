#pragma once
#include <Box2D/Box2D.h>
#include "Component.h"

class Vector2;
class RigidBody : public Component
{
public:
	static const unsigned int uniqueComponentIdIdentifier = 200;
	//this stores the body of this rb, the b2Body is pratically the same as rigidbody on unity.
	b2Body* body;
	bool useGravity = false;
	
	RigidBody(b2BodyType _typeOfRb);
	RigidBody(b2BodyType _typeOfRb, Vector2 _origin);

	// Inherited via Component
	void Start() override;

	void Update() override;
};

