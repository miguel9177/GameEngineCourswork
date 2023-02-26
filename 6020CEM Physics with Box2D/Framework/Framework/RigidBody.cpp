#include "RigidBody.h"
#include "Vector2.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
RigidBody::RigidBody(b2BodyType _typeOfRb) : Component(Component::typeOfComponent::Physics, uniqueComponentIdIdentifier)
{
	//creates a temp body defenition so that we can create a rigidbody
	b2BodyDef bodyDef;
	bodyDef.type = _typeOfRb;

	//creates the rigidbody
	body = PhysicsEngine::GetInstance()->CreateRigidBody(&bodyDef);
}

RigidBody::RigidBody(b2BodyType _typeOfRb, Vector2 _origin) : Component(Component::typeOfComponent::Physics, uniqueComponentIdIdentifier)
{
	//creates a temp body defenition so that we can create a rigidbody
	b2BodyDef bodyDef;
	bodyDef.type = _typeOfRb;
	bodyDef.position = _origin;

	//creates the rigidbody
	body = PhysicsEngine::GetInstance()->CreateRigidBody(&bodyDef);
}

void RigidBody::Start()
{
}

void RigidBody::Update()
{
	//gameObject->transform->position = body->GetTransform().p;
	//think how im gonna update the transform
}