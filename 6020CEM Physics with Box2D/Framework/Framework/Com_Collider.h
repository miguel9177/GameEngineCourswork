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
	static const unsigned int uniqueComponentIdIdentifier = 100;

	Com_Collider(ColliderType type_);
	Com_Collider(ColliderType type_, float _mass, float _friction, float _bouciness);

	ColliderType GetColliderType();

	virtual b2FixtureDef* GetColliderBox2dDefenition() = 0;

	// Inherited via Component
	virtual void Start();

};

