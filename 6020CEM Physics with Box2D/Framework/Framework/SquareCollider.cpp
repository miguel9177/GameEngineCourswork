#include "SquareCollider.h"
#include "Vector2.h"
#include <Box2D/Box2D.h>
#include "GameObject.h"
#include "RigidBody.h"
#include <iostream>

#pragma region Constructors

SquareCollider::SquareCollider(Vector2 _halfSize) : Com_Collider(ColliderType::BoxColl, uniqueComponentIdIdentifier)
{
	halfSize = _halfSize;
	posOffset = Vector2(0, 0);
	offsetAngle = 0;
	
}

SquareCollider::SquareCollider(Vector2 _halfSize, Vector2 _offsetPos) : Com_Collider(ColliderType::BoxColl, uniqueComponentIdIdentifier)
{
	halfSize = _halfSize;
	posOffset = _offsetPos;
	offsetAngle = 0;
	
}

SquareCollider::SquareCollider(Vector2 _halfSize, Vector2 _offsetPos, float _offsetAngle) : Com_Collider(ColliderType::BoxColl, uniqueComponentIdIdentifier)
{
	halfSize = _halfSize;
	posOffset = _offsetPos;
	offsetAngle = _offsetAngle;
	
}

SquareCollider::SquareCollider(Vector2 _halfSize, float _mass, float _friction, float _bouciness) 
	: Com_Collider(ColliderType::BoxColl, _mass, _friction, _bouciness, uniqueComponentIdIdentifier)
{
	halfSize = _halfSize;
	posOffset = Vector2(0, 0);
	offsetAngle = 0;

}

SquareCollider::SquareCollider(Vector2 _halfSize, Vector2 _offsetPos, float _mass, float _friction, float _bouciness) 
	: Com_Collider(ColliderType::BoxColl, _mass, _friction, _bouciness, uniqueComponentIdIdentifier)
{
	halfSize = _halfSize;
	posOffset = _offsetPos;
	offsetAngle = 0;
	
}

SquareCollider::SquareCollider(Vector2 _halfSize, Vector2 _offsetPos, float _offsetAngle, float _mass, float _friction, float _bouciness) 
	: Com_Collider(ColliderType::BoxColl, _mass, _friction, _bouciness, uniqueComponentIdIdentifier)
{
	halfSize = _halfSize;
	posOffset = _offsetPos;
	offsetAngle = _offsetAngle;
	
}

#pragma endregion

void SquareCollider::Start()
{
	CreateCollider();
}

//this will create the box2d collider (in this case a square collider)
void SquareCollider::CreateCollider()
{
	//this creates a box shape with the specific halfsize, offset and angles
	b2PolygonShape boxShape;
	boxShape.SetAsBox(halfSize.x * gameObject->GetTransform()->scale.x, halfSize.y * gameObject->GetTransform()->scale.y, posOffset, offsetAngle);

	//assigns the colleder settings
	coll.shape = &boxShape;
	coll.density = mass;   
	coll.friction = friction;  
	coll.restitution = bouciness;  

	if(gameObject->HasRigidBody())
		gameObject->TryGetRigidBody()->AddCollider(this);
}

//this gets the box 2d collider defenition of this collider
b2FixtureDef* SquareCollider::GetColliderBox2dDefenition()
{
	return &coll;
}