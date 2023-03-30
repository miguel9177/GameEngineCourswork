#include "SB_BulletFunctionality.h"
#include <iostream>
#include "../PhysicsEngine.h"
#include "../RigidBody.h"
SB_BulletFunctionality::SB_BulletFunctionality() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
}

void SB_BulletFunctionality::Start()
{
	PhysicsEngine::GetInstance()->SubscribeRbToCollisionDetectionCallbacks(this, gameObject->TryGetRigidBody());
}

void SB_BulletFunctionality::Update()
{
	
}

void SB_BulletFunctionality::LateStart()
{
	
}

void SB_BulletFunctionality::BeginContact(b2Contact* contact)
{
	b2Body* collidedBody1 = contact->GetFixtureA()->GetBody();
	b2Body* collidedBody2 = contact->GetFixtureB()->GetBody();
	
	if (collidedBody1 == gameObject->TryGetRigidBody()->Debug_GetB2Body() || collidedBody2 == gameObject->TryGetRigidBody()->Debug_GetB2Body())
	{
		
	}

}

void SB_BulletFunctionality::EndContact(b2Contact* contact)
{
}

