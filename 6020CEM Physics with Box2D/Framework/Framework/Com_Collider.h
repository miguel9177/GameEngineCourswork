#pragma once
#include "Component.h"
class Com_Collider : public Component
{
public:
	enum ColliderType { BoxColl, CircleColl };
private:
	ColliderType typeOfCollider;
public:
	static const unsigned int uniqueComponentIdIdentifier = 100;

	Com_Collider(ColliderType type_);

	ColliderType GetColliderType();

	// Inherited via Component
	virtual void Start();
};

