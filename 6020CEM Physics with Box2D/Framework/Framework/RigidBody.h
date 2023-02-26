#pragma once
#include <Box2D/Box2D.h>
#include "Component.h"

class Vector2;
class RigidBody : public Component
{
	//this stores the body of this rb, the b2Body is pratically the same as rigidbody on unity.
	b2Body* body;

public:
	static const unsigned int uniqueComponentIdIdentifier = 200;
	bool useGravity = false;
	
	RigidBody(b2BodyType _typeOfRb);
	RigidBody(b2BodyType _typeOfRb, Vector2 _pos);

	// Inherited via Component
	void Start() override;

	void Update();

#pragma region Getters and Setters
	Vector2 GetPosition();
	void SetPosition(Vector2 _position);
	float GetRotation();
	void SetRotation(float _rot);
	void SetPositionAndRotation(Vector2 _position, float _rot);
#pragma endregion

};

