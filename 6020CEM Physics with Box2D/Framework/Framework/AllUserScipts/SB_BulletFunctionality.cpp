#include "SB_BulletFunctionality.h"
#include <iostream>
#include "../PhysicsEngine.h"
#include "../RigidBody.h"
SB_BulletFunctionality::SB_BulletFunctionality() : ScriptBehaviour(uniqueComponentIdIdentifier)
{
}

//starts, runs once when the component is added to the object
void SB_BulletFunctionality::Start()
{
	PhysicsEngine::GetInstance()->SubscribeRbToCollisionDetectionCallbacks(this, gameObject->TryGetRigidBody());
}

//updates every frame
void SB_BulletFunctionality::Update()
{
	
}

//late start is runned once at the beigining of the gameplay, if the script is added at runtime, this wont be called 
void SB_BulletFunctionality::LateStart()
{
	
}

//on collision enter
void SB_BulletFunctionality::BeginContact(b2Contact* contact)
{
	//we get both the collided objects
	b2Body* collidedBody1 = contact->GetFixtureA()->GetBody();
	b2Body* collidedBody2 = contact->GetFixtureB()->GetBody();
	
	//iff the collision was made with our object do something, havent filled this since i don need it
	if (collidedBody1 == gameObject->TryGetRigidBody()->Debug_GetB2Body() || collidedBody2 == gameObject->TryGetRigidBody()->Debug_GetB2Body())
	{
		
	}

}

//on collisiomn exit
void SB_BulletFunctionality::EndContact(b2Contact* contact)
{
}

