#include "CircleCollider.h"
#include "Vector2.h"
#include <Box2D/Box2D.h>
#include "GameObject.h"
#include "RigidBody.h"
#include <iostream>

#pragma region Constructors

CircleCollider::CircleCollider(float _radius) : Com_Collider(ColliderType::CircleColl, uniqueComponentIdIdentifier)
{
	radius = _radius;
	posOffset = Vector2(0, 0);
	offsetAngle = 0;

}


CircleCollider::CircleCollider(float _radius, Vector2 _offsetPos) : Com_Collider(ColliderType::BoxColl, uniqueComponentIdIdentifier)
{
	radius = _radius;
	posOffset = _offsetPos;
	offsetAngle = 0;

}


CircleCollider::CircleCollider(float _radius, Vector2 _offsetPos, float _offsetAngle) : Com_Collider(ColliderType::BoxColl, uniqueComponentIdIdentifier)
{
	radius = _radius;
	posOffset = _offsetPos;
	offsetAngle = _offsetAngle;

}

CircleCollider::CircleCollider(float _radius, float _mass, float _friction, float _bouciness)
	: Com_Collider(ColliderType::BoxColl, _mass, _friction, _bouciness, uniqueComponentIdIdentifier)
{
	radius = _radius;
	posOffset = Vector2(0, 0);
	offsetAngle = 0;

}


CircleCollider::CircleCollider(float _radius, Vector2 _offsetPos, float _mass, float _friction, float _bouciness)
	: Com_Collider(ColliderType::BoxColl, _mass, _friction, _bouciness, uniqueComponentIdIdentifier)
{
	radius = _radius;
	posOffset = _offsetPos;
	offsetAngle = 0;

}

CircleCollider::CircleCollider(float _radius, Vector2 _offsetPos, float _offsetAngle, float _mass, float _friction, float _bouciness) 
	: Com_Collider(ColliderType::BoxColl, _mass, _friction, _bouciness, uniqueComponentIdIdentifier)
{
	radius = _radius;
	posOffset = _offsetPos;
	offsetAngle = _offsetAngle;

}

#pragma endregion

void CircleCollider::Start()
{
	CreateCollider();
}

void CircleCollider::CreateCollider()
{
	//this creates a circle shape with the specific radius
	b2CircleShape circleShape;
	circleShape.m_radius = radius * gameObject->GetTransform()->scale.x;
	circleShape.m_p.Set(posOffset.x, posOffset.y); // Set the position offset

	//assigns the collider settings
	coll.shape = &circleShape;
	coll.density = mass;   
	coll.friction = friction;  
	coll.restitution = bouciness;  

	if (gameObject->HasRigidBody())
		gameObject->TryGetRigidBody()->AddCollider(this);
}

b2FixtureDef* CircleCollider::GetColliderBox2dDefenition()
{
	return &coll;
}



