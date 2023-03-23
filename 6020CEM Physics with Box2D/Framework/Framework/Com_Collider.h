#pragma once
#include "Component.h"

class b2FixtureDef;
class Com_Collider : public Component
{
public:
	enum ColliderType { BoxColl, CircleColl };
	float mass;
	float friction;
	float bouciness;
private:
	ColliderType typeOfCollider;
public:
	//this is the minimum value of the collider identifiers, all colliders should have values between 100 and 199
	static const unsigned int minimumColliderComponentIdIdentifier = 100;

	Com_Collider(ColliderType type_, unsigned int uniqueComponentIdIdentifier);
	Com_Collider(ColliderType type_, float _mass, float _friction, float _bouciness, unsigned int uniqueComponentIdIdentifier);

	ColliderType GetColliderType();

	virtual b2FixtureDef* GetColliderBox2dDefenition() = 0;

	// Inherited via Component
	virtual void Start();

};

